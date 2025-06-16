#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <compiler.h>
#include "uart.h"



#include "d2d.h"


int32_t d2d_mode_init(blynx_bow_t *pD2dPhy, D2dLLRegBlock *pD2dLL) {
	uint16_t regVal;
	printf("%s\n", __func__);

	/* program PMU ctrl reg for getting d2d out of reset */
	regVal = readl(0x26000004);
	writel((regVal & 0xFFFFFEFF)|0x100,0x26000004);
	regVal = readl(0x26000038);
	regVal = (regVal & 0xfff00fff) | 0x22000;
	writel(regVal, 0x26000038);

	printf("the regval is %08x\r\n",regVal);
	//writel(0x98, 0x27008004);
    pD2dLL->txInterfaceControlStatus.val =
            (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__MODE_bp) &
            TX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
            (((uint32_t)0x2 << TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
            TX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
            (((uint32_t)0x1 << TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
            TX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
            (((uint32_t)0x1 << TX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
            TX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
            (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
            TX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
            (((uint32_t)0x0 << TX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
            TX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS, pD2dLL->txInterfaceControlStatus.val);

    //D2D_LL_BASE_ADDR + TX_INTERFACE_CONTROL_STATUS
	// Register: bow_top.clk_dist_enable: APB RD
	pD2dPhy->bow_top.clk_dist_enable = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TOP_BASE_ADDR +
			(int32_t)&((blynx_bow__bow_top_t_t *)0)->clk_dist_enable, pD2dPhy->bow_top.clk_dist_enable);

	// Register: bow_top.clk_dist_enable: APB WR
	pD2dPhy->bow_top.clk_dist_enable =
		((1 << BLYNX_BOW__BOW_TOP_T__CLK_DIST_ENABLE__ENABLE_bp) &
		 BLYNX_BOW__BOW_TOP_T__CLK_DIST_ENABLE__ENABLE_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TOP_BASE_ADDR +
			(int32_t)&((blynx_bow__bow_top_t_t *)0)->clk_dist_enable, pD2dPhy->bow_top.clk_dist_enable);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB RD
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config = 0x12;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB WR
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB RD
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config = 0x13;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB WR
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB RD
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config = 0x53;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB WR
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB RD
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config = 0x51;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB WR
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB RD
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config = 0x41;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_tx_qpump_vreg_config: APB WR
	pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_TX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_tx_qpump_vreg_config, pD2dPhy->tx_slice_0.tx_tx_qpump_vreg_config);

	// Register: tx_slice_0.tx_wild_clk_config1: APB RD
	pD2dPhy->tx_slice_0.tx_wild_clk_config1 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_wild_clk_config1, pD2dPhy->tx_slice_0.tx_wild_clk_config1);

	// Register: tx_slice_0.tx_wild_clk_config1: APB WR
	pD2dPhy->tx_slice_0.tx_wild_clk_config1 =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_wild_clk_config1, pD2dPhy->tx_slice_0.tx_wild_clk_config1);

	// Register: tx_slice_0.tx_wild_clk_config1: APB RD
	pD2dPhy->tx_slice_0.tx_wild_clk_config1 = 0x1;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_wild_clk_config1, pD2dPhy->tx_slice_0.tx_wild_clk_config1);

	// Register: tx_slice_0.tx_wild_clk_config1: APB WR
	pD2dPhy->tx_slice_0.tx_wild_clk_config1 =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_wild_clk_config1, pD2dPhy->tx_slice_0.tx_wild_clk_config1);

	// Register: tx_slice_0.tx_ser_ratio_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_ser_ratio_ctrl = 0x3;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_ser_ratio_ctrl, pD2dPhy->tx_slice_0.tx_ser_ratio_ctrl);

	// Register: tx_slice_0.tx_clk_en: APB RD
	pD2dPhy->tx_slice_0.tx_clk_en = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_en, pD2dPhy->tx_slice_0.tx_clk_en);

	// Register: tx_slice_0.tx_clk_en: APB WR
	pD2dPhy->tx_slice_0.tx_clk_en =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_REG_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_REG_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_RTL_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_RTL_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_en, pD2dPhy->tx_slice_0.tx_clk_en);

	// Register: tx_slice_0.tx_clk_en: APB RD
	pD2dPhy->tx_slice_0.tx_clk_en = 0x1;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_en, pD2dPhy->tx_slice_0.tx_clk_en);

	// Register: tx_slice_0.tx_clk_en: APB WR
	pD2dPhy->tx_slice_0.tx_clk_en =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_REG_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_REG_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_RTL_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_RTL_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_en, pD2dPhy->tx_slice_0.tx_clk_en);

	// Register: tx_slice_0.tx_clk_en: APB RD
	pD2dPhy->tx_slice_0.tx_clk_en = 0x3;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_en, pD2dPhy->tx_slice_0.tx_clk_en);

	// Register: tx_slice_0.tx_clk_en: APB WR
	pD2dPhy->tx_slice_0.tx_clk_en =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_REG_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_REG_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_RTL_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_RTL_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_en, pD2dPhy->tx_slice_0.tx_clk_en);

	// Register: tx_slice_0.tx_clk_sel: APB RD
	pD2dPhy->tx_slice_0.tx_clk_sel = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_sel, pD2dPhy->tx_slice_0.tx_clk_sel);

	// Register: tx_slice_0.tx_clk_sel: APB WR
	pD2dPhy->tx_slice_0.tx_clk_sel =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_SEL__MPCG_SEL_REG_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_SEL__MPCG_SEL_REG_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_SEL__MPCG_SEL_RTL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_SEL__MPCG_SEL_RTL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_CLK_SEL__MPCG_SEL_LINK_LAYER_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_CLK_SEL__MPCG_SEL_LINK_LAYER_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_clk_sel, pD2dPhy->tx_slice_0.tx_clk_sel);

	// Register: tx_slice_0.tx_sel_load: APB RD
	pD2dPhy->tx_slice_0.tx_sel_load = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_sel_load, pD2dPhy->tx_slice_0.tx_sel_load);

	// Register: tx_slice_0.tx_sel_load: APB WR
	pD2dPhy->tx_slice_0.tx_sel_load =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_SEL_LOAD__MPCG_SEL_LOAD_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_SEL_LOAD__MPCG_SEL_LOAD_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_sel_load, pD2dPhy->tx_slice_0.tx_sel_load);

	// Register: tx_slice_0.tx_shift_reg_setb: APB RD
	pD2dPhy->tx_slice_0.tx_shift_reg_setb = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_shift_reg_setb, pD2dPhy->tx_slice_0.tx_shift_reg_setb);

	// Register: tx_slice_0.tx_shift_reg_rst: APB RD
	pD2dPhy->tx_slice_0.tx_shift_reg_rst = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_shift_reg_rst, pD2dPhy->tx_slice_0.tx_shift_reg_rst);

	// Register: tx_slice_0.tx_shift_reg_setb: APB RD
	pD2dPhy->tx_slice_0.tx_shift_reg_setb = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_shift_reg_setb, pD2dPhy->tx_slice_0.tx_shift_reg_setb);

	// Register: tx_slice_0.tx_shift_reg_setb: APB WR
	pD2dPhy->tx_slice_0.tx_shift_reg_setb =
		((65535 << BLYNX_BOW__TX_SLICE_0_T__TX_SHIFT_REG_SETB__MPCG_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_SHIFT_REG_SETB__MPCG_SHIFT_REG_SETH_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_shift_reg_setb, pD2dPhy->tx_slice_0.tx_shift_reg_setb);

	// Register: tx_slice_0.tx_shift_reg_rst: APB RD
	pD2dPhy->tx_slice_0.tx_shift_reg_rst = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_shift_reg_rst, pD2dPhy->tx_slice_0.tx_shift_reg_rst);

	// Register: tx_slice_0.tx_shift_reg_rst: APB WR
	pD2dPhy->tx_slice_0.tx_shift_reg_rst =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_SHIFT_REG_RST__MPCG_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_SHIFT_REG_RST__MPCG_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_shift_reg_rst, pD2dPhy->tx_slice_0.tx_shift_reg_rst);

	// Register: tx_slice_0.tx_dcc_clktx_ctrl_p_dsm_v_fixed_val: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_p_dsm_v_fixed_val = 0x400;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktx_ctrl_p_dsm_v_fixed_val, pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_p_dsm_v_fixed_val);

	// Register: tx_slice_0.tx_dcc_clktx_ctrl_p_dsm_v_fixed_val: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_p_dsm_v_fixed_val =
		((1311 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_P_DSM_V_FIXED_VAL__VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_P_DSM_V_FIXED_VAL__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktx_ctrl_p_dsm_v_fixed_val, pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_p_dsm_v_fixed_val);

	// Register: tx_slice_0.tx_dcc_comp_sel_overrides: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_comp_sel_overrides, pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides);

	// Register: tx_slice_0.tx_dcc_comp_sel_overrides: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides =
		((4 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INP_OVERRIDE_VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INP_OVERRIDE_VAL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INM_OVERRIDE_VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INM_OVERRIDE_VAL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__ACC_INPUT_OVERRIDE_VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__ACC_INPUT_OVERRIDE_VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_comp_sel_overrides, pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides);

	// Register: tx_slice_0.tx_dcc_comp_sel_overrides: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides = 0x4;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_comp_sel_overrides, pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides);

	// Register: tx_slice_0.tx_dcc_comp_sel_overrides: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides =
		((4 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INP_OVERRIDE_VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INP_OVERRIDE_VAL_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INM_OVERRIDE_VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__COMP_SEL_INM_OVERRIDE_VAL_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__ACC_INPUT_OVERRIDE_VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_COMP_SEL_OVERRIDES__ACC_INPUT_OVERRIDE_VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_comp_sel_overrides, pD2dPhy->tx_slice_0.tx_dcc_comp_sel_overrides);

	// Register: tx_slice_0.tx_dcc_clktx_ctrl_n_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_misc_ctrl = 0x18;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktx_ctrl_n_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_clktx_ctrl_n_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_misc_ctrl =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_BYPASS_SAT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_BYPASS_SAT_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_INVERT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__ACC_INVERT_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_INVERT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_INVERT_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_PRELOAD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_PRELOAD_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_HOLD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__DSM_HOLD_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCKDET_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCKDET_RST_N_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCKDET_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCKDET_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCKDET_FORCE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCKDET_FORCE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCK_SEL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_MISC_CTRL__LOCK_SEL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktx_ctrl_n_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_clktx_ctrl_n_acc_override_val: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_acc_override_val = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktx_ctrl_n_acc_override_val, pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_acc_override_val);

	// Register: tx_slice_0.tx_dcc_clktx_ctrl_n_acc_override_val: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_acc_override_val =
		((1268 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_ACC_OVERRIDE_VAL__VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTX_CTRL_N_ACC_OVERRIDE_VAL__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktx_ctrl_n_acc_override_val, pD2dPhy->tx_slice_0.tx_dcc_clktx_ctrl_n_acc_override_val);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_p_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_misc_ctrl = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_p_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_p_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_misc_ctrl =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_BYPASS_SAT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_BYPASS_SAT_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_INVERT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__ACC_INVERT_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_INVERT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_INVERT_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_PRELOAD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_PRELOAD_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_HOLD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__DSM_HOLD_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCKDET_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCKDET_RST_N_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCKDET_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCKDET_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCKDET_FORCE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCKDET_FORCE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCK_SEL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_MISC_CTRL__LOCK_SEL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_p_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_p_acc_override_val: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_acc_override_val = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_p_acc_override_val, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_acc_override_val);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_p_acc_override_val: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_acc_override_val =
		((1311 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_ACC_OVERRIDE_VAL__VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_P_ACC_OVERRIDE_VAL__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_p_acc_override_val, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_p_acc_override_val);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_n_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_misc_ctrl = 0x10;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_n_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_n_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_misc_ctrl =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_BYPASS_SAT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_BYPASS_SAT_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_INVERT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__ACC_INVERT_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_INVERT_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_INVERT_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_PRELOAD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_PRELOAD_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_HOLD_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__DSM_HOLD_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCKDET_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCKDET_RST_N_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCKDET_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCKDET_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCKDET_FORCE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCKDET_FORCE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCK_SEL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_MISC_CTRL__LOCK_SEL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_n_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_n_acc_override_val: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_acc_override_val = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_n_acc_override_val, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_acc_override_val);

	// Register: tx_slice_0.tx_dcc_clktxb_ctrl_n_acc_override_val: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_acc_override_val =
		((1268 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_ACC_OVERRIDE_VAL__VAL_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CLKTXB_CTRL_N_ACC_OVERRIDE_VAL__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_clktxb_ctrl_n_acc_override_val, pD2dPhy->tx_slice_0.tx_dcc_clktxb_ctrl_n_acc_override_val);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl = 0xa;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bm)	|
		((2 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl = 0x1a;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bm)	|
		((2 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl = 0x3a;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bm)	|
		((2 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl = 0x7a;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bm)	|
		((2 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl = 0x78;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_misc_ctrl: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SW_RST_N_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__DISABLE_WCLK_bm)	|
		((2 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__SAMPLER_CYCLE_LATENCY_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INP_OVERRIDE_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__COMP_SEL_INM_OVERRIDE_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__ACC_INPUT_OVERRIDE_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_MISC_CTRL__BYP_RST_SYNC_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_misc_ctrl, pD2dPhy->tx_slice_0.tx_dcc_misc_ctrl);

	// Register: tx_slice_0.tx_dcc_config: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_config = 0x5;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_config, pD2dPhy->tx_slice_0.tx_dcc_config);

	// Register: tx_slice_0.tx_dcc_config: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_config =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_DAC_RST_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_DAC_RST_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_TAIL_SW_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_TAIL_SW_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_config, pD2dPhy->tx_slice_0.tx_dcc_config);

	// Register: tx_slice_0.tx_dcc_config: APB RD
	pD2dPhy->tx_slice_0.tx_dcc_config = 0x4;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_config, pD2dPhy->tx_slice_0.tx_dcc_config);

	// Register: tx_slice_0.tx_dcc_config: APB WR
	pD2dPhy->tx_slice_0.tx_dcc_config =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_DAC_RST_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_DAC_RST_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_TAIL_SW_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_DCC_CONFIG__DCC_EN_DCC_TAIL_SW_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_dcc_config, pD2dPhy->tx_slice_0.tx_dcc_config);

	// Register: tx_slice_0.tx_link_layer_clock_sel: APB RD
	pD2dPhy->tx_slice_0.tx_link_layer_clock_sel = 0x4;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_link_layer_clock_sel, pD2dPhy->tx_slice_0.tx_link_layer_clock_sel);

	// Register: tx_slice_0.tx_link_layer_clock_sel: APB WR
	pD2dPhy->tx_slice_0.tx_link_layer_clock_sel =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_link_layer_clock_sel, pD2dPhy->tx_slice_0.tx_link_layer_clock_sel);

	// Register: tx_slice_0.tx_link_layer_clock_sel: APB RD
	pD2dPhy->tx_slice_0.tx_link_layer_clock_sel = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_link_layer_clock_sel, pD2dPhy->tx_slice_0.tx_link_layer_clock_sel);

	// Register: tx_slice_0.tx_link_layer_clock_sel: APB WR
	pD2dPhy->tx_slice_0.tx_link_layer_clock_sel =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_link_layer_clock_sel, pD2dPhy->tx_slice_0.tx_link_layer_clock_sel);

	// Register: tx_slice_0.tx_link_layer_clock_sel: APB RD
	pD2dPhy->tx_slice_0.tx_link_layer_clock_sel = 0x1;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_link_layer_clock_sel, pD2dPhy->tx_slice_0.tx_link_layer_clock_sel);

	// Register: tx_slice_0.tx_link_layer_clock_sel: APB WR
	pD2dPhy->tx_slice_0.tx_link_layer_clock_sel =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_link_layer_clock_sel, pD2dPhy->tx_slice_0.tx_link_layer_clock_sel);

	// Register: tx_slice_0.tx_fe_drv_en_W0: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W0 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W0, pD2dPhy->tx_slice_0.tx_fe_drv_en_W0);

	// Register: tx_slice_0.tx_fe_drv_en_W0: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W0 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W0__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W0__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W0, pD2dPhy->tx_slice_0.tx_fe_drv_en_W0);

	// Register: tx_slice_0.tx_fe_drv_en_W1: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W1 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W1, pD2dPhy->tx_slice_0.tx_fe_drv_en_W1);

	// Register: tx_slice_0.tx_fe_drv_en_W1: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W1 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W1__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W1__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W1, pD2dPhy->tx_slice_0.tx_fe_drv_en_W1);

	// Register: tx_slice_0.tx_fe_drv_en_W2: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W2 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W2, pD2dPhy->tx_slice_0.tx_fe_drv_en_W2);

	// Register: tx_slice_0.tx_fe_drv_en_W2: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W2 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W2__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W2__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W2, pD2dPhy->tx_slice_0.tx_fe_drv_en_W2);

	// Register: tx_slice_0.tx_fe_drv_en_W3: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W3 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W3, pD2dPhy->tx_slice_0.tx_fe_drv_en_W3);

	// Register: tx_slice_0.tx_fe_drv_en_W3: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W3 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W3__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W3__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W3, pD2dPhy->tx_slice_0.tx_fe_drv_en_W3);

	// Register: tx_slice_0.tx_fe_drv_en_W4: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W4 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W4, pD2dPhy->tx_slice_0.tx_fe_drv_en_W4);

	// Register: tx_slice_0.tx_fe_drv_en_W4: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W4 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W4__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W4__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W4, pD2dPhy->tx_slice_0.tx_fe_drv_en_W4);

	// Register: tx_slice_0.tx_fe_drv_en_W5: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W5 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W5, pD2dPhy->tx_slice_0.tx_fe_drv_en_W5);

	// Register: tx_slice_0.tx_fe_drv_en_W5: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W5 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W5__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W5__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W5, pD2dPhy->tx_slice_0.tx_fe_drv_en_W5);

	// Register: tx_slice_0.tx_fe_drv_en_W6: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W6 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W6, pD2dPhy->tx_slice_0.tx_fe_drv_en_W6);

	// Register: tx_slice_0.tx_fe_drv_en_W6: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W6 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W6__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W6__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W6, pD2dPhy->tx_slice_0.tx_fe_drv_en_W6);

	// Register: tx_slice_0.tx_fe_drv_en_W7: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W7 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W7, pD2dPhy->tx_slice_0.tx_fe_drv_en_W7);

	// Register: tx_slice_0.tx_fe_drv_en_W7: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W7 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W7__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W7__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W7, pD2dPhy->tx_slice_0.tx_fe_drv_en_W7);

	// Register: tx_slice_0.tx_fe_drv_en_W8: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W8 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W8, pD2dPhy->tx_slice_0.tx_fe_drv_en_W8);

	// Register: tx_slice_0.tx_fe_drv_en_W8: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W8 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W8__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W8__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W8, pD2dPhy->tx_slice_0.tx_fe_drv_en_W8);

	// Register: tx_slice_0.tx_fe_drv_en_W9: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W9 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W9, pD2dPhy->tx_slice_0.tx_fe_drv_en_W9);

	// Register: tx_slice_0.tx_fe_drv_en_W9: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W9 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W9__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W9__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W9, pD2dPhy->tx_slice_0.tx_fe_drv_en_W9);

	// Register: tx_slice_0.tx_fe_drv_en_W10: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W10 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W10, pD2dPhy->tx_slice_0.tx_fe_drv_en_W10);

	// Register: tx_slice_0.tx_fe_drv_en_W10: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W10 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W10__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W10__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W10, pD2dPhy->tx_slice_0.tx_fe_drv_en_W10);

	// Register: tx_slice_0.tx_fe_drv_en_W11: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W11 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W11, pD2dPhy->tx_slice_0.tx_fe_drv_en_W11);

	// Register: tx_slice_0.tx_fe_drv_en_W11: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W11 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W11__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W11__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W11, pD2dPhy->tx_slice_0.tx_fe_drv_en_W11);

	// Register: tx_slice_0.tx_fe_drv_en_W12: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W12 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W12, pD2dPhy->tx_slice_0.tx_fe_drv_en_W12);

	// Register: tx_slice_0.tx_fe_drv_en_W12: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W12 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W12__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W12__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W12, pD2dPhy->tx_slice_0.tx_fe_drv_en_W12);

	// Register: tx_slice_0.tx_fe_drv_en_W13: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W13 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W13, pD2dPhy->tx_slice_0.tx_fe_drv_en_W13);

	// Register: tx_slice_0.tx_fe_drv_en_W13: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W13 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W13__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W13__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W13, pD2dPhy->tx_slice_0.tx_fe_drv_en_W13);

	// Register: tx_slice_0.tx_fe_drv_en_W14: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W14 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W14, pD2dPhy->tx_slice_0.tx_fe_drv_en_W14);

	// Register: tx_slice_0.tx_fe_drv_en_W14: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W14 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W14__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W14__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W14, pD2dPhy->tx_slice_0.tx_fe_drv_en_W14);

	// Register: tx_slice_0.tx_fe_drv_en_W15: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W15 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W15, pD2dPhy->tx_slice_0.tx_fe_drv_en_W15);

	// Register: tx_slice_0.tx_fe_drv_en_W15: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W15 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W15__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W15__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W15, pD2dPhy->tx_slice_0.tx_fe_drv_en_W15);

	// Register: tx_slice_0.tx_fe_drv_en_W16: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W16 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W16, pD2dPhy->tx_slice_0.tx_fe_drv_en_W16);

	// Register: tx_slice_0.tx_fe_drv_en_W16: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W16 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W16__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W16__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W16, pD2dPhy->tx_slice_0.tx_fe_drv_en_W16);

	// Register: tx_slice_0.tx_fe_drv_en_W17: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W17 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W17, pD2dPhy->tx_slice_0.tx_fe_drv_en_W17);

	// Register: tx_slice_0.tx_fe_drv_en_W17: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W17 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W17__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W17__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W17, pD2dPhy->tx_slice_0.tx_fe_drv_en_W17);

	// Register: tx_slice_0.tx_fe_drv_en_W18: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W18 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W18, pD2dPhy->tx_slice_0.tx_fe_drv_en_W18);

	// Register: tx_slice_0.tx_fe_drv_en_W18: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W18 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W18__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W18__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W18, pD2dPhy->tx_slice_0.tx_fe_drv_en_W18);

	// Register: tx_slice_0.tx_fe_drv_en_W19: APB RD
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W19 = 0x1f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W19, pD2dPhy->tx_slice_0.tx_fe_drv_en_W19);

	// Register: tx_slice_0.tx_fe_drv_en_W19: APB WR
	pD2dPhy->tx_slice_0.tx_fe_drv_en_W19 =
		((5 << BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W19__TX_FE_DRV_EN_N_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_FE_DRV_EN_W19__TX_FE_DRV_EN_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_fe_drv_en_W19, pD2dPhy->tx_slice_0.tx_fe_drv_en_W19);

	// Register: tx_slice_0.tx_phyready_override: APB RD
	pD2dPhy->tx_slice_0.tx_phyready_override = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_phyready_override, pD2dPhy->tx_slice_0.tx_phyready_override);

	// Register: tx_slice_0.tx_phyready_override: APB WR
	pD2dPhy->tx_slice_0.tx_phyready_override =
		((0 << BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_VALUE_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_VALUE_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_phyready_override, pD2dPhy->tx_slice_0.tx_phyready_override);

	// Register: tx_slice_0.tx_phyready_override: APB RD
	pD2dPhy->tx_slice_0.tx_phyready_override = 0x2;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_phyready_override, pD2dPhy->tx_slice_0.tx_phyready_override);

	// Register: tx_slice_0.tx_phyready_override: APB WR
	pD2dPhy->tx_slice_0.tx_phyready_override =
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_bm)	|
		((1 << BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_VALUE_bp) &
		 BLYNX_BOW__TX_SLICE_0_T__TX_PHYREADY_OVERRIDE__OVRD_VALUE_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_TX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__tx_slice_t_t *)0)->tx_phyready_override, pD2dPhy->tx_slice_0.tx_phyready_override);

#if 1 //DV TWEEK
	//d2d_ll_write(0x27009004, 0x58);
    // Register: d2d_reg_block.RxInterfaceControlStatus: APB LL_WR
    pD2dLL->rxInterfaceControlStatus.val =
        ((0x0 << RX_INTERFACE_CONTROL_STATUS__MODE_bp) &
        RX_INTERFACE_CONTROL_STATUS__MODE_bm)	|
        ((0x2 << RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bp) &
        RX_INTERFACE_CONTROL_STATUS__WIDTHPERSLICE_bm)	|
        ((0x1 << RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bp) &
        RX_INTERFACE_CONTROL_STATUS__NUMSLICES_bm)	|
        ((0x1 << RX_INTERFACE_CONTROL_STATUS__LINKRESET_bp) &
        RX_INTERFACE_CONTROL_STATUS__LINKRESET_bm)	|
        ((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYRESET_bp) &
        RX_INTERFACE_CONTROL_STATUS__PHYRESET_bm)	|
        ((0x0 << RX_INTERFACE_CONTROL_STATUS__PHYREADY_bp) &
        RX_INTERFACE_CONTROL_STATUS__PHYREADY_bm);

    d2d_ll_write(D2D_LL_BASE_ADDR + RX_INTERFACE_CONTROL_STATUS, pD2dLL->rxInterfaceControlStatus.val);

#endif
	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB RD
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config = 0x12;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB WR
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB RD
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config = 0x13;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB WR
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB RD
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config = 0x53;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB WR
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB RD
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config = 0x51;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB WR
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB RD
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config = 0x41;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_rx_qpump_vreg_config: APB WR
	pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_DIV_EN_FROM_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_OSC_SLOW_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV1_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV4_RTL_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_SEL_DIV8_RTL_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_START_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_RX_QPUMP_VREG_CONFIG__QPUMP_VREG_EN_FROM_RTL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_rx_qpump_vreg_config, pD2dPhy->rx_slice_0.rx_rx_qpump_vreg_config);

	// Register: rx_slice_0.rx_wild_clk_config0: APB RD
	pD2dPhy->rx_slice_0.rx_wild_clk_config0 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_wild_clk_config0, pD2dPhy->rx_slice_0.rx_wild_clk_config0);

	// Register: rx_slice_0.rx_wild_clk_config0: APB RD
	pD2dPhy->rx_slice_0.rx_wild_clk_config0 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_wild_clk_config0, pD2dPhy->rx_slice_0.rx_wild_clk_config0);

	// Register: rx_slice_0.rx_wild_clk_config1: APB RD
	pD2dPhy->rx_slice_0.rx_wild_clk_config1 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_wild_clk_config1, pD2dPhy->rx_slice_0.rx_wild_clk_config1);

	// Register: rx_slice_0.rx_wild_clk_config1: APB WR
	pD2dPhy->rx_slice_0.rx_wild_clk_config1 =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_wild_clk_config1, pD2dPhy->rx_slice_0.rx_wild_clk_config1);

	// Register: rx_slice_0.rx_wild_clk_config1: APB RD
	pD2dPhy->rx_slice_0.rx_wild_clk_config1 = 0x1;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_wild_clk_config1, pD2dPhy->rx_slice_0.rx_wild_clk_config1);

	// Register: rx_slice_0.rx_wild_clk_config1: APB WR
	pD2dPhy->rx_slice_0.rx_wild_clk_config1 =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_WILD_CLK_CONFIG1__MPCG_WILD_RST_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_wild_clk_config1, pD2dPhy->rx_slice_0.rx_wild_clk_config1);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3f3f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3fff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_clkrx_config: APB RD
	pD2dPhy->rx_slice_0.rx_clkrx_config = 0x12;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clkrx_config, pD2dPhy->rx_slice_0.rx_clkrx_config);

	// Register: rx_slice_0.rx_clkrx_config: APB WR
	pD2dPhy->rx_slice_0.rx_clkrx_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_DISABLE_VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_DISABLE_VAL_bm)	|
		((4 << BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_FE_BIAS_TRIM_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_FE_BIAS_TRIM_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_TIA_SEL_LF_RES_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_TIA_SEL_LF_RES_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_STG1_SEL_LF_RES_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLKRX_CONFIG__CLKRX_STG1_SEL_LF_RES_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clkrx_config, pD2dPhy->rx_slice_0.rx_clkrx_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0xffff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3f3f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3fff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x82c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x828;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x820;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x820;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x800;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x802;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x803;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x802;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x806;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x80e;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x81e;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83e;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_clkrx_config: APB RD
	pD2dPhy->rx_slice_0.rx_clkrx_config = 0x13;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clkrx_config, pD2dPhy->rx_slice_0.rx_clkrx_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x83c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0xffff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3f3f;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((63 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB RD
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state = 0x3fff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_clk_div_state: APB WR
	pD2dPhy->rx_slice_0.rx_dll_clk_div_state =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETH_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CLK_DIV_STATE__DLL_SHIFT_REG_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_clk_div_state, pD2dPhy->rx_slice_0.rx_dll_clk_div_state);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x82c;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x828;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x820;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x820;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x800;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_deser_ratio_ctrl: APB RD
	pD2dPhy->rx_slice_0.rx_deser_ratio_ctrl = 0x3;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_ratio_ctrl, pD2dPhy->rx_slice_0.rx_deser_ratio_ctrl);

	// Register: rx_slice_0.rx_deser_lat_trans_W0: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W0 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W0, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W0);

	// Register: rx_slice_0.rx_deser_lat_trans_W1: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W1 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W1, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W1);

	// Register: rx_slice_0.rx_deser_lat_trans_W2: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W2 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W2, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W2);

	// Register: rx_slice_0.rx_deser_lat_trans_W3: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W3 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W3, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W3);

	// Register: rx_slice_0.rx_deser_lat_trans_W4: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W4 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W4, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W4);

	// Register: rx_slice_0.rx_deser_lat_trans_W5: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W5 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W5, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W5);

	// Register: rx_slice_0.rx_deser_lat_trans_W6: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W6 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W6, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W6);

	// Register: rx_slice_0.rx_deser_lat_trans_W7: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W7 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W7, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W7);

	// Register: rx_slice_0.rx_deser_lat_trans_W8: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W8 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W8, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W8);

	// Register: rx_slice_0.rx_deser_lat_trans_W9: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W9 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W9, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W9);

	// Register: rx_slice_0.rx_deser_lat_trans_W10: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W10 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W10, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W10);

	// Register: rx_slice_0.rx_deser_lat_trans_W11: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W11 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W11, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W11);

	// Register: rx_slice_0.rx_deser_lat_trans_W12: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W12 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W12, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W12);

	// Register: rx_slice_0.rx_deser_lat_trans_W13: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W13 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W13, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W13);

	// Register: rx_slice_0.rx_deser_lat_trans_W14: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W14 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W14, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W14);

	// Register: rx_slice_0.rx_deser_lat_trans_W15: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W15 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W15, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W15);

	// Register: rx_slice_0.rx_deser_lat_trans_W16: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W16 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W16, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W16);

	// Register: rx_slice_0.rx_deser_lat_trans_W17: APB RD
	pD2dPhy->rx_slice_0.rx_deser_lat_trans_W17 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_deser_lat_trans_W17, pD2dPhy->rx_slice_0.rx_deser_lat_trans_W17);

	// Register: rx_slice_0.rx_clk_en: APB RD
	pD2dPhy->rx_slice_0.rx_clk_en = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_en: APB WR
	pD2dPhy->rx_slice_0.rx_clk_en =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_en: APB RD
	pD2dPhy->rx_slice_0.rx_clk_en = 0x1;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_en: APB WR
	pD2dPhy->rx_slice_0.rx_clk_en =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_en: APB RD
	pD2dPhy->rx_slice_0.rx_clk_en = 0x3;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_en: APB WR
	pD2dPhy->rx_slice_0.rx_clk_en =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_en: APB RD
	pD2dPhy->rx_slice_0.rx_clk_en = 0x7;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_en: APB WR
	pD2dPhy->rx_slice_0.rx_clk_en =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_DES_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_REG_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_RTL_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_EN__MPCG_CLK_LINK_LAYER_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_en, pD2dPhy->rx_slice_0.rx_clk_en);

	// Register: rx_slice_0.rx_clk_sel: APB RD
	pD2dPhy->rx_slice_0.rx_clk_sel = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_sel, pD2dPhy->rx_slice_0.rx_clk_sel);

	// Register: rx_slice_0.rx_clk_sel: APB RD
	pD2dPhy->rx_slice_0.rx_clk_sel = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_sel, pD2dPhy->rx_slice_0.rx_clk_sel);

	// Register: rx_slice_0.rx_clk_sel: APB RD
	pD2dPhy->rx_slice_0.rx_clk_sel = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_sel, pD2dPhy->rx_slice_0.rx_clk_sel);

	// Register: rx_slice_0.rx_clk_sel: APB RD
	pD2dPhy->rx_slice_0.rx_clk_sel = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_sel, pD2dPhy->rx_slice_0.rx_clk_sel);

	// Register: rx_slice_0.rx_clk_sel: APB WR
	pD2dPhy->rx_slice_0.rx_clk_sel =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_DES_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_DES_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_REG_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_REG_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_RTL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_RTL_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_LINK_LAYER_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_CLK_SEL__MPCG_SEL_LINK_LAYER_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_clk_sel, pD2dPhy->rx_slice_0.rx_clk_sel);

	// Register: rx_slice_0.rx_sel_deser_mux: APB RD
	pD2dPhy->rx_slice_0.rx_sel_deser_mux = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_sel_deser_mux, pD2dPhy->rx_slice_0.rx_sel_deser_mux);

	// Register: rx_slice_0.rx_sel_deser_mux: APB WR
	pD2dPhy->rx_slice_0.rx_sel_deser_mux =
		((2 << BLYNX_BOW__RX_SLICE_0_T__RX_SEL_DESER_MUX__MPCG_SEL_DESER_MUX_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_SEL_DESER_MUX__MPCG_SEL_DESER_MUX_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_sel_deser_mux, pD2dPhy->rx_slice_0.rx_sel_deser_mux);

	// Register: rx_slice_0.rx_shift_reg_out_seth_n: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_out_seth_n = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_out_seth_n, pD2dPhy->rx_slice_0.rx_shift_reg_out_seth_n);

	// Register: rx_slice_0.rx_shift_reg_out_setl: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_out_setl = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_out_setl, pD2dPhy->rx_slice_0.rx_shift_reg_out_setl);

	// Register: rx_slice_0.rx_shift_reg_mux_sel_seth_n: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n = 0xffff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_mux_sel_seth_n, pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n);

	// Register: rx_slice_0.rx_shift_reg_mux_sel_seth_n: APB WR
	pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_MUX_SEL_SETH_N__MPCG_SHIFT_REG_MUX_SEL_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_MUX_SEL_SETH_N__MPCG_SHIFT_REG_MUX_SEL_SETH_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_mux_sel_seth_n, pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n);

	// Register: rx_slice_0.rx_shift_reg_mux_sel_setl: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_setl = 0xffff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_mux_sel_setl, pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_setl);

	// Register: rx_slice_0.rx_shift_reg_mux_sel_setl: APB WR
	pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_setl =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_MUX_SEL_SETL__MPCG_SHIFT_REG_MUX_SEL_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_MUX_SEL_SETL__MPCG_SHIFT_REG_MUX_SEL_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_mux_sel_setl, pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_setl);

	// Register: rx_slice_0.rx_shift_reg_out_seth_n: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_out_seth_n = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_out_seth_n, pD2dPhy->rx_slice_0.rx_shift_reg_out_seth_n);

	// Register: rx_slice_0.rx_shift_reg_out_seth_n: APB WR
	pD2dPhy->rx_slice_0.rx_shift_reg_out_seth_n =
		((65535 << BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_OUT_SETH_N__MPCG_SHIFT_REG_OUT_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_OUT_SETH_N__MPCG_SHIFT_REG_OUT_SETH_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_out_seth_n, pD2dPhy->rx_slice_0.rx_shift_reg_out_seth_n);

	// Register: rx_slice_0.rx_shift_reg_out_setl: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_out_setl = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_out_setl, pD2dPhy->rx_slice_0.rx_shift_reg_out_setl);

	// Register: rx_slice_0.rx_shift_reg_out_setl: APB WR
	pD2dPhy->rx_slice_0.rx_shift_reg_out_setl =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_OUT_SETL__MPCG_SHIFT_REG_OUT_SETL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_OUT_SETL__MPCG_SHIFT_REG_OUT_SETL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_out_setl, pD2dPhy->rx_slice_0.rx_shift_reg_out_setl);

	// Register: rx_slice_0.rx_shift_reg_mux_sel_seth_n: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_mux_sel_seth_n, pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n);

	// Register: rx_slice_0.rx_shift_reg_mux_sel_seth_n: APB WR
	pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n =
		((65535 << BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_MUX_SEL_SETH_N__MPCG_SHIFT_REG_MUX_SEL_SETH_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_SHIFT_REG_MUX_SEL_SETH_N__MPCG_SHIFT_REG_MUX_SEL_SETH_N_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_mux_sel_seth_n, pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_seth_n);

	// Register: rx_slice_0.rx_shift_reg_mux_sel_setl: APB RD
	pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_setl = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_shift_reg_mux_sel_setl, pD2dPhy->rx_slice_0.rx_shift_reg_mux_sel_setl);

	// Register: rx_slice_0.rx_dll_config: APB RD
	pD2dPhy->rx_slice_0.rx_dll_config = 0x802;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_config: APB WR
	pD2dPhy->rx_slice_0.rx_dll_config =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_DIV_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_DAC_INT_SET_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PPHD_DAC_BIAS_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_INT_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_LVL_RST_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_CLK_SAMP_CAL_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_WILD_CLK_CAL_EN_bm)	|
		((8 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_CONFIG__DLL_PBD_SREF_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_config, pD2dPhy->rx_slice_0.rx_dll_config);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_0: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_0 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_0, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_0);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_0: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_0 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_0__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_0__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_0, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_0);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_1: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_1 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_1, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_1);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_1: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_1 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_1__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_1__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_1, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_1);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_2: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_2 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_2, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_2);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_2: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_2 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_2__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_2__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_2, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_2);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_3: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_3 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_3, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_3);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_3: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_3 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_3__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_3__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_3, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_3);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_4: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_4 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_4, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_4);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_4: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_4 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_4__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_4__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_4, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_4);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_5: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_5 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_5, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_5);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_5: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_5 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_5__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_5__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_5, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_5);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_6: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_6 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_6, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_6);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_6: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_6 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_6__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_6__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_6, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_6);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_7: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_7 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_7, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_7);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_7: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_7 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_7__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_PPHD_7__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_pphd_7, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_pphd_7);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_ev, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev =
		((851 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_INT_EV__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_INT_EV__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_ev, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_ev);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_od, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od =
		((851 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_INT_OD__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_R_INT_OD__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_r_int_od, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_r_int_od);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_0: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_0 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_0, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_0);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_0: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_0 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_0__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_0__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_0, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_0);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_1: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_1 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_1, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_1);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_1: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_1 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_1__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_1__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_1, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_1);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_2: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_2 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_2, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_2);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_2: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_2 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_2__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_2__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_2, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_2);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_3: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_3 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_3, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_3);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_3: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_3 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_3__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_3__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_3, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_3);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_4: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_4 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_4, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_4);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_4: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_4 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_4__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_4__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_4, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_4);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_5: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_5 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_5, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_5);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_5: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_5 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_5__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_5__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_5, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_5);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_6: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_6 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_6, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_6);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_6: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_6 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_6__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_6__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_6, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_6);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_7: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_7 = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_7, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_7);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_7: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_7 =
		((256 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_7__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_PPHD_7__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_pphd_7, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_pphd_7);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_int: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_int = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_int, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_int);

	// Register: rx_slice_0.rx_dll_ovrd_val_ctrl_d_int: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_int =
		((2052 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_INT__VAL_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_VAL_CTRL_D_INT__VAL_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_val_ctrl_d_int, pD2dPhy->rx_slice_0.rx_dll_ovrd_val_ctrl_d_int);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_r: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_r: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_r: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_r: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_r: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r = 0x1ff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_r: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__PPHD_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_EV_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_R__INT_OD_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_r, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_r);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_d: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_d, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_d: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_d, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_d: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d = 0xff;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_d, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d);

	// Register: rx_slice_0.rx_dll_ovrd_accum_ctrl_d: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d =
		((255 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__PPHD_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_OVRD_ACCUM_CTRL_D__CTRL_D_INT_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ovrd_accum_ctrl_d, pD2dPhy->rx_slice_0.rx_dll_ovrd_accum_ctrl_d);

	// Register: rx_slice_0.rx_dll_misc_ctrl: APB RD
	pD2dPhy->rx_slice_0.rx_dll_misc_ctrl = 0x11;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_misc_ctrl, pD2dPhy->rx_slice_0.rx_dll_misc_ctrl);

	// Register: rx_slice_0.rx_dll_misc_ctrl: APB WR
	pD2dPhy->rx_slice_0.rx_dll_misc_ctrl =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__GATE_CLK_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__GATE_CLK_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__RST_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__RST_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__BYP_RST_SYNC_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__BYP_RST_SYNC_bm)	|
		((2 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__DSM_SHIFT_AMT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__DSM_SHIFT_AMT_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_misc_ctrl, pD2dPhy->rx_slice_0.rx_dll_misc_ctrl);

	// Register: rx_slice_0.rx_dll_misc_ctrl: APB RD
	pD2dPhy->rx_slice_0.rx_dll_misc_ctrl = 0x10;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_misc_ctrl, pD2dPhy->rx_slice_0.rx_dll_misc_ctrl);

	// Register: rx_slice_0.rx_dll_misc_ctrl: APB WR
	pD2dPhy->rx_slice_0.rx_dll_misc_ctrl =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__GATE_CLK_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__GATE_CLK_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__RST_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__RST_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__BYP_RST_SYNC_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__BYP_RST_SYNC_bm)	|
		((2 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__DSM_SHIFT_AMT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_MISC_CTRL__DSM_SHIFT_AMT_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_misc_ctrl, pD2dPhy->rx_slice_0.rx_dll_misc_ctrl);

	// Register: rx_slice_0.rx_dll_ld_ctrl: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ld_ctrl = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ld_ctrl, pD2dPhy->rx_slice_0.rx_dll_ld_ctrl);

	// Register: rx_slice_0.rx_dll_ld_ctrl: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ld_ctrl =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__LOCK_DET_RST_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__LOCK_DET_RST_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_D_INT_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_D_INT_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_D_INT_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ld_ctrl, pD2dPhy->rx_slice_0.rx_dll_ld_ctrl);

	// Register: rx_slice_0.rx_dll_ld_ctrl: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ld_ctrl = 0x10;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ld_ctrl, pD2dPhy->rx_slice_0.rx_dll_ld_ctrl);

	// Register: rx_slice_0.rx_dll_ld_ctrl: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ld_ctrl =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__LOCK_DET_RST_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__LOCK_DET_RST_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_D_INT_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_EV_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_D_INT_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_D_INT_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ld_ctrl, pD2dPhy->rx_slice_0.rx_dll_ld_ctrl);

	// Register: rx_slice_0.rx_dll_ld_ctrl: APB RD
	pD2dPhy->rx_slice_0.rx_dll_ld_ctrl = 0x30;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ld_ctrl, pD2dPhy->rx_slice_0.rx_dll_ld_ctrl);

	// Register: rx_slice_0.rx_dll_ld_ctrl: APB WR
	pD2dPhy->rx_slice_0.rx_dll_ld_ctrl =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__LOCK_DET_RST_N_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__LOCK_DET_RST_N_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__OVRD_CTRL_D_INT_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_EV_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_R_INT_OD_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__FORCE_CTRL_D_INT_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_EV_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_EV_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_OD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_R_INT_OD_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_D_INT_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_DLL_LD_CTRL__SEL_LIVE_CTRL_D_INT_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_dll_ld_ctrl, pD2dPhy->rx_slice_0.rx_dll_ld_ctrl);

	// Register: rx_slice_0.rx_link_layer_clock_sel: APB RD
	pD2dPhy->rx_slice_0.rx_link_layer_clock_sel = 0x4;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_link_layer_clock_sel, pD2dPhy->rx_slice_0.rx_link_layer_clock_sel);

	// Register: rx_slice_0.rx_link_layer_clock_sel: APB WR
	pD2dPhy->rx_slice_0.rx_link_layer_clock_sel =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_link_layer_clock_sel, pD2dPhy->rx_slice_0.rx_link_layer_clock_sel);

	// Register: rx_slice_0.rx_link_layer_clock_sel: APB RD
	pD2dPhy->rx_slice_0.rx_link_layer_clock_sel = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_link_layer_clock_sel, pD2dPhy->rx_slice_0.rx_link_layer_clock_sel);

	// Register: rx_slice_0.rx_link_layer_clock_sel: APB WR
	pD2dPhy->rx_slice_0.rx_link_layer_clock_sel =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_link_layer_clock_sel, pD2dPhy->rx_slice_0.rx_link_layer_clock_sel);

	// Register: rx_slice_0.rx_link_layer_clock_sel: APB RD
	pD2dPhy->rx_slice_0.rx_link_layer_clock_sel = 0x1;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_link_layer_clock_sel, pD2dPhy->rx_slice_0.rx_link_layer_clock_sel);

	// Register: rx_slice_0.rx_link_layer_clock_sel: APB WR
	pD2dPhy->rx_slice_0.rx_link_layer_clock_sel =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_ASYNC_CLK_EN_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__PHY_LINK_LAYER_SYNC_CLK_EN_bm)	|
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_LINK_LAYER_CLOCK_SEL__APB_CLK_EN_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_link_layer_clock_sel, pD2dPhy->rx_slice_0.rx_link_layer_clock_sel);

	// Register: rx_slice_0.rx_phyready_override: APB RD
	pD2dPhy->rx_slice_0.rx_phyready_override = 0x0;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_phyready_override, pD2dPhy->rx_slice_0.rx_phyready_override);

	// Register: rx_slice_0.rx_phyready_override: APB WR
	pD2dPhy->rx_slice_0.rx_phyready_override =
		((0 << BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_VALUE_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_VALUE_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_phyready_override, pD2dPhy->rx_slice_0.rx_phyready_override);

	// Register: rx_slice_0.rx_phyready_override: APB RD
	pD2dPhy->rx_slice_0.rx_phyready_override = 0x2;

	d2d_phy_read(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_phyready_override, pD2dPhy->rx_slice_0.rx_phyready_override);

	// Register: rx_slice_0.rx_phyready_override: APB WR
	pD2dPhy->rx_slice_0.rx_phyready_override =
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_bm)	|
		((1 << BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_VALUE_bp) &
		 BLYNX_BOW__RX_SLICE_0_T__RX_PHYREADY_OVERRIDE__OVRD_VALUE_bm);

	d2d_phy_write(D2D_PHY_BASE_ADDR + BOW_RX_SLICE_0_ADDR +
			(int32_t)&((blynx_bow__rx_slice_t_t *)0)->rx_phyready_override, pD2dPhy->rx_slice_0.rx_phyready_override);

 	printf("d2d_init_mode is completed in d2d_mode_init .c file\r\n");
	return 0;
}

