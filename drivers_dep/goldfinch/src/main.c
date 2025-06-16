#include <stdio.h>
#define I3C_EN
#define D2D_EN
#include "uart.h"
#include <gpio.h>
#include <interrupt.h>
#include <riscv_cpu.h>

#ifdef I3C_EN
#include "i3c.h"
#endif /* I3C_EN */

#ifdef D2D_EN
#include "d2d.h"
blynx_bow_t d2dPhy;
D2dLLRegBlock d2dLL;
#endif /* D2D_EN */

#define SPD_ENABLE 0

extern void spd_i2c_read(void);
extern void ddr_phy_init(void);
extern void gfh_mc_init(void);
extern void gfh_mc_post_init(void);

void main()
{
  uart_init();
  uint8_t err;
  debug_gpio_set(0x7);
#ifdef I3C_EN
	err = i3c_slave_init();
    if (err !=0){
        //printf("ERROR: I3C Slave init failed - %d\n", err);
        return -1;
    }
    
    i3c_slave_send_fw_dnld_resp();
#endif /* I3C_EN */

#ifdef D2D_EN

	d2d_mode_init(&d2dPhy, &d2dLL);
#if 1 //comment added 
    while (i3c_slave_get_d2d_status() != 0x1);
    i3c_slave_send_d2d_resp(i3c_slave_get_d2d_status());
    d2d_set_rx_mode_train(&d2dPhy, &d2dLL);
    printf("the status from i3cslave\r\n");
    
    while (i3c_slave_get_d2d_status() != 0x2);
    d2d_set_tx_train_mode(&d2dPhy, &d2dLL);
    i3c_slave_send_d2d_resp(i3c_slave_get_d2d_status());
    d2d_rx_train(&d2dPhy, &d2dLL);
    //d2d_skew_correction(); //DV suggested to remove/not required

    while (i3c_slave_get_d2d_status() != 0x3);
    d2d_set_tx_mode_idle(&d2dPhy, &d2dLL);
    i3c_slave_send_d2d_resp(i3c_slave_get_d2d_status());
    d2d_poll_rx_for_tx_idle_mode(&d2dPhy, &d2dLL);
    d2d_set_rx_mode_wait(&d2dPhy, &d2dLL);

    while (i3c_slave_get_d2d_status() != 0x4);
    d2d_set_tx_mode_run(&d2dPhy, &d2dLL);
    i3c_slave_send_d2d_resp(i3c_slave_get_d2d_status());
    d2d_poll_rx_mode_run(&d2dPhy, &d2dLL);
#endif 
#endif


#if SPD_ENABLE
	spd_i2c_read();
#endif

	gfh_mc_init();

	ddr_phy_init();

	gfh_mc_post_init();


	while(1){
		__asm__ volatile ("wfi");
	}
}

