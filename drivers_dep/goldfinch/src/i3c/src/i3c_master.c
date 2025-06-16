#include <riscv_cpu.h>
#include "i3c.h"
#include "i3cm_reg.h"
#include "cpu.h"

#include "xil_exception.h"                 // for Xil_ExceptionHandler
#include "FreeRTOS.h"
#include "portmacro.h"
 uint32_t transfer_command = 0;
 uint32_t transfer_argument = 0;
 uint32_t short_data_argument = 0;
 uint32_t address_assignment_command = 0;


struct metal_interrupt* mInterrupt;
struct metal_interrupt *m_cpu_intr;
struct metal_cpu *m_cpu;

/* code generalised for modifying BUF 
 * threshold with i3c_dport_q_entries */
uint32_t i3c_dport_q_entries = 4;

void map_devIndx_to_DA(struct slave_table (*gfh_slave_table)[])
{
	uint32_t slave_pid;

    switch(I3C_NUM_SLAVE_DEVICES) {
        case 0x4:
        {
	    (*gfh_slave_table)[3].gfh_inst = 0x3;
	    slave_pid = I3C_REG_READ(I3CM_DEV_CHAR_TABLE4_LOC2);
        (*gfh_slave_table)[3].dev_index = (slave_pid >> 12) & 0xf;
        }
        case 0x3:
        {
    	(*gfh_slave_table)[2].gfh_inst = 0x2;
	    slave_pid = I3C_REG_READ(I3CM_DEV_CHAR_TABLE3_LOC2);
        (*gfh_slave_table)[2].dev_index = (slave_pid >> 12) & 0xf;
        }
        case 0x2:
        {
	    (*gfh_slave_table)[1].gfh_inst = 0x1;
	    slave_pid = I3C_REG_READ(I3CM_DEV_CHAR_TABLE2_LOC2);
        (*gfh_slave_table)[1].dev_index = (slave_pid >> 12) & 0xf;
        }
        case 0x1:
        {
	    (*gfh_slave_table)[0].gfh_inst = 0x0;
	    slave_pid = I3C_REG_READ(I3CM_DEV_CHAR_TABLE1_LOC2);
        (*gfh_slave_table)[0].dev_index = (slave_pid >> 12) & 0xf;
        }
    }
}

void i3c_master_interrupt_handler(void) 
{
	u_i3cm_intr_status intr_status;

	intr_status.val = I3C_REG_READ(I3CM_INTR_STATUS);
	// Bit[9] TRANSFER_ERR_STS -- we should probably report if there is an error but this is low priority for now (can add later); clear required
	if(intr_status.transfer_err_sts)
	{
		I3C_REG_WRITE((0x1<<9),I3CM_INTR_STATUS);
	}
	// Bit[5] TRANSFER_ABORT_STS - Report and clear
	if(intr_status.transfer_abort_sts)
	{
		I3C_REG_WRITE((0x1<<5),I3CM_INTR_STATUS);
	}
	//Bit[1] RX_THLD_STS - triggers when there is RX data in buffer to process; needs a function to process the data from slave(GFH)
	if(intr_status.rx_thld_sts)
	{
		//TODO: Implement handler
	}

//	metal_interrupt_clear(mInterrupt,I3C_INTERRUPT_ID);
 
}
int32_t i3c_master_init()
{
	uint32_t rddata;
    uint32_t dEnt = 0;
	

	
	I3C_REG_WRITE(0x0000040a, I3CM_QUEUE_THLD_CTRL);
    dEnt = 0;while (!((i3c_dport_q_entries >> (dEnt + 1)) & 0x1)){dEnt++;}
	I3C_REG_WRITE((((0x02010002) & ~(0x7<<8)) | ((dEnt &0x7) << 8)),
                    I3CM_DATA_BUFFER_THLD_CTRL);
	I3C_REG_WRITE(0x00000000, I3CM_DEVICE_CTRL_EXTENDED);
	I3C_REG_WRITE(0x00000236, I3CM_INTR_STATUS_EN);
	//I3C_REG_WRITE(0x00000236, I3CM_INTR_SIGNAL_EN );
	I3C_REG_WRITE(0x80550000, I3CM_DEVICE_ADDR_ADDR);
	I3C_REG_WRITE(0x000a0028, I3CM_SCL_I3C_OD_TIMING);
	I3C_REG_WRITE(0x00080008, I3CM_SCL_I3C_PP_TIMING);
	I3C_REG_WRITE(0x00e8017a, I3CM_SCL_I2C_FM_TIMING );
	I3C_REG_WRITE(0x00ff00f6, I3CM_SCL_I2C_FMP_TIMING);
	I3C_REG_WRITE(0x5c091f11, I3CM_SCL_EXT_LCNT_TIMING);
	I3C_REG_WRITE(0x30000003, I3CM_SCL_EXT_TERMN_LCNT_TIMING);
	I3C_REG_WRITE(0x00050000, I3CM_SDA_HOLD_SWITCH_DLY_TIMING);
	I3C_REG_WRITE(0x00000016, I3CM_BUS_FREE_AVAIL_TIMING);
	I3C_REG_WRITE(0x00000055, I3CM_BUS_IDLE_TIMING);
	I3C_REG_WRITE(0x80000001, I3CM_DEVICE_CTRL);
	if(I3C_NUM_SLAVE_DEVICES > 0)
		I3C_REG_WRITE(0x60d50050, I3CM_DEV_ADDR_TABLE_LOC1 ); // DYN_ADDR = 55 DEV_INDEX 0
	if(I3C_NUM_SLAVE_DEVICES > 1)
		I3C_REG_WRITE(0x60a20051, I3CM_DEV_ADDR_TABLE_LOC2 ); // DYN_ADDR = 22 DEV_INDEX 1
	if(I3C_NUM_SLAVE_DEVICES > 2)
		I3C_REG_WRITE(0x60c40052, I3CM_DEV_ADDR_TABLE_LOC3 ); // DYN_ADDR = 44 DEV_INDEX 2
	if(I3C_NUM_SLAVE_DEVICES > 3)
		I3C_REG_WRITE(0x60e60053, I3CM_DEV_ADDR_TABLE_LOC4 ); // DYN_ADDR = 66 DEV_INDEX 3

 	xPortInstallInterruptHandler(I3C_INTERRUPT_ID, (Xil_ExceptionHandler)&i3c_master_interrupt_handler, NULL);
        vPortEnableInterrupt(I3C_INTERRUPT_ID);
    return 0;	 
}

void i3c_master_assign_address()
{
  	uint32_t rddata;
  	uint32_t wrdata;

  	//cmd_atr=3, dev_count=1, ROC=1, TOC=0
  	address_assignment_command=0;
  	add_asgn_cmd(AAC_CMD_ATR,3);
  	add_asgn_cmd(AAC_CMD,7);
  	add_asgn_cmd(AAC_TID,8);
  	add_asgn_cmd(AAC_RSVD,0);
  	add_asgn_cmd(AAC_DEV_COUNT,I3C_NUM_SLAVE_DEVICES);
  	add_asgn_cmd(AAC_ROC,1);
  	add_asgn_cmd(AAC_TOC,0);
  	I3C_REG_WRITE(address_assignment_command, I3CM_COMMAND_QUEUE_PORT);
  	address_assignment_command=0;

	for (uint8_t i=0; i<=20;i++) {
		rddata = readl(I3CM_RESPONSE_QUEUE_PORT);
		rddata = readl(I3CM_QUEUE_STATUS_LEVEL);
		rddata = readl(I3CM_INTR_STATUS);
		rddata = readl(I3CM_PRESENT_STATE);
	}

  	// Resume
  	I3C_REG_WRITE(0xc0000001, I3CM_DEVICE_CTRL);

  	//cmd_atr=3, dev_count=1, ROC=1, TOC=0
  	address_assignment_command=0;
  	add_asgn_cmd(AAC_CMD_ATR,3);
  	add_asgn_cmd(AAC_CMD,7);
  	add_asgn_cmd(AAC_TID,8);
  	add_asgn_cmd(AAC_RSVD,0);
  	add_asgn_cmd(AAC_DEV_COUNT,I3C_NUM_SLAVE_DEVICES);
  	add_asgn_cmd(AAC_ROC,1);
  	add_asgn_cmd(AAC_TOC,0);
  	I3C_REG_WRITE(address_assignment_command, I3CM_COMMAND_QUEUE_PORT);
  	address_assignment_command=0;

}

//This is for Private read command for response
int32_t i3c_private_read(uint8_t dev_index, I3C_CMD *pI3cCmd)
{
	uint32_t status;
    uint32_t dEnt = 0;
    uint32_t dataRdEntries;
    uint32_t dataQEntries;
    uint32_t dPos, dataLen, tmpData, tmpData1;

    if (pI3cCmd == NULL)
        return -1;

    if (pI3cCmd->pData == NULL)
        return -2;

    //dataRdEntries = ((pI3cCmd->opCode & I3C_DATALEN_MASK) >> I3C_DATALEN_POS)/4;
    /* Read buffer size */
    dataLen = (pI3cCmd->opCode & I3C_DATALEN_MASK) >> I3C_DATALEN_POS;

    dataQEntries = dataLen/4;

    /* Config DATA BUFFER THLD */
    dEnt = 0;while (!((i3c_dport_q_entries >> (dEnt + 1)) & 0x1)){dEnt++;}
	I3C_REG_WRITE((((0x02010002) & ~(0x7<<8)) | ((dEnt &0x7) << 8)), I3CM_DATA_BUFFER_THLD_CTRL );

	transfer_arg(TA_CMD_ATR,1);
	transfer_arg(TA_DATA_LENGTH, i3c_dport_q_entries * 4);
	transfer_arg(TA_DB, 0x2d);
	I3C_REG_WRITE(transfer_argument, I3CM_COMMAND_QUEUE_PORT);
	transfer_argument = 0;

	transfer_command = 0;
	transfer_cmd(TC_CMD_ATR,0);
	transfer_cmd(TC_TID, dev_index);
	transfer_cmd(TC_CMD, 0x7f);
	transfer_cmd(TC_CP, 0); // Why is CP = 0x0 when CMD = 0x7F
	transfer_cmd(TC_DEV_INDX, dev_index);
	transfer_cmd(TC_SPEED, 1);
	transfer_cmd(TC_RnW, 1);
	transfer_cmd(TC_ROC, 1);
	transfer_cmd(TC_TOC, 1);
	I3C_REG_WRITE(transfer_command, I3CM_COMMAND_QUEUE_PORT);
	transfer_command = 0;

	if(((I3C_REG_READ(I3CM_QUEUE_STATUS_LEVEL)>>0x8) & 0xFF) != 0)
	{
		// Read response queue port -- Confirms master transfer
		status = I3C_REG_READ(I3CM_RESPONSE_QUEUE_PORT);
	}

	//Wait until the RX_THLD_STS is high
	while(!((I3C_REG_READ(I3CM_INTR_STATUS) >> 0x1) & 0x1));
	pI3cCmd->opCode = I3C_REG_READ(I3CM_RX_DATA_PORT);
	pI3cCmd->data0 = I3C_REG_READ(I3CM_RX_DATA_PORT);
    /* read configured dataQEntries but update only
	 * to the size of given buffer */
	for (dPos = 0; dPos < (i3c_dport_q_entries-2); dPos++) {
        if (dPos < dataQEntries) {
        	pI3cCmd->pData[dPos] = I3C_REG_READ(I3CM_RX_DATA_PORT);
        } else {
        	tmpData = I3C_REG_READ(I3CM_RX_DATA_PORT);
        }
    }

	return 0;
}

int32_t i3c_master_write(struct slave_table *pGfh, uint32_t address, uint32_t *pData, uint32_t dataLen)
{
	uint32_t status;
	uint32_t response[4] = {0x0};
	uint8_t gpio_val;
    uint32_t dPos, dEntries;
    uint32_t wDataEntries = i3c_dport_q_entries;
    uint32_t dEnt = 0;
    I3C_CMD i3c_cmd;
    
    if (pData == NULL || pGfh == NULL) {
        return -1;
    }

	gpio_val = get_i3c_ready(pGfh->gfh_inst);

    dEntries = dataLen/4;
    i3c_cmd.opCode = ((WRITE_REGISTER_OPCODE & I3C_OPCODE_MASK) |
                    ((dataLen << I3C_DATALEN_POS)&I3C_DATALEN_MASK));
    i3c_cmd.data0 = address;
    i3c_cmd.pData = pData;

	I3C_REG_WRITE(i3c_cmd.opCode, I3CM_TX_DATA_PORT);
	I3C_REG_WRITE(i3c_cmd.data0, I3CM_TX_DATA_PORT);
    for (dPos = 0; dPos < (i3c_dport_q_entries-2); dPos++) {
        if(dPos < dEntries) {
        	I3C_REG_WRITE(pData[dPos], I3CM_TX_DATA_PORT);
        } else {
            I3C_REG_WRITE(0x0, I3CM_TX_DATA_PORT); //RSVD
        }
    }
    if (dEntries > (i3c_dport_q_entries-2)) {
        wDataEntries = I3C_RX_BUF_MAX;
        for (;dPos<(I3C_RX_BUF_MAX-(i3c_dport_q_entries-2));dPos++){
            if(dPos < dEntries) {
            	I3C_REG_WRITE(pData[dPos], I3CM_TX_DATA_PORT);
            } else {
                I3C_REG_WRITE(0x0, I3CM_TX_DATA_PORT); //RSVD
            }
        }
    }

    /* configure DAT BUFFER THLD */
    dEnt = 0;while (!((wDataEntries>>(dEnt + 1)) & 0x1)){dEnt++;}
	I3C_REG_WRITE((((0x02010002) & ~(0x7<<8)) | ((dEnt &0x7) << 8)), I3CM_DATA_BUFFER_THLD_CTRL );
	transfer_argument = 0;
	transfer_arg(TA_CMD_ATR,1);
	transfer_arg(TA_DATA_LENGTH, (wDataEntries*4));
	transfer_arg(TA_DB, 0x4d);
	I3C_REG_WRITE(transfer_argument, I3CM_COMMAND_QUEUE_PORT);
	transfer_argument = 0;

	transfer_command = 0;
	transfer_cmd(TC_CMD_ATR,0);
	transfer_cmd(TC_TID, pGfh->dev_index);
	transfer_cmd(TC_CMD, 0x20);
	transfer_cmd(TC_CP, 0); // Why is CP = 0x0 when CMD = 0x20
	transfer_cmd(TC_DEV_INDX, pGfh->dev_index);
	transfer_cmd(TC_SPEED, 1);
	transfer_cmd(TC_ROC, 1);
	transfer_cmd(TC_TOC, 1);
	I3C_REG_WRITE(transfer_command, I3CM_COMMAND_QUEUE_PORT);
	transfer_command = 0;

	if(((I3C_REG_READ(I3CM_QUEUE_STATUS_LEVEL)>>0x8) & 0xFF) != 0)
	{
		// Read response queue port -- Confirms master transfer
		status = I3C_REG_READ(I3CM_RESPONSE_QUEUE_PORT);
		//if(((status >> 24) & 0xF != pGfh->dev_index) || ((status >> 28 & 0xF != 0x0)))
		//	return -1;
	}

	// Wait for GPIO toggle
	while((gpio_val^0x1) != get_i3c_ready(pGfh->gfh_inst));

	if(i3c_private_read(pGfh->dev_index, &i3c_cmd) != 0)
		return -1;
	if((WRITE_REGISTER_RESPONSE_OPCODE != (i3c_cmd.opCode & I3C_OPCODE_MASK)))
		return -1;

	return 0;
}

int32_t i3c_master_read(struct slave_table *pGfh,uint32_t address, uint32_t * pData, uint32_t dataLen)
{
	uint32_t status;
	uint8_t gpio_val;
	uint32_t response[4] = {0x0};
    uint32_t dPos, dEntries;
    I3C_CMD i3c_cmd;

    if (dataLen > ((i3c_dport_q_entries-2)*4) || (dataLen%4)){
        return -1;
    }

    if (pData == NULL || pGfh == NULL)
        return -1;

	gpio_val = get_i3c_ready(pGfh->gfh_inst);

    dEntries = dataLen/4;
    i3c_cmd.opCode = (READ_REGISTER_OPCODE | ((dataLen<<I3C_DATALEN_POS)&I3C_DATALEN_MASK));
    i3c_cmd.data0 = address;
    i3c_cmd.pData = pData;

	I3C_REG_WRITE(i3c_cmd.opCode, I3CM_TX_DATA_PORT);
	I3C_REG_WRITE(i3c_cmd.data0, I3CM_TX_DATA_PORT);

    for (dPos = 0; dPos < (i3c_dport_q_entries-2); dPos++) {
    	I3C_REG_WRITE(0x0, I3CM_TX_DATA_PORT);
    }

	transfer_argument = 0;
	transfer_arg(TA_CMD_ATR,1);
	transfer_arg(TA_DATA_LENGTH, i3c_dport_q_entries * 4);
	transfer_arg(TA_DB, 0x4d);
	I3C_REG_WRITE(transfer_argument, I3CM_COMMAND_QUEUE_PORT);
	transfer_argument = 0;

	transfer_command = 0;
	transfer_cmd(TC_CMD_ATR,0);
	transfer_cmd(TC_TID, pGfh->dev_index);
	transfer_cmd(TC_CMD, 0x20);
	transfer_cmd(TC_CP, 0);
	transfer_cmd(TC_DEV_INDX, pGfh->dev_index);
	transfer_cmd(TC_SPEED, 1);
	transfer_cmd(TC_ROC, 1);
	transfer_cmd(TC_TOC, 1);
	I3C_REG_WRITE(transfer_command, I3CM_COMMAND_QUEUE_PORT);
	transfer_command = 0;

	if(((I3C_REG_READ(I3CM_QUEUE_STATUS_LEVEL)>>0x8) & 0xFF) != 0)
	{
		// Read response queue port -- Confirms master transfer
		status = I3C_REG_READ(I3CM_RESPONSE_QUEUE_PORT);
		//if(((status >> 24) & 0xF != pGfh->dev_index) || ((status >> 28 & 0xF != 0x0)))
		//	return -1;
	}

	// Wait for the gpio toggle
	while((gpio_val^0x1) != get_i3c_ready(pGfh->gfh_inst));
	
	// Read the response from Slave  -- Confirms slave handshake
	if( 0 != i3c_private_read(pGfh->dev_index, &i3c_cmd))
			return -1;
	if((READ_REGISTER_RESPONSE_OPCODE != (i3c_cmd.opCode & I3C_OPCODE_MASK)))
		return -1;

	return 0;
}

int32_t i3c_master_copy_data(struct slave_table *pGfh, uint32_t sAddr, uint32_t dAddr, uint32_t length){
    uint32_t copied_len = 0, dPos;
    uint32_t data[I3C_RX_BUF_MAX-2];

    if (pGfh == NULL) {
        return -1;
    }

    while (copied_len < length) {
        uint32_t dLen = 0;
        dLen = length - copied_len;
        for (dPos=0; dPos < (I3C_RX_BUF_MAX-2);dPos++) {
            if ((copied_len + dPos*4) < length) {
                data[dPos] = readl((sAddr + copied_len + dPos*4));
            } else {
                data[dPos] = 0;
            }
        }
        if ((length - copied_len) > ((I3C_RX_BUF_MAX-2)*4)) {
            dLen = (I3C_RX_BUF_MAX-2)*4;
        }
        i3c_master_write(pGfh, dAddr+copied_len, data, dLen);
        copied_len += dLen;

    }
    
}

int32_t i3c_master_send_jump_to_tim(struct slave_table *pGfh, uint32_t address)
{
	uint32_t status, dPos;
	uint8_t gpio_val;
    I3C_CMD i3c_cmd;
    uint32_t data[i3c_dport_q_entries-2];

    if (pGfh == NULL) {
        return -1;
    }

    i3c_cmd.opCode = ((FW_DOWNLOAD_COMPLETE_OPCODE & I3C_OPCODE_MASK) |
                    (((0x0 << I3C_DATALEN_POS)&I3C_DATALEN_MASK)));
    i3c_cmd.pData = data;

	gpio_val = get_i3c_ready(pGfh->gfh_inst);

	I3C_REG_WRITE(i3c_cmd.opCode, I3CM_TX_DATA_PORT);
	I3C_REG_WRITE(address, I3CM_TX_DATA_PORT);

    for (dPos = 0; dPos < (i3c_dport_q_entries-2); dPos++) {
        I3C_REG_WRITE(i3c_cmd.pData[dPos], I3CM_TX_DATA_PORT);
    }

	transfer_argument = 0;
	transfer_arg(TA_CMD_ATR,1);
	transfer_arg(TA_DATA_LENGTH, (i3c_dport_q_entries)*4);
	transfer_arg(TA_DB, 0x4d);
	I3C_REG_WRITE(transfer_argument, I3CM_COMMAND_QUEUE_PORT);
	transfer_argument = 0;

	transfer_command = 0;
	transfer_cmd(TC_CMD_ATR,0);
	transfer_cmd(TC_TID, pGfh->dev_index);
	transfer_cmd(TC_CMD, 0x20);
	transfer_cmd(TC_CP, 0); // Why is CP = 0x0 when CMD = 0x20
	transfer_cmd(TC_DEV_INDX, pGfh->dev_index);
	transfer_cmd(TC_SPEED, 1);
	transfer_cmd(TC_ROC, 0);
	transfer_cmd(TC_TOC, 1);
	I3C_REG_WRITE(transfer_command, I3CM_COMMAND_QUEUE_PORT);
	transfer_command = 0;

	if(((I3C_REG_READ(I3CM_QUEUE_STATUS_LEVEL)>>0x8) & 0xFF) != 0)
	{
		// Read response queue port -- Confirms master transfer
		status = I3C_REG_READ(I3CM_RESPONSE_QUEUE_PORT);
		//if(((status >> 24) & 0xF != pGfh->dev_index) || ((status >> 28 & 0xF != 0x0)))
		//	return -1;
	}

	// Wait for GPIO toggle
	while((gpio_val^0x1) != get_i3c_ready(pGfh->gfh_inst));
	
	// Read the response from Slave  -- Confirms slave handshake
	if( 0 != i3c_private_read(pGfh->dev_index, &i3c_cmd))
			return -1;
	if((FW_DOWNLOAD_COMPLETE_RESP_OPCODE != (i3c_cmd.opCode & I3C_OPCODE_MASK)))
		return -1;

	return 0;
}

int32_t i3c_master_send_d2d_status(struct slave_table *pGfh, uint32_t d2d_mode) {
	uint32_t status;
	uint8_t gpio_val, dPos = 0;
    I3C_CMD i3c_cmd;
    uint32_t data[i3c_dport_q_entries-2];

    if (pGfh == NULL) {
        return -1;
    }

    i3c_cmd.opCode = ((D2D_OPCODE & I3C_OPCODE_MASK) |
                    (((0x0 << I3C_DATALEN_POS)&I3C_DATALEN_MASK)));
    i3c_cmd.pData = data;

	gpio_val = get_i3c_ready(pGfh->gfh_inst);

	I3C_REG_WRITE(i3c_cmd.opCode, I3CM_TX_DATA_PORT);
	I3C_REG_WRITE(d2d_mode, I3CM_TX_DATA_PORT);

    for (dPos = 0; dPos < (i3c_dport_q_entries-2); dPos++) {
        I3C_REG_WRITE(i3c_cmd.pData[dPos], I3CM_TX_DATA_PORT);
    }

	transfer_argument = 0;
	transfer_arg(TA_CMD_ATR,1);
	transfer_arg(TA_DATA_LENGTH,(i3c_dport_q_entries)*4);
	transfer_arg(TA_DB, 0x4d);
	I3C_REG_WRITE(transfer_argument, I3CM_COMMAND_QUEUE_PORT);
	transfer_argument = 0;

	transfer_command = 0;
	transfer_cmd(TC_CMD_ATR,0);
	transfer_cmd(TC_TID, pGfh->dev_index);
	transfer_cmd(TC_CMD, 0x20);
	transfer_cmd(TC_CP, 0); // Why is CP = 0x0 when CMD = 0x20
	transfer_cmd(TC_DEV_INDX, pGfh->dev_index);
	transfer_cmd(TC_SPEED, 1);
	transfer_cmd(TC_ROC, 1);
	transfer_cmd(TC_TOC, 1);
	I3C_REG_WRITE(transfer_command, I3CM_COMMAND_QUEUE_PORT);
	transfer_command = 0;

	if(((I3C_REG_READ(I3CM_QUEUE_STATUS_LEVEL)>>0x8) & 0xFF) != 0)
	{
		// Read response queue port -- Confirms master transfer
		status = I3C_REG_READ(I3CM_RESPONSE_QUEUE_PORT);
		//if(((status >> 24) & 0xF != pGfh->dev_index) || ((status >> 28 & 0xF != 0x0)))
		//	return -1;
	}

	// Wait for GPIO toggle
	while((gpio_val^0x1) != get_i3c_ready(pGfh->gfh_inst));

	// Read the response from Slave  -- Confirms slave handshake
	if( 0 != i3c_private_read(pGfh->dev_index, &i3c_cmd))
			return -1;
	if((D2D_RESP_OPCODE != (i3c_cmd.opCode & I3C_OPCODE_MASK)))
		return -1;

	return 0;
}

