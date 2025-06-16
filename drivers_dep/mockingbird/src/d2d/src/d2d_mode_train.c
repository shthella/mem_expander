#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <common/compiler.h>

#include <common/cpu.h>

#include "d2d.h"
#include <interrupt.h>

volatile int32_t timer_triggered = 0;

__attribute__((optimize("O2"))) uint64_t flc_delay(uint64_t delay) {
    uint64_t busyLoop = delay;
    while (busyLoop){ busyLoop--;}
}

int32_t d2d_set_rx_mode_train (blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL) {
    pD2dLL->rxInterfaceControlStatus.val =
        ((0x1 << RX_INTERFACE_CONTROL_STATUS__MODE_bp) &
        RX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
        ((0x2 << RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
        RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
        ((0x0 << RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
        RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
        ((0x1 << RX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
        RX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
        ((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
        RX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
        ((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
        RX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + RX_INTERFACE_CONTROL_STATUS, pD2dLL->rxInterfaceControlStatus.val);
    
}

void timer_handler (int id, void *data) {
    timer_triggered = 1;
}

int32_t d2d_timer_set(time_t usec) {
    unsigned long long timeval, timebase;
    struct metal_interrupt *tmr_intr; //timer interrupt 
    int rc, tmr_id;
    struct metal_interrupt* sInterrupt; 
    struct metal_interrupt *s_cpu_intr; //cpu interrupt
    struct metal_cpu *s_cpu;

	//s_cpu = metal_cpu_get(metal_cpu_get_current_hartid());
	if (s_cpu == NULL) {
	     return 1;
	}
	
	//s_cpu_intr = metal_cpu_interrupt_controller(s_cpu);
	if (s_cpu_intr == NULL) {
	     return 2;
	}
	//metal_interrupt_init(s_cpu_intr);
	
	//sInterrupt = metal_interrupt_get_controller(2,metal_cpu_get_current_hartid());
	if(sInterrupt == NULL) {
		return 3;
	}
#if 0
	metal_interrupt_init(sInterrupt);
	if(metal_interrupt_set_vector_mode(sInterrupt, METAL_SELECTIVE_VECTOR_MODE) != 0) {
		return 4;
	}
#endif 

#if 0
    timeval = 0;
    timebase = 0;
    timeval = metal_cpu_get_timer(s_cpu);
    timebase = metal_cpu_get_timebase(s_cpu);
    if ((timeval == 0) || (timebase == 0)) {
       return 2;
    }

    tmr_intr = metal_cpu_timer_interrupt_controller(s_cpu);
    if (tmr_intr == NULL) {
        return 4;
    }
    metal_interrupt_init(tmr_intr);
    tmr_id = metal_cpu_timer_get_interrupt_id(s_cpu);
    rc = metal_interrupt_register_handler(tmr_intr, tmr_id, timer_handler, s_cpu);
    if (rc < 0) {
        return (rc * -1);
    }

    metal_cpu_set_mtimecmp(s_cpu, usec);
   if (metal_interrupt_enable(tmr_intr, tmr_id) == -1) {
        return 5;
    }   
    
    if (metal_interrupt_enable(s_cpu_intr, 0) == -1) {
        return 6;
    }
#endif 
}

int32_t d2d_set_tx_train_mode(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL) {
    // Register: d2d_reg_block.TxInterfaceControlStatus: APB LL_WR
    pD2dLL->txInterfaceControlStatus.val =
        (((uint32_t)0x1 << TX_INTERFACE_CONTROL_STATUS__MODE_bp) &
        TX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
        (((uint32_t)0x2 << TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
        TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
        TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
        (((uint32_t)0x1 << TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
        TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
        TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
        TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS, pD2dLL->txInterfaceControlStatus.val);
    
}
int32_t d2d_rx_train(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL){
    /* +++++++++++++++++++++++++++++++++++++++++++++ TRAIN START ++++++++++++++++++++++++++++++++ */
    // Register: d2d_reg_block.RxTrainNudge: APB LL_WR
    pD2dLL->rxTrainNudge.val =
        ((0x0 << RX_TRAIN_NUDGE__NUDGE0_bp) &
        RX_TRAIN_NUDGE__NUDGE0_bm)	|
        ((0x1 << RX_TRAIN_NUDGE__NUDGE1_bp) &
        RX_TRAIN_NUDGE__NUDGE1_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + RX_TRAIN_NUDGE, pD2dLL->rxTrainNudge.val);

    // Register: d2d_reg_block.RxTrainNudge: APB LL_WR
    pD2dLL->rxTrainNudge.val =
        ((0x0 << RX_TRAIN_NUDGE__NUDGE0_bp) &
        RX_TRAIN_NUDGE__NUDGE0_bm)	|
        ((0x1 << RX_TRAIN_NUDGE__NUDGE1_bp) &
        RX_TRAIN_NUDGE__NUDGE1_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + RX_TRAIN_NUDGE, pD2dLL->rxTrainNudge.val);

    // Register: d2d_reg_block.RxTrainTrigSample: APB LL_WR
    pD2dLL->rxTrainTrigSample.val =
        ((0x1 << RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bp) &
        RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + RX_TRAIN_TRIG_SAMPLE, pD2dLL->rxTrainTrigSample.val);

    // Register: d2d_reg_block.DdifFlitSample00: APB LL_RD
    pD2dLL->ddifFlitSample00.val = 0x17;

    pD2dLL->ddifFlitSample00.val =
    d2d_ll_read(D2D_LL_BASE_ADDR + DDIF_FLIT_SAMPLE00, pD2dLL->ddifFlitSample00.val);

    // Register: d2d_reg_block.DdifFlitSample02: APB LL_RD
    pD2dLL->ddifFlitSample02.val = 0x17;

    pD2dLL->ddifFlitSample02.val =
    d2d_ll_read(D2D_LL_BASE_ADDR + DDIF_FLIT_SAMPLE02, pD2dLL->ddifFlitSample02.val);

    /* 3.7.5.3.1 Get DLL Accumulator Values and Observed Current Values, Compute Override Values */

    // Get and save initial accumulator values
    uint32_t    ctrl_r_pphd_P[8] = {0},
                ctrl_d_pphd_P[8] = {0},
                ctrl_r_int_ev_msb_cur, ctrl_r_int_ev_lsb_cur,
                ctrl_r_int_od_msb_cur, ctrl_r_int_od_lsb_cur,
                ctrl_d_int_msb_cur, ctrl_d_int_lsb_cur;
    // Register: rx_slice_0.rx_dll_dll_freeze: APB RD

    // Register: rx_slice_0.rx_dll_dll_freeze: APB WR
    pD2dPhy->rx_slice_0.rx_dll_dll_freeze =
        ((0x1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_DLL_FREEZE__FREEZE_bp) &
        BLYNX_BOW__RX_SLICE_0_T__RX_DLL_DLL_FREEZE__FREEZE_bm);

     d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_dll_freeze, pD2dPhy->rx_slice_0.rx_dll_dll_freeze);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_0: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_0 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_0 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_0, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_0);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_0: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_0 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_0 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_0, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_0);

    ctrl_r_pphd_P[0] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_0 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_0)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_1: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_1 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_1 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_1, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_1);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_1: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_1 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_1 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_1, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_1);

    ctrl_r_pphd_P[1] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_1 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_1)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_2: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_2 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_2 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_2, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_2);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_2: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_2 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_2 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_2, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_2);

    ctrl_r_pphd_P[2] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_2 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_2)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_3: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_3 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_3 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_3, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_3);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_3: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_3 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_3 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_3, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_3);

    ctrl_r_pphd_P[3] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_3 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_3)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_4: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_4 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_4 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_4, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_4);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_4: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_4 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_4 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_4, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_4);

    ctrl_r_pphd_P[4] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_4 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_4)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_5: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_5 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_5 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_5, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_5);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_5: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_5 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_5 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_5, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_5);

    ctrl_r_pphd_P[5] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_5 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_5)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_6: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_6 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_6 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_6, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_6);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_6: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_6 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_6 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_6, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_6);

    ctrl_r_pphd_P[6] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_6 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_6)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_7: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_7 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_7 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_lo_7, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_7);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_7: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_7 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_7 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_pphd_hi_7, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_7);

    ctrl_r_pphd_P[7] =  ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_hi_7 << 16 +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_pphd_lo_7)) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_lo: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_lo = 0x4c00;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_lo =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_int_ev_lo, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_lo);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_hi: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_hi = 0xd;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_hi =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
        (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_int_ev_hi,
        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_hi);

    ctrl_r_int_ev_msb_cur = (((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_hi << 16) +
        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_lo) >> 10) >> 11;
    ctrl_r_int_ev_lsb_cur = (((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_hi << 16) +
        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_ev_lo) >> 10) & ((1 << 11) - 1);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_lo: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_lo = 0x4c00;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_lo =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_int_od_lo, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_lo);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_hi: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_hi = 0xd;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_hi =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_r_int_od_hi, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_hi);

    ctrl_r_int_od_msb_cur = (((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_hi << 16) +
        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_lo) >> 10) >> 11;
    ctrl_r_int_od_lsb_cur = (((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_hi << 16) +
        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_r_int_od_lo) >> 10) & ((1 << 11) - 1);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_0: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_0 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_0 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_0, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_0);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_0: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_0 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_0 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_0, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_0);

    ctrl_d_pphd_P[0] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_0 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_0) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_1: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_1 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_1 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_1, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_1);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_1: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_1 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_1 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_1, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_1);

    ctrl_d_pphd_P[1] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_1 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_1) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_2: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_2 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_2 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_2, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_2);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_2: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_2 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_2 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_2, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_2);

    ctrl_d_pphd_P[2] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_2 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_2) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_3: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_3 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_3 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_3, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_3);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_3: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_3 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_3 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_3, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_3);

    ctrl_d_pphd_P[3] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_3 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_3) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_4: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_4 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_4 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_4, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_4);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_4: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_4 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_4 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_4, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_4);

    ctrl_d_pphd_P[4] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_4 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_4) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_5: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_5 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_5 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_5, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_5);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_5: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_5 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_5 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_5, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_5);

    ctrl_d_pphd_P[5] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_5 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_5) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_6: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_6 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_6 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_6, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_6);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_6: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_6 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_6 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_6, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_6);

    ctrl_d_pphd_P[6] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_6 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_6) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_7: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_7 = 0x0;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_7 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_lo_7, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_7);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_7: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_7 = 0x80;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_7 =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_pphd_hi_7, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_7);

    ctrl_d_pphd_P[7] = ((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_hi_7 << 16) +
                        pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_pphd_lo_7) >> 15;

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_lo: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_lo = 0x1000;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_lo =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_int_lo, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_lo);

    // Register: rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_hi: APB RD
    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_hi = 0x20;

    pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_hi =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_accum_obsv_ctrl_d_int_hi, pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_hi);

    ctrl_d_int_msb_cur = (((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_hi<< 16) +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_lo) >> 10) >> 11;
    ctrl_d_int_lsb_cur = (((pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_hi<< 16) +
                            pD2dPhy->rx_slice_0.rx_dll_accum_obsv_ctrl_d_int_lo) >> 10) & ((1 << 11) - 1);

    // Register: rx_slice_0.rx_dll_dll_freeze: APB RD
    pD2dPhy->rx_slice_0.rx_dll_dll_freeze = 0x1;

    pD2dPhy->rx_slice_0.rx_dll_dll_freeze =
    d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_dll_freeze, pD2dPhy->rx_slice_0.rx_dll_dll_freeze);

    // Register: rx_slice_0.rx_dll_dll_freeze: APB WR
    pD2dPhy->rx_slice_0.rx_dll_dll_freeze =
        ((0x0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_DLL_FREEZE__FREEZE_bp) &
        BLYNX_BOW__RX_SLICE_0_T__RX_DLL_DLL_FREEZE__FREEZE_bm);

     d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_dll_freeze, pD2dPhy->rx_slice_0.rx_dll_dll_freeze);


    /* 3.7.5.3.2 Override Accumulators */

    // Override accumulators at current sample point

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_0, ctrl_r_pphd_P[0]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_1, ctrl_r_pphd_P[1]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_2, ctrl_r_pphd_P[2]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_3, ctrl_r_pphd_P[3]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_4, ctrl_r_pphd_P[4]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_5, ctrl_r_pphd_P[5]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_6, ctrl_r_pphd_P[6]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_7, ctrl_r_pphd_P[7]);

    // Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev: APB RD
    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
        (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_ev,
        ((ctrl_r_int_ev_msb_cur & 0x7) << 11) + ctrl_r_int_ev_lsb_cur);

    // Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od: APB RD
    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
        (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_od,
         ((ctrl_r_int_od_msb_cur & 0x7) << 11) + ctrl_r_int_od_lsb_cur);

    // Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_0: APB RD
    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_0, ctrl_d_pphd_P[0]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_1, ctrl_d_pphd_P[1]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_2, ctrl_d_pphd_P[2]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_3, ctrl_d_pphd_P[3]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_4, ctrl_d_pphd_P[4]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_5, ctrl_d_pphd_P[5]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_6, ctrl_d_pphd_P[6]);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_7, ctrl_d_pphd_P[7]);


    // Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_int: APB RD
    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
        (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_int,
        ((ctrl_d_int_msb_cur & 0x7) << 11) + ctrl_d_int_lsb_cur);
/* TILL THIS SAME AS DOC */

    // Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_r: APB RD
    pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r =
	    ((0xff << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bm)	|
	    ((0x1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bm)	|
	    ((0x1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bm);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

    // Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_d: APB RD
    pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d =
	    ((0xff << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bm)	|
	    ((0x1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bm);

    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_d, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d);

    /* 3.7.5.3.3 Calculate Alignment Offset Adjustment and Control Values */

    uint32_t word_alignment_adjustment, word_alignment_offset;
    uint32_t serialization_ratio = 16;

    uint32_t    ctrl_r_int_ev_msb_tgt, ctrl_r_int_od_msb_tgt,
                ctrl_r_int_ev_lsb_tgt, ctrl_r_int_od_lsb_tgt,
                ctrl_d_int_msb_tgt, ctrl_d_int_lsb_tgt;
    uint32_t granule;

    uint64_t align_dly_us = 12;
    uint64_t align_dly_ns;
    // Observe data received at RX link layer, compare with data sent from TX link layer and 
    // determine the alignment offset. Calculate the adjustment
        pD2dLL->ddifFlitSample00.val =
            d2d_ll_read(D2D_LL_BASE_ADDR + DDIF_FLIT_SAMPLE00, pD2dLL->ddifFlitSample00.val);

        granule = pD2dLL->ddifFlitSample00.val & ((serialization_ratio/2)-1);

        word_alignment_offset = granule ? ((serialization_ratio - granule)*2) : 0;

        word_alignment_adjustment = (word_alignment_offset < (serialization_ratio/2)) ? 
        word_alignment_offset : word_alignment_offset - serialization_ratio;

    // Compute current control values and target control values
    ctrl_r_int_ev_msb_tgt = ctrl_r_int_ev_msb_cur + word_alignment_adjustment;
    ctrl_r_int_od_msb_tgt = ctrl_r_int_od_msb_cur + word_alignment_adjustment;
    ctrl_d_int_msb_tgt = ctrl_d_int_msb_cur + word_alignment_adjustment;
    ctrl_r_int_ev_lsb_tgt = ctrl_r_int_ev_lsb_cur;
    ctrl_r_int_od_lsb_tgt = ctrl_r_int_od_lsb_cur;
    ctrl_d_int_lsb_tgt = ctrl_d_int_lsb_cur;


    /* 3.7.5.3.4 Repeat Section 3.7.5.3.5, Until All Current Values Match Target Values */

    while ((ctrl_r_int_ev_msb_cur != ctrl_r_int_ev_msb_tgt) || 
            (ctrl_r_int_od_msb_cur != ctrl_r_int_od_msb_tgt) || 
            (ctrl_d_int_msb_cur != ctrl_d_int_msb_tgt) || 
            (ctrl_r_int_ev_lsb_cur != ctrl_r_int_ev_lsb_tgt) ||
            (ctrl_r_int_od_lsb_cur != ctrl_r_int_od_lsb_tgt) || 
            (ctrl_d_int_lsb_cur != ctrl_d_int_lsb_tgt)) {

        // Start: Move sampling clock one UI at a time towards the desired direction
        // Compute next control values to program and time to wait
        if (word_alignment_adjustment > 0) { // Moving to the Right
            if (ctrl_r_int_ev_msb_cur == ctrl_r_int_ev_msb_tgt) {
                // At the target UI
                ctrl_r_int_ev_lsb_cur = ((ctrl_r_int_ev_lsb_cur < 0x200) && (ctrl_r_int_ev_lsb_tgt > 0x200)) ? 0x200 : ctrl_r_int_ev_lsb_tgt;
                ctrl_r_int_od_lsb_cur = ((ctrl_r_int_od_lsb_cur < 0x200) && (ctrl_r_int_od_lsb_tgt > 0x200)) ? 0x200 : ctrl_r_int_od_lsb_tgt;
                ctrl_d_int_lsb_cur = ((ctrl_d_int_lsb_cur < 0x200) && (ctrl_d_int_lsb_tgt > 0x200)) ? 0x200 : ctrl_d_int_lsb_tgt;
                align_dly_ns = align_dly_us * 1000 * 
                    ((ctrl_r_int_ev_lsb_cur > 0x200) || (ctrl_r_int_od_lsb_cur > 0x200) || (ctrl_d_int_lsb_cur    > 0x200)) ?
                    1.0 : 0.4;
                } else if ((ctrl_r_int_ev_lsb_cur != 0x7ff) || (ctrl_r_int_od_lsb_cur != 0x7ff) || (ctrl_d_int_lsb_cur != 0x7ff)) {
                    // Begin Moving within the UI
                    ctrl_r_int_ev_lsb_cur = (ctrl_r_int_ev_lsb_cur < 0x200) ? 0x200 : 0x7ff;
                    ctrl_r_int_od_lsb_cur = (ctrl_r_int_od_lsb_cur < 0x200) ? 0x200 : 0x7ff;
                    ctrl_d_int_lsb_cur = (ctrl_d_int_lsb_cur < 0x200) ? 0x200 : 0x7ff;
                    align_dly_ns = align_dly_us * 1000 * (ctrl_r_int_ev_lsb_cur > 0x200) ? 1.0 : 0.4;
                    } else {
                        // Moving across UI
                        ctrl_r_int_ev_msb_cur += 1;
                        ctrl_r_int_od_msb_cur += 1;
                        ctrl_d_int_msb_cur += 1;
                        ctrl_r_int_ev_lsb_cur = 0x0;
                        ctrl_r_int_od_lsb_cur = 0x0;
                        ctrl_d_int_lsb_cur = 0x0;
                        align_dly_ns = 10;
                        }
        } else {
            // Moving to the left
            if (ctrl_r_int_ev_msb_cur == ctrl_r_int_ev_msb_tgt) {
                // At the target UI
                ctrl_r_int_ev_lsb_cur = ((ctrl_r_int_ev_lsb_cur > 0x200) && (ctrl_r_int_ev_lsb_tgt < 0x200)) ? 0x200 : ctrl_r_int_ev_lsb_tgt;
                ctrl_r_int_od_lsb_cur = ((ctrl_r_int_od_lsb_cur > 0x200) && (ctrl_r_int_od_lsb_tgt < 0x200)) ? 0x200 : ctrl_r_int_od_lsb_tgt;
                ctrl_d_int_lsb_cur = ((ctrl_d_int_lsb_cur > 0x200) && (ctrl_d_int_lsb_tgt < 0x200)) ? 0x200 : ctrl_d_int_lsb_tgt;
                align_dly_ns = align_dly_us * 1000;
            }else if ((ctrl_r_int_ev_lsb_cur != 0x0) || (ctrl_r_int_od_lsb_cur != 0x0) || (ctrl_d_int_lsb_cur != 0x0)) {
                // Begin Moving within UI
                ctrl_r_int_ev_lsb_cur = (ctrl_r_int_ev_lsb_cur > 0x200) ? 0x200 : 0x0;
                ctrl_r_int_od_lsb_cur = (ctrl_r_int_od_lsb_cur > 0x200) ? 0x200 : 0x0;
                ctrl_d_int_lsb_cur = (ctrl_d_int_lsb_cur > 0x200) ? 0x200 : 0x0;
                align_dly_ns = align_dly_us * 1000;
            } else {
                // Moving across UI
                ctrl_r_int_ev_msb_cur -= 1;
                ctrl_r_int_od_msb_cur -= 1;
                ctrl_d_int_msb_cur -= 1;
                ctrl_r_int_ev_lsb_cur = 0x7ff;
                ctrl_r_int_od_lsb_cur = 0x7ff;
                ctrl_d_int_lsb_cur = 0x7ff;
                align_dly_ns = 10;
            }
        }
        pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev =  ((ctrl_r_int_ev_msb_cur & 0x7) << 11 + ctrl_r_int_ev_lsb_cur);
        d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
            (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_ev,
            pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev);
        pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od = ((ctrl_r_int_od_msb_cur & 0x7) << 11) + ctrl_r_int_od_lsb_cur;
        d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
            (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_od,
            pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od);
        pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_int = ((ctrl_d_int_msb_cur & 0x7) << 11) + ctrl_d_int_lsb_cur;
        d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
         (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_int,
         pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_int);


        flc_delay(10);
#if 0
        timer_triggered = 0;
        d2d_timer_set(1);
        while(!timer_triggered) {
            __asm__ volatile ("wfi");
        }
#endif   

    } /* End of word alignment */

    pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r =
	    ((0x00 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bm)	|
	    ((0x0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bm)	|
	    ((0x0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bm);
    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

    pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d =
	    ((0x00 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bm)	|
	    ((0x0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bp) &
	    BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bm);
    d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
    (uint32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_d, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d);

    /* ++++++++++++++++++++++++++++++++++++++ TRAIN END ++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

    return 0;
}

int32_t d2d_skew_correction(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL) {
    // Register: d2d_reg_block.RxInterfaceControlStatus: APB LL_WR
    pD2dLL->rxInterfaceControlStatus.val =
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__MODE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
    	((0x2 << RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
    	RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
    	((0x1 << RX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + RX_INTERFACE_CONTROL_STATUS, pD2dLL->rxInterfaceControlStatus.val);

    // Register: d2d_reg_block.RxInterfaceControlStatus: APB LL_WR
    pD2dLL->rxInterfaceControlStatus.val =
    	((0x1 << RX_INTERFACE_CONTROL_STATUS__MODE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
    	((0x2 << RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
    	RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
    	((0x1 << RX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + RX_INTERFACE_CONTROL_STATUS, pD2dLL->rxInterfaceControlStatus.val);
    
    // Register: d2d_reg_block.RxTrainTrigSample: APB LL_WR
    pD2dLL->rxTrainTrigSample.val =
    	((0x1 << RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bp) &
    	RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + RX_TRAIN_TRIG_SAMPLE, pD2dLL->rxTrainTrigSample.val);
    
    // Register: d2d_reg_block.DdifFlitSample00: APB LL_RD
    pD2dLL->ddifFlitSample00.val = 0x28;
    
    d2d_ll_read(D2D_LL_BASE_ADDR + DDIF_FLIT_SAMPLE00, pD2dLL->ddifFlitSample00.val);
    
    // Register: d2d_reg_block.TxInterfaceControlStatus: APB LL_WR
    pD2dLL->txInterfaceControlStatus.val =
    	((0x1 << TX_INTERFACE_CONTROL_STATUS__MODE_bp) &
    	TX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
    	((0x2 << TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
    	TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
    	TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
    	((0x1 << TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) & //KRI changed 0 to 1
    	TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
    	TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
    	TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS, pD2dLL->txInterfaceControlStatus.val);
    
    // Register: d2d_reg_block.TxInterfaceControlStatus: APB LL_WR
    pD2dLL->txInterfaceControlStatus.val =
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__MODE_bp) &
    	TX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
    	((0x2 << TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
    	TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
    	TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
    	TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
    	TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
    	TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS, pD2dLL->txInterfaceControlStatus.val);

    return 0;
}

/* mkb: & gfh: set tx mode idle */
int32_t d2d_set_tx_mode_idle(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL){

        pD2dLL->txInterfaceControlStatus.val =
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__MODE_bp) &
        TX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
        (((uint32_t)0x2 << TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
        TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
        TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
        (((uint32_t)0x1 << TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
        TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
        TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
        TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS, pD2dLL->txInterfaceControlStatus.val);

    pD2dLL->txInterfaceControlStatus.val =
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__MODE_bp) &
        TX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
        (((uint32_t)0x2 << TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
        TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
        TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
        TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
        TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
        (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
        TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS, pD2dLL->txInterfaceControlStatus.val);

    return 0;
}

/* mkb: & gfh: poll tx mode idle */
int32_t d2d_poll_rx_for_tx_idle_mode(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL)
{
    do {
    // Register: d2d_reg_block.RxTrainTrigSample: APB LL_WR
    pD2dLL->rxTrainTrigSample.val =
    	((0x1 << RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bp) &
    	RX_TRAIN_TRIG_SAMPLE__TRAINTRIGSAMPLE_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + RX_TRAIN_TRIG_SAMPLE, pD2dLL->rxTrainTrigSample.val);
    
    // Register: d2d_reg_block.DdifFlitSample04: APB LL_RD
    pD2dLL->ddifFlitSample04.val = 0x0;
    
    /* DdifFlitSample04 = 0x0 meand Tx is in Idle mode */
    }while (d2d_ll_read(D2D_LL_BASE_ADDR + DDIF_FLIT_SAMPLE04, pD2dLL->ddifFlitSample04.val) != 0x0);

    return 0;
}
/* mkb: & gfh: Rx mode into wait stage */
int32_t d2d_set_rx_mode_wait(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL) {
    // Register: d2d_reg_block.RxInterfaceControlStatus: APB LL_WR
    pD2dLL->rxInterfaceControlStatus.val =
    	((0x2 << RX_INTERFACE_CONTROL_STATUS__MODE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
    	((0x2 << RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
    	RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
    	((0x1 << RX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + RX_INTERFACE_CONTROL_STATUS, pD2dLL->rxInterfaceControlStatus.val);
    
    // Register: d2d_reg_block.RxInterfaceControlStatus: APB LL_WR
    pD2dLL->rxInterfaceControlStatus.val =
    	((0x2 << RX_INTERFACE_CONTROL_STATUS__MODE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
    	((0x2 << RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
    	RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
    	RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
    	((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
    	RX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + RX_INTERFACE_CONTROL_STATUS, pD2dLL->rxInterfaceControlStatus.val);

    return 0;
}

/* mkb: & gfh: set Tx mode to RUN */
int32_t d2d_set_tx_mode_run(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL) {
    // Register: d2d_reg_block.TxInterfaceControlStatus: APB LL_WR
    pD2dLL->txInterfaceControlStatus.val =
    	((0x3 << TX_INTERFACE_CONTROL_STATUS__MODE_bp) &
    	TX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
    	((0x2 << TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
    	TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
    	TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
    	TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
    	TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
    	((0x0 << TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
    	TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS, pD2dLL->txInterfaceControlStatus.val);
    
    return 0;
}

/* mkb: & gfh: Poll for Rx mode to RUN */
int32_t d2d_poll_rx_mode_run(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL) {
    // Register: d2d_reg_block.RxInterfaceControlStatus: APB LL_RD
    pD2dLL->rxInterfaceControlStatus.val = 0x0;
    
    while(d2d_ll_read(D2D_LL_BASE_ADDR + RX_INTERFACE_CONTROL_STATUS, pD2dLL->rxInterfaceControlStatus.val) != 0xb);
    
    // Register: d2d_reg_block.RxVirtualWireDisable00: APB LL_WR
    pD2dLL->rxVirtualWireDisable00.val =
    	((0x0 << RX_VIRTUAL_WIRE_DISABLE00__DISABLE_bp) &
    	RX_VIRTUAL_WIRE_DISABLE00__DISABLE_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + RX_VIRTUAL_WIRE_DISABLE00, pD2dLL->rxVirtualWireDisable00.val);
    
    // Register: d2d_reg_block.TxVirtualWireDisable00: APB LL_WR
    pD2dLL->txVirtualWireDisable00.val =
    	((0x0 << TX_VIRTUAL_WIRE_DISABLE00__DISABLE_bp) &
    	TX_VIRTUAL_WIRE_DISABLE00__DISABLE_bm);
    
    d2d_ll_write(D2D_LL_BASE_ADDR + TX_VIRTUAL_WIRE_DISABLE00, pD2dLL->txVirtualWireDisable00.val);

    return 0;
}
