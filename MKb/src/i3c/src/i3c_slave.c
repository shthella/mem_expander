#include <gpio.h>
#include <interrupt.h>
#include "riscv_cpu.h"
#include "i3c.h"
#include "i3cs_reg.h"
#include "xil_exception.h"

uint32_t transmit_command;
/* code generalised for modifying BUF 
 * threshold with i3c_dport_q_entries */
//uint32_t i3c_dport_q_entries = 4;

volatile uint32_t jumpToTIM = 0;
volatile uint32_t d2d_status = 0;

struct metal_interrupt* sInterrupt;
struct metal_interrupt *s_cpu_intr;
struct metal_cpu *s_cpu;

#ifdef BOOTROM_MODE
extern uint8_t debug_gpio_set(uint8_t state);
#endif

uint32_t i3c_slave_get_d2d_status(void) {
    return d2d_status;
}

uint32_t i3c_slave_get_jump_addr(void) {
    return jumpToTIM;
}

// Interrupt handler for I3C slave.
void i3c_slave_interrupt_handler(void) __attribute__((interrupt));
void i3c_slave_interrupt_handler(void) 
{
	uint32_t i3c_dport_q_entries = 4;
	volatile uint32_t rddata[i3c_dport_q_entries];
	volatile uint32_t wrdata[i3c_dport_q_entries];
    uint8_t no_gpio_toggle = 0;
	uint32_t intr_status = 0;
	static uint8_t tid;
	uint8_t queue_level=0;
    struct metal_interrupt* sInt;

	//printf("[DEBUG-AKURRA][%d][%s]I3C Slave interrupt Handler invoked\n",__LINE__, __func__);
	intr_status = I3C_REG_READ(I3CS_INTR_STATUS);
	
 	// Bit[11] READ_REQ_RECV_STS --   This is kind of an error mechanism.  What it means is that the master is sending a read request, but the slave has not done what it needs to do properly.  Slave needs to put data in its TX buffer and load the command queue such that the slave knows how much data to send to master for that read; clear required
	if((intr_status >> 11) & 0x1)
	{
		I3C_REG_WRITE((0x1<<11),I3CS_INTR_STATUS);
	}
	// Bit[9] TRANSFER_ERR_STS -- we should probably report if there is an error but this is low priority for now (can add later); clear required
	if((intr_status >> 9) & 0x1)
	{
		//toggle the gpio indicating the Dynamic Address is assigned via ENTDAA/SETDASA.
		I3C_REG_WRITE((0x1<<9),I3CS_INTR_STATUS);
	}
	// Bit[8] DYN_ADDR_ASSGN_STS -- should only trigger once during initial GFH & MKB setup; clear required
	if((intr_status >> 8) & 0x1)
	{
		I3C_REG_WRITE((0x1<<8),I3CS_INTR_STATUS);
		//toggle_i3c_ready();
	}
	// Bit[6] CCC_UPDATED_STS -- triggers every time command from Master is received; clear required
	if((intr_status >> 6) & 0x1)
	{
		I3C_REG_WRITE((0x1<<6),I3CS_INTR_STATUS);
	}
	// Bit[4] RESP_READY_STS -- triggers when response is ready in the response queue. Read to clear, otherwise the queue will be full and next commands are stalled.
	if((intr_status >> 4) & 0x1)
	{
		queue_level = (I3C_REG_READ(I3CS_QUEUE_STATUS_LEVEL)>>0x8) & 0xFF;
		while(queue_level != 0)
		{
			queue_level--;
			I3C_REG_READ(I3CS_RESPONSE_QUEUE_PORT);
		}
	}
	if((intr_status >> 0x1) & 0x1) //checking for RXbuffer interrupt - RX_THLD_STS
	{
        uint32_t dPos;
        uint8_t errCode = 0;
        for(dPos = 0; dPos < i3c_dport_q_entries; dPos++){
  		    rddata[dPos] = I3C_REG_READ(I3CS_RX_DATA_PORT);
        }
 
        switch((rddata[0] & I3C_OPCODE_MASK))
		{
            case READ_REGISTER_OPCODE:
            {
#ifdef BOOTROM_MODE
    			debug_gpio_set(0x4);
#endif
                uint32_t addr, dataQEntries, rdEntries;
                uint32_t dataLen = ((rddata[0] & I3C_DATALEN_MASK)>>I3C_DATALEN_POS);
    
                addr = rddata[1];
                dataQEntries = dataLen/4;
    
                if (dataQEntries < (i3c_dport_q_entries-2)) {
                    rdEntries = dataQEntries;
                } else {
                    rdEntries = i3c_dport_q_entries-2;
                    errCode = 0x10;//TODO ErrCode need to finalise
                }
    
      			transmit_command = 0;
      			transmit_cmd(TTC_CMD_ATR, 0x0);
      			transmit_cmd(TTC_TID, tid&0x7);
      			transmit_cmd(TTC_DATA_LENGTH, i3c_dport_q_entries * 4);
      			I3C_REG_WRITE(transmit_command, I3CS_COMMAND_QUEUE_PORT);
      			transmit_command = 0;
    
      			I3C_REG_WRITE(( ((errCode&I3C_ERROR_MASK) << I3C_ERROR_POS) |
                                (READ_REGISTER_RESPONSE_OPCODE & I3C_OPCODE_MASK)|
                                (((dataQEntries*4)<<I3C_DATALEN_POS)&I3C_DATALEN_MASK)),
                                I3CS_TX_DATA_PORT);
                addr = rddata[1];
      			I3C_REG_WRITE(addr, I3CS_TX_DATA_PORT);
                for (dPos=0; dPos < (i3c_dport_q_entries-2); dPos++) {
                    if (dPos < dataQEntries) {
          		    	wrdata[2] = I3C_REG_READ((addr+dPos*4));
          		    	I3C_REG_WRITE(wrdata[2], I3CS_TX_DATA_PORT);
                    } else {
          		    	I3C_REG_WRITE(0x0, I3CS_TX_DATA_PORT);
                    }
                }
    
		    }
            break;
            case WRITE_REGISTER_OPCODE:
    		{
#ifdef BOOTROM_MODE
    			debug_gpio_set(0x5);
#endif
                uint32_t addr, dataQEntries, rdEntries, dPos1;
                uint32_t dataLen = ((rddata[0] & I3C_DATALEN_MASK)>>I3C_DATALEN_POS);
    
                addr = rddata[1];
                dataQEntries = dataLen/4;
    
                for (dPos1 = 0; dPos1 < (i3c_dport_q_entries-2); dPos1++, addr += 4) {
                    if (dPos1 < dataQEntries) {
                        I3C_REG_WRITE(rddata[2+dPos1], addr);
                    }
                }
                if (dataQEntries > (i3c_dport_q_entries-2)) {
                    uint32_t tmpData;
                    while (((I3C_REG_READ(I3CS_DATA_BUFFER_STATUS_LEVEL)>>16)&0xff) != (I3C_RX_BUF_MAX - i3c_dport_q_entries));
                    for(; dPos1 < (I3C_RX_BUF_MAX -(i3c_dport_q_entries - 2)); dPos1++, addr += 4){
                        tmpData = I3C_REG_READ(I3CS_RX_DATA_PORT);
                        if (dPos1 < dataQEntries) {
                            I3C_REG_WRITE(tmpData, addr);
                        }
                    }
                }
                
      			transmit_command = 0;
      			transmit_cmd(TTC_CMD_ATR, 0x0);
      			transmit_cmd(TTC_TID, tid&0x7);
      			transmit_cmd(TTC_DATA_LENGTH, i3c_dport_q_entries * 4);
      			I3C_REG_WRITE(transmit_command, I3CS_COMMAND_QUEUE_PORT);
      			transmit_command = 0;
    
                /* for WRITE_REGISTER_RESPONSE_OPCODE we only
                 * do 4 entry write for pvt read */
                I3C_REG_WRITE(((WRITE_REGISTER_RESPONSE_OPCODE & I3C_OPCODE_MASK)|
                    (((dataQEntries*4)<<I3C_DATALEN_POS)&I3C_DATALEN_MASK)), I3CS_TX_DATA_PORT);
                addr = rddata[1];
                I3C_REG_WRITE(addr, I3CS_TX_DATA_PORT);
    
                for (dPos=0; dPos<(i3c_dport_q_entries-2); dPos++){
                    if(dPos < dataQEntries) {
      			        wrdata[2] = I3C_REG_READ(addr+(dPos*4));
              			I3C_REG_WRITE(wrdata[2], I3CS_TX_DATA_PORT);
                    } else {
              			I3C_REG_WRITE(0, I3CS_TX_DATA_PORT);
                    }
                }

		    }
            break;
            case D2D_OPCODE:
    		{
                d2d_status = rddata[1];
                no_gpio_toggle = 1;
    		}
            break;
            case FW_DOWNLOAD_COMPLETE_OPCODE:
		    {
#ifdef BOOTROM_MODE
                debug_gpio_set(0x6);
#endif
                jumpToTIM = rddata[1];
                no_gpio_toggle = 1;
		    }
            break;
        }
		queue_level = (I3C_REG_READ(I3CS_QUEUE_STATUS_LEVEL)>>0x8) & 0xFF;
		while(queue_level != 0)
		{
			queue_level--;
			I3C_REG_READ(I3CS_RESPONSE_QUEUE_PORT);
		}

		I3C_REG_WRITE((0x1<<6),I3CS_INTR_STATUS);
		tid++;
	}

  //  metal_interrupt_clear(sInterrupt,I3C_INTERRUPT_ID);

	if(((intr_status >> 8) & 0x1) || ((intr_status >> 0x1) & 0x1))
	{
        if(!no_gpio_toggle) {
            toggle_i3c_ready();
        }
    }
#ifdef BOOTROM_MODE
    debug_gpio_set(0x3);
#endif

}

int32_t i3c_slave_send_fw_dnld_resp(void){
    uint32_t dEnt;
    uint32_t i3c_dport_q_entries;
    transmit_command = 0;
    transmit_cmd(TTC_CMD_ATR, 0x0);
    transmit_cmd(TTC_TID, 0x0&0x7);
    transmit_cmd(TTC_DATA_LENGTH, (i3c_dport_q_entries * 4));
    I3C_REG_WRITE(transmit_command, I3CS_COMMAND_QUEUE_PORT);
    transmit_command = 0;

    I3C_REG_WRITE(FW_DOWNLOAD_COMPLETE_RESP_OPCODE, I3CS_TX_DATA_PORT);
    for (dEnt=0; dEnt<(i3c_dport_q_entries-1);dEnt++) {
        I3C_REG_WRITE(0x0, I3CS_TX_DATA_PORT);
    }

    toggle_i3c_ready();
}

int32_t i3c_slave_send_d2d_resp(uint32_t d2d_status) {
    uint32_t dEnt;
    uint32_t i3c_dport_q_entries;
    transmit_command = 0;
    transmit_cmd(TTC_CMD_ATR, 0x0);
    transmit_cmd(TTC_TID, 0x0&0x7);
    transmit_cmd(TTC_DATA_LENGTH, (i3c_dport_q_entries * 4));
    I3C_REG_WRITE(transmit_command, I3CS_COMMAND_QUEUE_PORT);
    transmit_command = 0;

    I3C_REG_WRITE(D2D_OPCODE, I3CS_TX_DATA_PORT);
    I3C_REG_WRITE(d2d_status, I3CS_TX_DATA_PORT);
    for (dEnt=0; dEnt<(i3c_dport_q_entries-2);dEnt++) {
        I3C_REG_WRITE(0x0, I3CS_TX_DATA_PORT);
    }

    toggle_i3c_ready();
}

//slave initialization 
int32_t i3c_slave_init(void)
{
#ifdef BOOTROM_MODE
	uint8_t i3c_address = 0;
    uint32_t dEnt = 0;
	u_i3cs_device_addr 		device_addr = {0};
	u_i3cs_slv_mipi_id_value	mipi_id_value = {0};
	u_i3cs_slv_pid_value 		pid_value = {0};
	u_i3cs_max_data_speed 		max_data_speed = {0};
	u_i3cs_slv_char_ctrl 		char_ctrl = {0};
	u_i3cs_queue_thld_ctrl 		queue_thld_ctrl = {0};
	u_i3cs_data_buffer_thld_ctrl 	data_buffer_thld_ctrl = {0};
	u_i3cs_bus_free_avail_timing 	bus_free_avail_timing = {0};
	u_i3cs_bus_idle_timing 		bus_idle_timing = {0};
#endif	
	u_i3cs_device_ctrl 		device_ctrl = {0};
	u_i3cs_intr_status_en 		intr_status_en = {0};
	u_i3cs_intr_signal_en 		intr_signal_en = {0};

#ifdef BOOTROM_MODE
	if(get_i3c_address(&i3c_address) != TEST_SUCCESS) {
		return 1;
	}
#endif	
//	s_cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if (s_cpu == NULL) {
	     return 2;
	}
	
	//s_cpu_intr = metal_cpu_interrupt_controller(s_cpu);
	if (s_cpu_intr == NULL) {
	     //printf("Cpu interrupt controller failed");
	     return 3;
	}
	
//	metal_interrupt_init(s_cpu_intr);
	
//	sInterrupt = metal_interrupt_get_controller(METAL_CLIC_CONTROLLER,metal_cpu_get_current_hartid());
	if(sInterrupt == NULL) {
		//printf("Get interrupt controller failed");
	}
	
//	metal_interrupt_init(sInterrupt);
/*	
	if(metal_interrupt_set_vector_mode(sInterrupt, METAL_SELECTIVE_VECTOR_MODE) != 0) {
		//printf("Set interrupt vector mode failed");
		return 4;
	}
	
	if(metal_interrupt_register_vector_handler(sInterrupt,I3C_INTERRUPT_ID,&i3c_slave_interrupt_handler,NULL) != 0) {
		//printf("Set interrupt register handler failed");
		return 5;
	}
*/	
xPortInstallInterruptHandler(I3C_INTERRUPT_ID, (Xil_ExceptionHandler)&i3c_slave_interrupt_handler, NULL);
        vPortEnableInterrupt(I3C_INTERRUPT_ID);
#ifdef BOOTROM_MODE
	device_addr.val = 0x00378026; // We're not using static address and dynamic address is set master. This programming is irrelevant
	I3C_REG_WRITE(device_addr.val, I3CS_DEVICE_ADDR_ADDR);

	mipi_id_value.slv_mipi_mfg_id = I3C_MIPI_MID;
	I3C_REG_WRITE(mipi_id_value.val, I3CS_SLV_MIPI_ID_VALUE);

	max_data_speed.mxds_max_wr_speed = 0x5;
	max_data_speed.mxds_max_rd_speed = 0x4;
	max_data_speed.mxds_clk_data_turn = 0x7;
	I3C_REG_WRITE(max_data_speed.val, I3CS_MAX_DATA_SPEED);
	
	pid_value.slv_part_id = 0x1;
	pid_value.slv_pid_dcr = 0xc6;
	pid_value.slv_inst_id = i3c_address;	
	I3C_REG_WRITE(pid_value.val, I3CS_SLV_PID_VALUE);
	
	char_ctrl.max_speed_data_limit = 0x1;
	char_ctrl.dcr = 0x4e;
	I3C_REG_WRITE(char_ctrl.val, I3CS_SLV_CHAR_CTRL);
	
	queue_thld_ctrl.cmd_empty_buf_thld = 0x6;
	queue_thld_ctrl.resp_buf_thld = 0x1; // Two responses per command will be present
	I3C_REG_WRITE(queue_thld_ctrl.val, I3CS_QUEUE_THLD_CTRL);

	// Confirm on RX_START_THLD value(1/4)	
	// RX_START_THLD = 1, RX_BUF_THLD = 1, TX_EMPTY_BUF_THLD = 0x3;
    dEnt = 0;while (!((i3c_dport_q_entries >> (dEnt + 1)) & 0x1)){dEnt++;}
	data_buffer_thld_ctrl.rx_start_thld = 0x1;
	data_buffer_thld_ctrl.rx_buf_thld = (dEnt&0x7);
	data_buffer_thld_ctrl.tx_empty_buf_thld = 0x3;
	I3C_REG_WRITE(data_buffer_thld_ctrl.val, I3CS_DATA_BUFFER_THLD_CTRL);

	// Why 32bit value? Only 31:16 is valid. wrdata = 0x015300be;   //
	bus_free_avail_timing.bus_available_time = 0xbe;
	I3C_REG_WRITE(bus_free_avail_timing.val, I3CS_BUS_FREE_AVAIL_TIMING);
	
	bus_idle_timing.bus_idle_time = 0x17672; 
	I3C_REG_WRITE(bus_idle_timing.val, I3CS_BUS_IDLE_TIMING);

	intr_status_en.tx_thld_sts_en = 0x0;
	intr_status_en.rx_thld_sts_en = 0x1;
	intr_status_en.cmd_queue_ready_sts_en = 0x0;
	intr_status_en.resp_ready_sts_en = 0x1;
	intr_status_en.ccc_updated_sts_en = 0x1;
	intr_status_en.dyn_addr_assgn_sts_en = 0x1;
	intr_status_en.transfer_err_sts_en = 0x1;
	intr_status_en.read_req_recv_sts_en = 0x1;
	I3C_REG_WRITE(intr_status_en.val, I3CS_INTR_STATUS_EN);
	
	intr_signal_en.tx_thld_status_en = 0x0;
	intr_signal_en.rx_thld_status_en = 0x1;
	intr_signal_en.cmd_queue_ready_status_en = 0x0;
	intr_signal_en.resp_ready_status_en = 0x1;
	intr_signal_en.ccc_updated_status_en = 0x1;
	intr_signal_en.dyn_addr_assgn_status_en = 0x1;
	intr_signal_en.transfer_err_status_en = 0x1;
	intr_signal_en.read_req_recv_status_en = 0x1;
	I3C_REG_WRITE(intr_signal_en.val, I3CS_INTR_SIGNAL_EN);
	
	device_ctrl.enable = 0x1;
	I3C_REG_WRITE(device_ctrl.val,I3CS_DEVICE_CTRL );

	if(metal_interrupt_enable(sInterrupt,I3C_INTERRUPT_ID) != 0) {
		//printf("Set interrupt vector enable failed");
		return 6;
	}

	if(set_i3c_ready() != TEST_SUCCESS) {
		return 7;
	}

	if (metal_interrupt_enable(s_cpu_intr, 0) != 0) {
	    	// printf("CPU interrupt enable failed");
	    	return 8;
	}

#else /* !BOOTROM_MODE */
	intr_status_en.tx_thld_sts_en = 0x0;
	intr_status_en.rx_thld_sts_en = 0x1;
	intr_status_en.cmd_queue_ready_sts_en = 0x0;
	intr_status_en.resp_ready_sts_en = 0x1;
	intr_status_en.ccc_updated_sts_en = 0x1;
	intr_status_en.dyn_addr_assgn_sts_en = 0x1;
	intr_status_en.transfer_err_sts_en = 0x1;
	intr_status_en.read_req_recv_sts_en = 0x1;
	I3C_REG_WRITE(intr_status_en.val, I3CS_INTR_STATUS_EN);
	
	intr_signal_en.tx_thld_status_en = 0x0;
	intr_signal_en.rx_thld_status_en = 0x1;
	intr_signal_en.cmd_queue_ready_status_en = 0x0;
	intr_signal_en.resp_ready_status_en = 0x1;
	intr_signal_en.ccc_updated_status_en = 0x1;
	intr_signal_en.dyn_addr_assgn_status_en = 0x1;
	intr_signal_en.transfer_err_status_en = 0x1;
	intr_signal_en.read_req_recv_status_en = 0x1;
	I3C_REG_WRITE(intr_signal_en.val, I3CS_INTR_SIGNAL_EN);
	
	device_ctrl.enable = 0x1;
	I3C_REG_WRITE(device_ctrl.val,I3CS_DEVICE_CTRL );
/*
	if(metal_interrupt_enable(sInterrupt,I3C_INTERRUPT_ID) != 0) {
		//printf("Set interrupt vector enable failed");
		return 6;
	}

	if (metal_interrupt_enable(s_cpu_intr, 0) != 0) {
	    	// printf("CPU interrupt enable failed");
	    	return 7;
	}
*/
#endif /* !BOOTROM_MODE */

#ifdef BOOTROM_MODE
	debug_gpio_set(0x3);
	while(!jumpToTIM)
	{
		__asm__ volatile ("nop");
	}

	I3C_REG_WRITE(0x0, I3CS_INTR_STATUS_EN);
	I3C_REG_WRITE(0x0, I3CS_INTR_SIGNAL_EN);
    metal_interrupt_disable(sInterrupt, I3C_INTERRUPT_ID);
    metal_interrupt_disable(s_cpu_intr, I3C_INTERRUPT_ID);
    metal_interrupt_disable(s_cpu_intr, METAL_INTERRUPT_ID_BASE);
	//Jump execution to TIM
	void (*jump_to_TIM_address)(void) = (void (*)())jumpToTIM;
	jump_to_TIM_address();
#endif

	return 0;
}
