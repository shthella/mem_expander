#include <stdio.h>
#include <stdint.h>
#include "common.h"

/* Below variables updated from Flash */
unsigned int pstate_num = 1;
unsigned int dram_freq = 0;
unsigned int dfi_freq_ratio = 1;
unsigned int x8_device = 1;
unsigned int skip_training = 0;
unsigned int cs_dimm0 = 1;
unsigned int cs_dimm1 = 0;
unsigned int rank_num = 1;
unsigned int ad_mirror = 0;
unsigned int cs_mode = 0;

/* General purpose variables */
unsigned int addr, value, offset, offset1, offset2;
unsigned int addr1, addr2, g_offset;

void ddr_phy_init()
{
	printf("ddr phy init is called\n");
#ifdef UART_ENABLED
	printf("PHY INIT\n");
	printf("SKIP TRAINING\n");
	printf("IMEM INIT\n");
	printf("DMEM INIT\n");
	printf("RUN FIRMWARE\n");
#endif

	/* Step (C) Initialize PHY Configuration */
	phy_config_init();
	
	//##############################################################
	//
	// Training firmware is *NOT* executed. This function replaces these steps
	// in the PHY Initialization sequence:
	//
	//  (E) Set the PHY input clocks to the desired frequency
	//  (F) Write the Message Block parameters for the training firmware
	//  (G) Execute the Training Firmware
	//  (H) Read the Message Block results
	//
	//##############################################################
	if(skip_training != 0)
		skip_traininig_1_or_2();

	if (skip_training == 1)
	{
		/* [dwc_ddrphy_phyinit_progCsrSkipTrain]
		 *  Special skipTraining configuration to Prevernt DRAM Commands 
		 *  on the first dfi status interface handshake. */
		/* [dwc_ddrphy_phyinit_progCsrSkipTrain]
		 * In order to see this behavior, the frist dfi_freq should be in
		 * the range of 0x0f < dfi_freq_sel[4:0] < 0x14. */
		writel(0x90028, 0x0);
	}

	if(skip_training != 1)
	{
		//##############################################################
		//
		// (D) Load the 1D IMEM image
		//
		// This function loads the training firmware IMEM image into the SRAM.
		// See PhyInit App Note for detailed description and function usage
		//
		//##############################################################
	//	imem_init();

		//##############################################################
		//
		// (F) Load the 1D DMEM image and write the 1D Message Block parameters for the training firmware 
		// 
		// See PhyInit App Note for detailed description and function usage
		// 
		//##############################################################
		dmem_init(1);

		//##############################################################
		//
		// (G) Execute the Training Firmware 
		// 
		// See PhyInit App Note for detailed description and function usage
		//
		//##############################################################
		run_training_firmware();
	}

	//##############################################################
	//
	// (I) Load PHY Init Engine Image
	// Load the PHY Initialization Engine memory with the provided initialization sequence.
	//
	//##############################################################
	load_phy_init_engine();
}
