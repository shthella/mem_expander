/* SPDX-License-Identifier: Apache-2.0 */
#include <stdio.h>
#include "common.h"
#include "uart.h"

void __attribute__((optimize("O0"))) wait(int cnt)
{
	while(cnt != 0)
		cnt--;
}
	

#ifdef GENERIC_MC_CONFIG
void gfh_mc_init() 
{
	printf("gf_mc init is started from gfh_mc.c\r\n");
	unsigned int val;

	gfh_write_mc(PAGED_REG_SEL, 0x0);

	val = 0;
	val |= (0xC << ADDRESS_MAP0__ADDR_AREA_LENGTH_bp) & ADDRESS_MAP0__ADDR_AREA_LENGTH_bm;
	val | = (0x1 << ADDRESS_MAP0__CHIP_SELECT_NUMB_bp) & ADDRESS_MAP0__CHIP_SELECT_NUMB_bm;
	gfh_write_mc(ADDRESS_MAP0, val);

	gfh_write_mc(ADDRESS_MAP1, 0x0);

	/* Hash Mapping */
	val = 0xaaaaa800;
	val |= (0x0 << REGION_ADDR_HASH_CONFIG0__BANK_ADDR_HASH_EN_bp) & REGION_ADDR_HASH_CONFIG0__BANK_ADDR_HASH_EN_bm;
	gfh_write_mc(REGION_ADDR_HASH_CONFIG0, val);

	val = 0x33333334;
	val |= (0x0 << REGION_ADDR_HASH_CONFIG1__BG_ADDR_B0_HASH_EN_bp) & REGION_ADDR_HASH_CONFIG1__BG_ADDR_B0_HASH_EN_bm;
	gfh_write_mc(REGION_ADDR_HASH_CONFIG1, val);

	val = 0xccccccc8;
	val |= (0x0 << REGION_ADDR_HASH_CONFIG2__BG_ADDR_B1_HASH_EN_bp) & REGION_ADDR_HASH_CONFIG2__BG_ADDR_B1_HASH_EN_bm;
	gfh_write_mc(REGION_ADDR_HASH_CONFIG2, val);
	gfh_write_mc(REGION_ADDR_HASH_CONFIG3, 0x0);
	gfh_write_mc(REGION_ADDR_HASH_CONFIG4, 0x0);
	gfh_write_mc(REGION_ADDR_HASH_CONFIG5, 0x0);

	/* DDR4 burst length */
	val = 0;
	val |= (0x3 << REGION_ADDR_MAP_CONFIG0__COL_ADDR_SEG0_WIDTH_bp) & REGION_ADDR_MAP_CONFIG0__COL_ADDR_SEG0_WIDTH_bm;
	val |= (0x7 << REGION_ADDR_MAP_CONFIG0__COL_ADDR_SEG1_WIDTH_bp) & REGION_ADDR_MAP_CONFIG0__COL_ADDR_SEG1_WIDTH_bm;
	val |= (0xE << REGION_ADDR_MAP_CONFIG0__ROW_ADDR_SEG0_WIDTH_bp) & REGION_ADDR_MAP_CONFIG0__ROW_ADDR_SEG0_WIDTH_bm;
	gfh_write_mc(REGION_ADDR_MAP_CONFIG0, val);

	/* DDR4 data width */
	/* No change in Reset value - Valid only when hash is disabled */
	gfh_write_mc(REGION_ADDR_MAP_CONFIG1, 0x11083);

	/* No change in Reset value - Valid only when hash is disabled */
	gfh_write_mc(REGION_ADDR_MAP_CONFIG2, 0x40f);

	/* No change in Reset value - Valid only when hash is disabled */
	gfh_write_mc(REGION_ADDR_MAP_CONFIG3, 0x1c6);

	/* Valid only when hash is disabled */
	val = 0;
	val |= (0x1F << REGION_ADDR_MAP_CONFIG4__CS_ADDR_BITS_MAPPING_bp) & REGION_ADDR_MAP_CONFIG4__CS_ADDR_BITS_MAPPING_bw;
	gfh_write_mc(REGION_ADDR_MAP_CONFIG4, val);

	/* SPD: */
	val = 0;
	val |= (0x4 << DEVICE_TYPE__DATA_WIDTH_bp) & DEVICE_TYPE__DATA_WIDTH_bm;
	val |= (0x1 << DEVICE_TYPE__BURST_LENGTH_bp) & DEVICE_TYPE__BURST_LENGTH_bm;
	val |= (0x1 << DEVICE_TYPE__DEVICE_DIE_DATA_WIDTH_bp) & DEVICE_TYPE__DEVICE_DIE_DATA_WIDTH_bm;
	val |= (0x1 << DEVICE_TYPE__DIMM_TYPE_bp) & DEVICE_TYPE__DIMM_TYPE_bm;
	gfh_write_mc(DEVICE_TYPE, val);

	/* TODO - Need to test other features based on SoC for further bringup */
	val = 0;
	val = (0x1 << CH__R_A_S_CNTL__ECC_ENB_bp) & CH__R_A_S_CNTL__ECC_ENB_bm;
	gfh_write_mc(CH__R_A_S_CNTL, val);

	/* TODO - Need to test other features based on SoC for further bringup */
	val = 0;
	val |= (0x1 << CH_DEVICE_MODE__PULL_IN_REF_ENABLE_bp) & CH_DEVICE_MODE__PULL_IN_REF_ENABLE_bm;
	val |= (0x1 << CH_DEVICE_MODE__ZQC_AFTER_SR_bp) & CH_DEVICE_MODE__ZQC_AFTER_SR_bm;
	val |= (0x1 << CH_DEVICE_MODE__AUTO_REF_ENABLE_CS0_bp) & CH_DEVICE_MODE__AUTO_REF_ENABLE_CS0_bm;
	val |= (0x1 << CH_DEVICE_MODE__AUTO_REF_ENABLE_CS1_bp) & CH_DEVICE_MODE__AUTO_REF_ENABLE_CS1_bm;
	val |= (0x1 << CH_DEVICE_MODE__AUTO_REF_ENABLE_CS2_bp) & CH_DEVICE_MODE__AUTO_REF_ENABLE_CS2_bm;
	val |= (0x1 << CH_DEVICE_MODE__AUTO_REF_ENABLE_CS3_bp) & CH_DEVICE_MODE__AUTO_REF_ENABLE_CS3_bm;
	val |= (0x1 << CH_DEVICE_MODE__INVALID_CMD_PIN_LEVEL_bp) & CH_DEVICE_MODE__INVALID_CMD_PIN_LEVEL_bp;
	gfh_write_mc(CH_DEVICE_MODE, val);

	/* Pending: why [19:16] is 0xE ? */
	val = 0;
	val |= (0xF << CH_ODT_CTRL0__ODT_WR_EN_CS0_bp) & CH_ODT_CTRL0__ODT_WR_EN_CS0_bm;
	val |= (0xF << CH_ODT_CTRL0__ODT_WR_EN_CS1_bp) & CH_ODT_CTRL0__ODT_WR_EN_CS1_bm;
	val |= (0xF << CH_ODT_CTRL0__ODT_WR_EN_CS2_bp) & CH_ODT_CTRL0__ODT_WR_EN_CS2_bm;
	val |= (0xF << CH_ODT_CTRL0__ODT_WR_EN_CS3_bp) & CH_ODT_CTRL0__ODT_WR_EN_CS3_bm;
	val |= (0xE << CH_ODT_CTRL0__ODT_RD_EN_CS0_bp) & CH_ODT_CTRL0__ODT_RD_EN_CS0_bm;
	val |= (0xD << CH_ODT_CTRL0__ODT_RD_EN_CS1_bp) & CH_ODT_CTRL0__ODT_RD_EN_CS1_bm;
	val |= (0xB << CH_ODT_CTRL0__ODT_RD_EN_CS2_bp) & CH_ODT_CTRL0__ODT_RD_EN_CS2_bm;
	val |= (0x7 << CH_ODT_CTRL0__ODT_RD_EN_CS3_bp) & CH_ODT_CTRL0__ODT_RD_EN_CS3_bm;
	gfh_write_mc(CH_ODT_CTRL0, val);

	/* Pending: Designer need to update */
	val = (0x2 << CHCS_DEVICE_CONFIG_ODT__DQ_ODT_bp) & CHCS_DEVICE_CONFIG_ODT__DQ_ODT_bm;
	gfh_write_mc(CHCS_DEVICE_CONFIG_ODT, val);

	val = (0x1 << PAGED_REG_SEL__CHCS_CONFIG_CS_SEL_bp) & PAGED_REG_SEL__CHCS_CONFIG_CS_SEL_bm;
	gfh_write_mc(PAGED_REG_SEL, val);

	/* Pending: Designer need to update */
	val = (0x2 << CHCS_DEVICE_CONFIG_ODT__DQ_ODT_bp) & CHCS_DEVICE_CONFIG_ODT__DQ_ODT_bm;
	gfh_write_mc(CHCS_DEVICE_CONFIG_ODT, val);

	/* SPD: */
	val = (0x18 << CH_DEVICE_CONFIG0__RL_bp) & CH_DEVICE_CONFIG0__RL_bm;
	val |= (0x18 << CH_DEVICE_CONFIG0__NWR_bp) & CH_DEVICE_CONFIG0__NWR_bm;
	val | = (0x10 << CH_DEVICE_CONFIG0__WL_bp) & CH_DEVICE_CONFIG0__WL_bm;
	gfh_write_mc(CH_DEVICE_CONFIG0, val);

	/* Designer need to update - which feature need to be enabled */
	gfh_write_mc(CH_DEVICE_CONFIG1, 0);

	/* Designer need to update - which feature need to be enabled */
	gfh_write_mc(CH_DEVICE_CONFIG2, 0);

	/* Designer need to update - which feature need to be enabled */
	/* for basic bringup we can keep it as demo init seq */
	gfh_write_mc(CH_DEVICE_DDR4_CONFIG0, 0x600006);
	gfh_write_mc(CH_DEVICE_DDR4_CONFIG1, 0x80000);

	/* it's for simulation in case of skip training mode. In FW not needed  */
	gfh_write_mc(CH__D_R_A_M_TIMING_INIT0, 0x64000140);
	gfh_write_mc(CH__D_R_A_M_TIMING_INIT1, 0x28010);
	gfh_write_mc(CH__D_R_A_M_TIMING_INIT2, 0x11000);
	
	/* [PM]: Table 173 of DDR4 spec) fixed for all speed(min value) */
	gfh_write_mc(CH__D_R_A_M_TIMING_ZQC0, 0x40020080);


	/* [PM]: Keep tMRD = 8 for all. tMOD in JEDEC is max(24nCK, 15ns).
	 * As DDR4 highest speed is 1.6GHz, so 15ns <= 24nCK.Keep tMOD = 0x18 
	 * for all is right too fixed for all speed(min value) */
	gfh_write_mc(CH__D_R_A_M_TIMING_MR0, 0x180800);

	/* [PM]: These values are for DDR freq 3200.
	 * If we keep the same value for lower speed, this will still work with 
	 * a hit in performance */
	gfh_write_mc(CH__D_R_A_M_TIMING_CORE0, 0x4c183422);

	/* SPD: [PM]: These values are for 3200. If we keep the same value for 
	 * lower speed, this will still work with a hit in performance.
	 * tRTP = mas (4nCK, 7.5ns).  So if fw need program it to be exactly 
	 * correct, it need calculate it based on the speed. Some setting like
	 * tRFC is Capacity related, i.e., how many rows are there in a bank, 
	 * better to read tRFC from SPD
	   tRTP = 4nck (min)
	   tWR = 15ns(min)
	   tWTR_L = 4nck (min)
	   tRRD = 4nck
	   fixed for all speeed, but dependent on page size */
	gfh_write_mc(CH__D_R_A_M_TIMING_CORE1, 0xc180c08);

	/* [PM]: There is no such limitation for precharge to precharge delay
	 * so it is kept as 0. DDR4 need to take care of tRP & tCCD_L. tRP is
	 * defined in ns. So speed related. This values are ok. 
	 * depends on speed bin and frequency 
	 * tCCD_L = 5nck(min fixed for all speed) */
	gfh_write_mc(CH__D_R_A_M_TIMING_CORE2, 0x181808);

	/* [PM]: This are max(2nCK, 2.5ns)., tCCD_S = 4 and can be same for
	 * all speed. tWTR_s and RRD_s is per speed
	   tWTR_S = 2nck(min)
	   tCCD_S = 4nck(min)
	   tRRD_s = 4nck(min)
	   same for all speed */
	gfh_write_mc(CH__D_R_A_M_TIMING_CORE3, 0x4404);

	/* [PM]: We are not supporting 3D Stack not required for ddr4 */
	gfh_write_mc(CH__D_R_A_M_TIMING_CORE4, 0);

	/* SPD: [PM]: tRFC from SPD, and convert to nCK. tREFI is 7.8us, and convert
	 * to refresh clock cycles (a fixed low speed clock, mc_ref_clk). */
	gfh_write_mc(CH__D_R_A_M_TIMING_REF0, 0xc00100);

	/* SPD: [PM]: MC can also send self refresh command so this value need t0o
	 * come from SPD and it is speed specific */
	gfh_write_mc(CH__D_R_A_M_TIMING_SR0, 0x40009110);

	/* SPD: [PM] These values are based on speed and should come from SPD.
	 * For 3200 they are as follows -
	   tCKSRX = max(5nCK,10ns)
	   tCKE = max(3nCK, 5ns)
	   tACTPD, tPRPDEN, tREFPDEN= 0x2
	   tCKSRE = max(5nCK,10ns)
	   tXP = max(4nCK,6ns ) */
	gfh_write_mc(CH__D_R_A_M_TIMING_PD0, 0x1008280a);

	/* [PM]: DDR4 ODT is controlled by ODT pin, and the on/off timing is fixed to WL-2 */
	gfh_write_mc(CH__D_R_A_M_TIMING_ODT0, 0);

	/* For LPDDR4/5 */
	gfh_write_mc(CH__D_R_A_M_TIMING_MISC0, 0);

	/* SPD: [PM]: these are for timing check. tMPX_LH = 12 ns for 3200.
	 * As CKE toggle is very less, so keep tMPX_LH = 0x14 for all speed
	 * is also fine. don't affect much on performance.
	 * This value should come from SPD as this is speed specific.
	 * Rest of the values are fixed and shown below.
	   bit[25:20] tMRD_PDA = 0x10 
	   bit[17:16] tMPRR = 0x1     
	   bit[12:8] tMPX_LH = 0x14
	   bit[5:0] tCPDED = 0x4 */
	gfh_write_mc(CH__D_R_A_M_TIMING_MISC1, 0x1011404);

	/* [PM]: Rank switching timiing. Fixed for all speed. Should be same
	 * as tCCD + Preamble + Postamble + Extra Gap. rd2wr can programed to
	 * 2 I think. it is + RL - WL + 1 + preamble + postamble.
	 * it is defined as extra delay. Following values are good to go */
	gfh_write_mc(CH__D_R_A_M_TIMING_OFFSPEC0, 0x70008);

	/* [PM]: For debug only, for normal mode, keep these as zero. */
	gfh_write_mc(CH__D_R_A_M_TIMING_OFFSPEC1, 0);

	/* [PM]: Only valid during CRC & CA Parity check failure.
	 * It is not a DDR timing. RTL:
	 * retry_delay_rd = (rdata_round_dly > crc_alert_round_rd_dly) ? rdata_round_dly
	 * : crc_alert_round_rd_dly; 
	 * It is calculated round dly. If not enabled retry feature,
	 * can keep these as 0x1 which means take the command as safe on the next cycle.
	 * For retry window only pass that delay window, the commands are taken as safe,
	 * don't need retry. */
	gfh_write_mc(CH__D_R_A_M_TIMING_RETRY, 0x101);

	/* [PM]: Post package repair mode. When PPR is enabled, we need performance.
	 * I mean, these PPR timing is only for the PPR process. so keep these value same
	 * as 3200 for all speed is fine. only some cycles difference on PPR process.
	 * But after PPR is done, normal write/read still works well with performance. */
	gfh_write_mc(CH__D_R_A_M_TIMING_PPR0, 0xa0);

	/* [PM]: Post package repair mode. Same as above */
	gfh_write_mc(CH__D_R_A_M_TIMING_PPR1, 0x5020);

	/* [PM]: can keep the current value for all speed.
	   tCMD_GEAR = tMOD = 24nCK
	   tSYNC_GEAR = tMOD + 4nCK = 28nCK. */
	gfh_write_mc(CH__D_R_A_M_TIMING_GEARDOWN, 0x181c);

	/* [PM]: Refer to table 48 of RCD. Add zero delay latency buffer,
	 * if parity checking is enabled. */
	gfh_write_mc(CH__F0_R_C0, 0x4000);

	/* [PM]: Refer to table 42 and 39 in RCD */
	gfh_write_mc(CH__F0_R_C2, 0x60b00000);

	/* [PM]: Refer to table 45 in RCD For RDIMM it is 0x4 and LRDIMM it is 0x0.
	 * This is between read/write timing control */
	gfh_write_mc(CH__F0_R_C3, 0x400);

	/* [PM]: tPDM is 1 to 1.3ns  We programmed it as 1.3ns + 0.5nCK.
	   tInDIS from Table 141 of RCD
	   tMRC from Table 141 */
	gfh_write_mc(CH__R_C_D_TIMING0, 0x34102010);

	/* [PM]: Table 143 of RCD, CLA=2. tCKEV => table 141 */
	gfh_write_mc(CH__R_C_D_TIMING1, 0x60806);

	/* SPD: [PM]: 
	   tPDM_WR/RD = for DB. 
	   For RDIMM this to be set to 0x0.
	   for LRDIMM, need to refer from DB spec. Table 144
	   tPDM is same for RDIMM & LRDIMM. it is command progation delay.
	   tPDM_WR / tPDM_RD is MDQS from/to DRAM DQS progation delay.
	   As per table 142 in RCD this tODU = 0xa0 is within range.
	   0xa0 = 160 cycle, = 100ns *1.6GHz
	   tSTAB is good for 5us, table 132 of RCD */
	gfh_write_mc(CH__R_C_D_TIMING2, 0x501f40);

	/* [PM]: tphy_wrlat = tphy_wrcslat = CWL - 5
	   tphy_wrdata = 0x2
	   These are from Synopsys PHY databook - 
	   dwc_ddr43_phy_pub_databook_2.44a.pdf, section 5.1.2.2 DFI write timing parameters */
	gfh_write_mc(CH__D_F_I_PHY_CNTL0, 0x20b0b);

	/* [PM]: from Synopsys data book
	   trddata_en = tphy_rdcslat = RL - 5, RL = 24 */
	gfh_write_mc(CH__D_F_I_PHY_CNTL1, 0x1313);

	/* [PM]:  bit[31:24] tinit_complete = 0xff
	   bit[23:16] tinit_start = 0xff 
	   These two timing is for frequency change only. don't affect the initializaitlon
	   dfi_frequency is for the frequence index selection in PHY. if there is only 1 Pstate.
	   it is always set 0. If multi Pstate is designed, dfi_frequency 
	   is used to select the index when changing frequency. Section
	   6.4.5.1/2 of Synopsys PHY document. Here  dfi_freq means  dfi_frequency
	   interface. Indicate the DDR state if DFI do DDR boot. 0: IDLE, 1: Self-Refresh,
	   2: Power-Down, 3: SR Power-Down. Means after PHY boot & training done.
	   PHY will put DDR into SR, when pass DFI bus to MC. */
	gfh_write_mc(cwD_F_I_PHY_CNTL2, 0xffff0003);

	/* Designer need to update based on feature */
	gfh_write_mc(MISC_CNTL, 0x43);

	/* Designer need to update based on feature */
	gfh_write_mc(RW_ARBITER_CNTL, 0x4017);

	/* Designer need to update based on feature */
	gfh_write_mc(READ_CNTL, 0x5143);

	/* clock gating will enable in any scenario ? */
	gfh_write_mc(CLK_GATING_CNTL, 0x1);

	/* Designer need to update based on feature */
	gfh_write_mc(D_F_I_USER_CMD0 0x10000001);

	/* Designer need to update based on feature */
	gfh_write_mc(CH_DDR_STATUS_OVERWRITE, 0x303);
}
#else
void gfh_mc_init() 
{       
	printf("the gfh_mc_init is called from gfh main\r\n");
	uint32_t val0;
	uint32_t cnt= 0;
		printf("the gfh_mc_init is called from gfh main\r\n");
	printf("the write values isaddr: %08x and dat:%08x\r\n",0x26000ff0,0x494e4348);
	write_mc(0x26000ff0, 0x494e4348);
	printf("the write values isaddr: %08x and dat:%08x\r\n",0x26000ff0,0x494e4348);
	write_mc(0x26000ff4, 0x4f4c4446);
	write_mc(0x26000ff8, 0x20202047);
	write_mc(0x26000ffc, 0x464c4354);
	val0 = read_mc(0x26000ff0);
	val0 = read_mc(0x26000ff4);
	val0 = read_mc(0x26000ff8);
	val0 = read_mc(0x26000ffc);

	//D2d Initialization Starts

	write_mc(0x27009004, 0x49);
	wait(50);
	write_mc(0x27008004, 0x89);
	wait(50);
	write_mc(0x27008004, 0x8);
	wait(50);
	write_mc(0x27009004, 0xa);
	wait(50);
	write_mc(0x27008004, 0xb);
	wait(50);

	// Polling status register
	do{
		val0 =read_mc(0x27009004);
		cnt = cnt +1;
		if(cnt>100){
			//  exit(1);
			//set_gpio(18);
		}
	} while((val0 & 0x3) != 0x3 ); 
#if 0
	if (cnt > 100) {
		printf("D2D INIT Timeout");
		//exit(1);
		set_gpio(18);
	}
#endif

	(*(volatile unsigned long int *)(0x27009800)) = 0x0;
	(*(volatile unsigned long int *)(0x27008800)) = 0x0;

	write_mc(0x27009800, 0x0);
	write_mc(0x27008800, 0x0);

	(*(volatile unsigned long int *)(0x21000640)) = 0x100c ; //cs-2, 4GB
	(*(volatile unsigned long int *)(0x21000644)) = 0x0 ;
	(*(volatile unsigned long int *)(0x2100065c)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000660)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000664)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000670)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000648)) = 0x11073 ;
	(*(volatile unsigned long int *)(0x2100064c)) = 0x11083 ;
	(*(volatile unsigned long int *)(0x21000650)) = 0x40f ;
	(*(volatile unsigned long int *)(0x21000654)) = 0x1c6 ;
	(*(volatile unsigned long int *)(0x21000658)) = 0x1f ;
	(*(volatile unsigned long int *)(0x21000180)) = 0x11140 ;
	(*(volatile unsigned long int *)(0x21000100)) = 0x1 ;
	(*(volatile unsigned long int *)(0x21000184)) = 0x1f94 ;
	(*(volatile unsigned long int *)(0x21000080)) = 0x7bdeffff ;
	(*(volatile unsigned long int *)(0x21000008)) = 0x0 ;
	(*(volatile unsigned long int *)(0x2100019c)) = 0x2 ;
	(*(volatile unsigned long int *)(0x21000008)) = 0x1 ;
	(*(volatile unsigned long int *)(0x2100019c)) = 0x2 ;
	(*(volatile unsigned long int *)(0x21000008)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000188)) = 0x1018180 ;
	(*(volatile unsigned long int *)(0x2100018c)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000190)) = 0x0 ;
	(*(volatile unsigned long int *)(0x210001c0)) = 0x600006 ;
	(*(volatile unsigned long int *)(0x210001c4)) = 0x80000 ;
	(*(volatile unsigned long int *)(0x21000340)) = 0x64000140 ;
	(*(volatile unsigned long int *)(0x21000344)) = 0x28010 ;
	(*(volatile unsigned long int *)(0x21000348)) = 0x11000 ;
	(*(volatile unsigned long int *)(0x2100034c)) = 0x40020080 ;
	(*(volatile unsigned long int *)(0x21000354)) = 0x180800 ;
	(*(volatile unsigned long int *)(0x2100035c)) = 0x4c183422 ;
	(*(volatile unsigned long int *)(0x21000360)) = 0xc180c08 ;
	(*(volatile unsigned long int *)(0x21000364)) = 0x181808 ;
	(*(volatile unsigned long int *)(0x21000368)) = 0x4404 ;
	(*(volatile unsigned long int *)(0x21000388)) = 0xc00100 ;
	(*(volatile unsigned long int *)(0x21000398)) = 0x40009110 ;
	(*(volatile unsigned long int *)(0x210003a0)) = 0x1008280a ;
	(*(volatile unsigned long int *)(0x210003b8)) = 0x0 ;
	(*(volatile unsigned long int *)(0x210003c4)) = 0x0 ;
	(*(volatile unsigned long int *)(0x210003c8)) = 0x1011404 ;
	(*(volatile unsigned long int *)(0x210003d0)) = 0x70008 ;
	(*(volatile unsigned long int *)(0x210003d4)) = 0x0 ;
	(*(volatile unsigned long int *)(0x210003d8)) = 0x101;
	(*(volatile unsigned long int *)(0x210003dc)) = 0xa0 ;
	(*(volatile unsigned long int *)(0x210003e0)) = 0x5020 ;
	(*(volatile unsigned long int *)(0x210003e4)) = 0x181c ;
	(*(volatile unsigned long int *)(0x21000008)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000500)) = 0x0 ;
	(*(volatile unsigned long int *)(0x21000504)) = 0x4000 ;
	(*(volatile unsigned long int *)(0x2100050c)) = 0x60b00000 ;
	(*(volatile unsigned long int *)(0x21000510)) = 0x400 ;
	(*(volatile unsigned long int *)(0x2100057c)) = 0x34102010 ;
	(*(volatile unsigned long int *)(0x21000580)) = 0x60806 ;
	(*(volatile unsigned long int *)(0x21000584)) = 0x501f40 ;
	(*(volatile unsigned long int *)(0x21000008)) = 0x0 ;
	(*(volatile unsigned long int *)(0x2100030c)) = 0x20b0b ;
	(*(volatile unsigned long int *)(0x21000310)) = 0x1313 ;
	(*(volatile unsigned long int *)(0x21000314)) = 0xffff0003 ;
	//(*(volatile unsigned long int *)(0x21000324)) = 0x45914259 ;
	(*(volatile unsigned long int *)(0x21000040)) = 0x43 ;
	(*(volatile unsigned long int *)(0x21000050)) = 0x4017 ;
	(*(volatile unsigned long int *)(0x21000054)) = 0x5143 ;
	(*(volatile unsigned long int *)(0x2100025c)) = 0x1 ;
}

void gfh_mc_post_init()
{
	printf("gfh_mc_init is called from gfh_mc.c file\r\n");
	uint32_t val0;
	uint32_t cnt= 0;

	(*(volatile unsigned long int*)(0x21000304)) = 0x10000001;
	(*(volatile unsigned long int*)(0x21000008)) = 0x0;

	do{
		val0 = read_mc(0x2100032c);
		cnt = cnt+1;
	} while(val0 != 0x1) ; 

#if 0
	if (cnt > 100) {
		printf("DFI PHY INIT Timeout");
		set_gpio(18);
	}
#endif
	cnt = 0;
	(*(volatile unsigned long int*)(0x21000008)) = 0x0000000000000000;
	(*(volatile unsigned long int*)(0x21000268)) = 0x303;

	// Polling status register
	do{
		val0 =read_mc(0x21000280);
	} while(val0 != 0x33 ); 
	cnt = 0;

	// extended
	(*(volatile unsigned long int*)(0x21000008)) = 0x0000000000000000;
	(*(volatile unsigned long int*)(0x210001a4)) = 0x00200000;
#if 0
	do{
		val0 =read_mc(0x21000280);	
	} while(val0 != 0x31 ); 
#endif
	(*(volatile unsigned long int*)(0x210001a4)) = 0x10200000;
	(*(volatile unsigned long int*)(0x21000008)) = 0x0000000000000001;

	do{
		val0 =read_mc(0x21000280);	
	} while(val0 != 0x11 ); 	
	(*(volatile unsigned long int*)(0x21000588)) = 0x0000000000001008;
}
#endif
