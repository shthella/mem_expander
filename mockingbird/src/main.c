#include <stdio.h>
#include "uart.h"
#define I3C_EN
#define D2D_EN
#undef I3C_COPY_EN

#include <gpio.h>
#include <interrupt.h>
#include <riscv_cpu.h>
#include <flash_mem_layout.h>
#include <spi_common.h>

#ifdef I3C_EN
#include "i3c.h"
#endif /* I3C_EN */

#ifdef D2D_EN
#include "d2d.h"
#endif /* D2D_EN */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "stack_macros.h"
#include "xil_exception.h"

#define GFH1_I3C_SLAVE 0
#define GFH2_I3C_SLAVE 1
#define GFH3_I3C_SLAVE 2
#define GFH4_I3C_SLAVE 3

#define GFH1_I3C_SLAVE_READY 15
#define GFH2_I3C_SLAVE_READY 16
#define GFH3_I3C_SLAVE_READY 17
#define GFH4_I3C_SLAVE_READY 18

#define TIM0_ADDR   0x80000000
#define TIM1_ADDR   0x80020000
struct slave_table gfh_slave[I3C_NUM_SLAVE_DEVICES] = {0};
#ifdef D2D_EN
blynx_bow_t d2dPhy;
D2dLLRegBlock d2dLL;
#endif /* D2D_EN */


void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName ){}
void vApplicationMallocFailedHook( void ){}
void FreedomMetal_ExceptionHandler(void){}
void FreedomMetal_InterruptHandler(void){}

#define MKB_PLL_CNTRL_REG 0x26000100

void mkb_pll_enable(void){
      uint32_t val;
      val = readl(MKB_PLL_CNTRL_REG);
      val |= 0x1; // bit[0] = PLL enable
      writel(val, MKB_PLL_CNTRL_REG);
      do {
            val = readl(MKB_PLL_CNTRL_REG);
      } while((val & 0x40000000) != 0x40000000); // bit[30] = PLL locked goes high
}

int32_t master_fw_upload(struct slave_table *pGfh, uint32_t dAddr, uint32_t lableCode)
{
    uint32_t nodePos = 0, bufLen;
	uint8_t flashBlockInfo[sizeof(FlashBlockInfo)];
	uint8_t flashData[sizeof(FlashData)];
	FlashBlockInfo *pFlashBlockInfo;
	FlashData *pFlashData;

#if SKIP_FLASH_COPY
	qspi_mode_init();
#endif /* SKIP_FLASH_COPY */
	qspi_copy_data(0x0, flashBlockInfo, sizeof(flashBlockInfo));
    pFlashBlockInfo = (FlashBlockInfo *)flashBlockInfo;
	nodePos = 0;
    do {
        qspi_copy_data((uint8_t *)(pFlashBlockInfo->flashDataStart + (nodePos * sizeof(flashData))), flashData, sizeof(flashData));
        nodePos++;
        pFlashData = (FlashData *)flashData;
    }while(!pFlashData->isLastNode && pFlashData->labelCode != lableCode);
    if(pFlashData->labelCode != lableCode) {
	    return -1;
    }
    bufLen = pFlashData->len + ((pFlashData->len%4)?(4-(pFlashData->len%4)):0);

	qspi_data_transfer_handler((void *)pGfh, (void *)i3c_master_copy_data, pFlashData->sAddr, dAddr, bufLen);
}


int main() {
    uart_init();

#if 1	

	debug_gpio_set(0x7);	// DEBUG: Indicating TIM execution started
	/*********************** I3C ************************************/
	uint32_t data = 0x0;
	struct metal_gpio *gpio;

	// Enable PLL and wait for the lock
	mkb_pll_enable();

#ifdef I3C_EN

	i3c_master_init();

	if(I3C_NUM_SLAVE_DEVICES > 0)
		metal_gpio_enable_input(gpio, GFH1_I3C_SLAVE_READY);
	if(I3C_NUM_SLAVE_DEVICES > 1)
		metal_gpio_enable_input(gpio, GFH2_I3C_SLAVE_READY);
	if(I3C_NUM_SLAVE_DEVICES > 2)
		metal_gpio_enable_input(gpio, GFH3_I3C_SLAVE_READY);
	if(I3C_NUM_SLAVE_DEVICES > 3)
		metal_gpio_enable_input(gpio, GFH4_I3C_SLAVE_READY);


	//Wait until all the GFH slaves are ready.
	if(I3C_NUM_SLAVE_DEVICES > 0)
		while(!get_i3c_ready(GFH1_I3C_SLAVE));
	if(I3C_NUM_SLAVE_DEVICES > 1)
		while(!get_i3c_ready(GFH2_I3C_SLAVE));
	if(I3C_NUM_SLAVE_DEVICES > 2)
		while(!get_i3c_ready(GFH3_I3C_SLAVE));
	if(I3C_NUM_SLAVE_DEVICES > 3)
		while(!get_i3c_ready(GFH4_I3C_SLAVE));

	i3c_master_assign_address(); // Assigns dynamic address to 4 GFH chiplets
	// Wait until slave toggles the GPIOs to indicate DAA is done
	if(I3C_NUM_SLAVE_DEVICES > 0)
		while(get_i3c_ready(GFH1_I3C_SLAVE));
	if(I3C_NUM_SLAVE_DEVICES > 1)
		while(get_i3c_ready(GFH2_I3C_SLAVE));
	if(I3C_NUM_SLAVE_DEVICES > 2)
		while(get_i3c_ready(GFH3_I3C_SLAVE));
	if(I3C_NUM_SLAVE_DEVICES > 3)
		while(get_i3c_ready(GFH4_I3C_SLAVE));
	
	// Map DA to dev_index
	map_devIndx_to_DA(&gfh_slave);
#endif /* I3C_EN */

	/*********************** D2D ************************************/
    // Copy GFH fw to it's TIM
//	if(I3C_NUM_SLAVE_DEVICES > 0) {
#ifdef I3C_EN
#ifdef I3C_COPY_EN

        master_fw_upload(&gfh_slave[0], TIM1_ADDR, LC_GFH_D2D);
		i3c_master_send_jump_to_tim(&gfh_slave[0], TIM1_ADDR);
#else /* !I3C_COPY_EN direct jump to backdoor copied tim */
		i3c_master_send_jump_to_tim(&gfh_slave[0], TIM1_ADDR);
		
#endif /* !I3C_COPY_EN */

#ifdef D2D_EN   //This code is part of D2D will enable this along with D2D
	printf("%s function is running from mkb main\r\n" , __func__);
	    d2d_mode_init(&d2dPhy, &d2dLL);

		i3c_master_send_d2d_status(&gfh_slave[0], 0x1);
        d2d_set_rx_mode_train(&d2dPhy, &d2dLL);
		i3c_master_send_d2d_status(&gfh_slave[0], 0x2);
        d2d_set_tx_train_mode(&d2dPhy, &d2dLL);
        d2d_rx_train(&d2dPhy, &d2dLL);
        //d2d_skew_correction(); //DV suggested to remove/not required

		i3c_master_send_d2d_status(&gfh_slave[0], 0x3);
        d2d_set_tx_mode_idle(&d2dPhy, &d2dLL);
        d2d_poll_rx_for_tx_idle_mode(&d2dPhy, &d2dLL);
        d2d_set_rx_mode_wait(&d2dPhy, &d2dLL);
        
		i3c_master_send_d2d_status(&gfh_slave[0], 0x4);
        d2d_set_tx_mode_run(&d2dPhy, &d2dLL);
        d2d_poll_rx_mode_run(&d2dPhy, &d2dLL);

        /* TODO: TEST Writes, need to remove */
        writes(0xfeebeabd, 0x2f000000 + ((0x00050000 + 0)*4));
        writes(0xfeebeabd, 0x2f000000 + ((0x00050000 + 2)*4));

#endif /* D2D_EN */
#endif /* I3C_EN */
    //}

	if(I3C_NUM_SLAVE_DEVICES > 1) {
#ifdef I3C_EN
#ifdef I3C_COPY_EN
        master_fw_upload(&gfh_slave[1], TIM1_ADDR, LC_GFH_D2D);
		i3c_master_send_jump_to_tim(&gfh_slave[1], TIM1_ADDR);
#else /* !I3C_COPY_EN direct jump to backdoor copied tim */
		i3c_master_send_jump_to_tim(&gfh_slave[0], TIM1_ADDR);
#endif /* !I3C_COPY_EN */
#endif /* I3C_EN */
    }
	if(I3C_NUM_SLAVE_DEVICES > 2) {
#ifdef I3C_EN
#ifdef I3C_COPY_EN
        master_fw_upload(&gfh_slave[2], TIM1_ADDR, LC_GFH_D2D);
		i3c_master_send_jump_to_tim(&gfh_slave[2], TIM1_ADDR);
#else /* !I3C_COPY_EN direct jump to backdoor copied tim */
		i3c_master_send_jump_to_tim(&gfh_slave[0], TIM1_ADDR);
#endif /* !I3C_COPY_EN */
#endif /* I3C_EN */
    }
	if(I3C_NUM_SLAVE_DEVICES > 3) {
#ifdef I3C_EN
#ifdef I3C_COPY_EN
        master_fw_upload(&gfh_slave[3], TIM1_ADDR, LC_GFH_D2D);
		i3c_master_send_jump_to_tim(&gfh_slave[3], TIM1_ADDR);
#else /* !I3C_COPY_EN direct jump to backdoor copied tim */
		i3c_master_send_jump_to_tim(&gfh_slave[0], TIM1_ADDR);
#endif /* !I3C_COPY_EN */
#endif /* I3C_EN */
    }
    
	/*********************** IPM ************************************/
	ipm_init();
	/*********************** DDR ************************************/

	/*********************** PCIe ***********************************/


	/*********************** FreeRTOS *******************************/
	vTaskStartScheduler();
	while(1)
	{
		//Forever loop for FreeRTOS
	}
#endif
	return 0;

}

