#include "common.h"

void wait_for_training_FW_done()
{
	volatile unsigned int val;

        do {
                val = readl(0xd0004);
        } while ((val & 0x3) != 2);

        do {
                val = readl(0xd0032);
        } while ((val != 7));


	// Write the DctWriteProt to 0 to acknowledge the receipt of the message
        writel(0xd0031, 0x0);

        do {
                val = readl(0xd0004);
        } while ((val & 0x3) != 3);

	// write the DctWriteProt to 1 to complete the protocol
	writel(0xd0031, 0x1);
}

void execute_training_firmware()
{
	//##############################################################
	//
	// (G) Execute the Training Firmware 
	// 
	// See PhyInit App Note for detailed description and function usage
	//
	//##############################################################
	// 
	// 
	// 1.  Reset the firmware microcontroller by writing the MicroReset CSR to set the StallToMicro and 
	//     ResetToMicro fields to 1 (all other fields should be zero). 
	//     Then rewrite the CSR so that only the StallToMicro remains set (all other fields should be zero). 
	writel(0xd0000,0x1);
	writel(0xd0099,0x9);
	writel(0xd0099,0x1);

	// 2. Begin execution of the training firmware by setting the MicroReset CSR to 4'b0000. 
	writel(0xd0099,0x0);

	// 3.   Wait for the training firmware to complete by following the procedure in "uCtrl Initialization and Mailbox Messaging" 
	// [dwc_ddrphy_phyinit_userCustom_G_waitFwDone] Wait for the training firmware to complete.  Implement timeout fucntion or follow the procedure in "3.4 Running the firmware" of the Training Firmware Application Note to poll the Mailbox message.
	//dwc_ddrphy_phyinit_userCustom_G_waitFwDone ();

	/* TODO - Done. Need to include wait */
	/* `include "sequences/phy/snps/userCustom_steps/userCustom_G_waitFwDone.sv" */
	wait_for_training_FW_done();

	// [dwc_ddrphy_phyinit_userCustom_G_waitFwDone] End of dwc_ddrphy_phyinit_userCustom_G_waitFwDone()
	// 4.   Halt the microcontroller." 
	writel(0xd0099,0x1);
	// [dwc_ddrphy_phyinit_G_execFW] End of dwc_ddrphy_phyinit_G_execFW ()
	
	//##############################################################
	//
	// (H) Read the Message Block results
	// 
	// The procedure is as follows:
	// 
	//##############################################################
	// 1.        Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
	writel(0xd0000,0x0);
	// 2. Read the Firmware Message Block to obtain the results from the training.
	// This can be accomplished by issuing APB read commands to the DMEM addresses.
	// Example:
	// if (Train2D)
	// { 
	//   _read_2d_message_block_outputs_
	// }
	// else
	// {
	//   _read_1d_message_block_outputs_
	// }
	//dwc_ddrphy_phyinit_userCustom_H_readMsgBlock (0);

	// [dwc_ddrphy_phyinit_userCustom_H_readMsgBlock] End of dwc_ddrphy_phyinit_userCustom_H_readMsgBlock ()
	// 3.        Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. 
	writel(0xd0000,0x1);
	// 4.        If training is required at another frequency, repeat the operations starting at step (E). 
	// [dwc_ddrphy_phyinit_H_readMsgBlock] End of dwc_ddrphy_phyinit_H_readMsgBlock()
}

void userCustom_customPostTrain()
{
	writel(0xd0000,0x0);   // permit APB programming to PHY

	writel(0x1004a,0x400); // not to power down RDM(RDBI) receiver. DqDqsRcvCntrl1, for RDBI
	writel(0x1104a,0x400);
	writel(0x1204a,0x400);
	writel(0x1304a,0x400);
	writel(0x1404a,0x400);
	writel(0x1504a,0x400);
	writel(0x1604a,0x400);
	writel(0x1704a,0x400);
	writel(0x1804a,0x400);
}

void load_phy_init_engine()
{

	//##############################################################
	//
	// (I) Load PHY Init Engine Image 
	// 
	// Load the PHY Initialization Engine memory with the provided initialization sequence.
	// See PhyInit App Note for detailed description and function usage
	// 
	// 
	//##############################################################
	// Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0. 
	// This allows the memory controller unrestricted access to the configuration CSRs. 
	writel(0xd0000,0x0);
	// [phyinit_I_loadPIEImage] Programming PIE Production Code
	// [dwc_ddrphy_phyinit_LoadPieProdCode] Load PIE Production code: userInputBasic.DramDataWidth=8, userInputAdvanced.EnableHighClkSkewFix=0
	writel(0x90000,0x10);
	writel(0x90001,0x400);
	writel(0x90002,0x10e);
	writel(0x90003,0x0);
	writel(0x90004,0x0);
	writel(0x90005,0x8);
	writel(0x40000,0x10);
	writel(0x40020,0x0);
	writel(0x40040,0x0);
	writel(0x40060,0x0);
	writel(0x40001,0x70a);
	writel(0x40021,0x7005);
	writel(0x40041,0x0);
	writel(0x40061,0x2001);
	writel(0x40002,0x4010);
	writel(0x40022,0x0);
	writel(0x40042,0x0);
	writel(0x40062,0x0);
	writel(0x90029,0x10);
	writel(0x9002a,0x400);
	writel(0x9002b,0x16e);
	writel(0x9002c,0x8);
	writel(0x9002d,0x370);
	writel(0x9002e,0x169);
	writel(0x9002f,0x8);
	writel(0x90030,0x7aa);
	writel(0x90031,0x6a);
	writel(0x90032,0x10);
	writel(0x90033,0x7b2);
	writel(0x90034,0x6a);
	writel(0x90035,0x0);
	writel(0x90036,0x48a);
	writel(0x90037,0x6a);
	writel(0x90038,0x9);
	writel(0x90039,0x480);
	writel(0x9003a,0x16a);
	writel(0x9003b,0x4);
	writel(0x9003c,0x790);
	writel(0x9003d,0x16a);
	writel(0x9003e,0xc);
	writel(0x9003f,0x408);
	writel(0x90040,0x169);
	writel(0x90041,0xa);
	writel(0x90042,0x0);
	writel(0x90043,0x68);
	writel(0x90044,0x0);
	writel(0x90045,0x408);
	writel(0x90046,0x169);
	writel(0x90047,0x1);
	writel(0x90048,0x480);
	writel(0x90049,0x16a);
	writel(0x9004a,0xb);
	writel(0x9004b,0x480);
	writel(0x9004c,0x109);
	writel(0x9004d,0x8);
	writel(0x9004e,0x448);
	writel(0x9004f,0x139);
	writel(0x90050,0x78);
	writel(0x90051,0x8);
	writel(0x90052,0x139);
	writel(0x90053,0x2);
	writel(0x90054,0x10);
	writel(0x90055,0x139);
	writel(0x90056,0xb);
	writel(0x90057,0x7c0);
	writel(0x90058,0x139);
	writel(0x90059,0x44);
	writel(0x9005a,0x633);
	writel(0x9005b,0x159);
	writel(0x9005c,0x14f);
	writel(0x9005d,0x630);
	writel(0x9005e,0x159);
	writel(0x9005f,0x47);
	writel(0x90060,0x633);
	writel(0x90061,0x149);
	writel(0x90062,0x4f);
	writel(0x90063,0x633);
	writel(0x90064,0x179);
	writel(0x90065,0x8);
	writel(0x90066,0xe0);
	writel(0x90067,0x109);
	writel(0x90068,0x0);
	writel(0x90069,0x7c8);
	writel(0x9006a,0x109);
	writel(0x9006b,0x0);
	writel(0x9006c,0x1);
	writel(0x9006d,0x8);
	writel(0x9006e,0x0);
	writel(0x9006f,0x45a);
	writel(0x90070,0x9);
	writel(0x90071,0x0);
	writel(0x90072,0x448);
	writel(0x90073,0x109);
	writel(0x90074,0x40);
	writel(0x90075,0x633);
	writel(0x90076,0x179);
	writel(0x90077,0x1);
	writel(0x90078,0x618);
	writel(0x90079,0x109);
	writel(0x9007a,0x40c0);
	writel(0x9007b,0x633);
	writel(0x9007c,0x149);
	writel(0x9007d,0x8);
	writel(0x9007e,0x4);
	writel(0x9007f,0x48);
	writel(0x90080,0x4040);
	writel(0x90081,0x633);
	writel(0x90082,0x149);
	writel(0x90083,0x0);
	writel(0x90084,0x4);
	writel(0x90085,0x48);
	writel(0x90086,0x40);
	writel(0x90087,0x633);
	writel(0x90088,0x149);
	writel(0x90089,0x10);
	writel(0x9008a,0x4);
	writel(0x9008b,0x18);
	writel(0x9008c,0x0);
	writel(0x9008d,0x4);
	writel(0x9008e,0x78);
	writel(0x9008f,0x549);
	writel(0x90090,0x633);
	writel(0x90091,0x159);
	writel(0x90092,0xd49);
	writel(0x90093,0x633);
	writel(0x90094,0x159);
	writel(0x90095,0x94a);
	writel(0x90096,0x633);
	writel(0x90097,0x159);
	writel(0x90098,0x441);
	writel(0x90099,0x633);
	writel(0x9009a,0x149);
	writel(0x9009b,0x42);
	writel(0x9009c,0x633);
	writel(0x9009d,0x149);
	writel(0x9009e,0x1);
	writel(0x9009f,0x633);
	writel(0x900a0,0x149);
	writel(0x900a1,0x0);
	writel(0x900a2,0xe0);
	writel(0x900a3,0x109);
	writel(0x900a4,0xa);
	writel(0x900a5,0x10);
	writel(0x900a6,0x109);
	writel(0x900a7,0x9);
	writel(0x900a8,0x3c0);
	writel(0x900a9,0x149);
	writel(0x900aa,0x9);
	writel(0x900ab,0x3c0);
	writel(0x900ac,0x159);
	writel(0x900ad,0x18);
	writel(0x900ae,0x10);
	writel(0x900af,0x109);
	writel(0x900b0,0x0);
	writel(0x900b1,0x3c0);
	writel(0x900b2,0x109);
	writel(0x900b3,0x18);
	writel(0x900b4,0x4);
	writel(0x900b5,0x48);
	writel(0x900b6,0x18);
	writel(0x900b7,0x4);
	writel(0x900b8,0x58);
	writel(0x900b9,0xb);
	writel(0x900ba,0x10);
	writel(0x900bb,0x109);
	writel(0x900bc,0x1);
	writel(0x900bd,0x10);
	writel(0x900be,0x109);
	writel(0x900bf,0x5);
	writel(0x900c0,0x7c0);
	writel(0x900c1,0x109);
	writel(0x900c2,0x3);
	writel(0x900c3,0x370);
	writel(0x900c4,0x169);
	writel(0x900c5,0x3);
	writel(0x900c6,0x8);
	writel(0x900c7,0x139);
	writel(0x900c8,0x8);
	writel(0x900c9,0x478);
	writel(0x900ca,0x109);
	writel(0x900cb,0x0);
	writel(0x900cc,0x8140);
	writel(0x900cd,0x10c);
	writel(0x900ce,0x10);
	writel(0x900cf,0x8138);
	writel(0x900d0,0x104);
	writel(0x900d1,0x7a);
	writel(0x900d2,0x8);
	writel(0x900d3,0x109);
	writel(0x900d4,0x8);
	writel(0x900d5,0x448);
	writel(0x900d6,0x109);
	writel(0x900d7,0xf);
	writel(0x900d8,0x7c0);
	writel(0x900d9,0x109);
	writel(0x900da,0x47);
	writel(0x900db,0x630);
	writel(0x900dc,0x109);
	writel(0x900dd,0x8);
	writel(0x900de,0x618);
	writel(0x900df,0x109);
	writel(0x900e0,0x8);
	writel(0x900e1,0xe0);
	writel(0x900e2,0x109);
	writel(0x900e3,0x0);
	writel(0x900e4,0x8);
	writel(0x900e5,0x109);
	writel(0x900e6,0x0);
	writel(0x900e7,0x7c8);
	writel(0x900e8,0x109);
	writel(0x900e9,0x8);
	writel(0x900ea,0x8140);
	writel(0x900eb,0x10c);
	writel(0x900ec,0x0);
	writel(0x900ed,0x478);
	writel(0x900ee,0x109);
	writel(0x900ef,0x0);
	writel(0x900f0,0x1);
	writel(0x900f1,0x8);
	writel(0x900f2,0x8);
	writel(0x900f3,0x4);
	writel(0x900f4,0x0);
	writel(0x90006,0x8);
	writel(0x90007,0x7c8);
	writel(0x90008,0x109);
	writel(0x90009,0x0);
	writel(0x9000a,0x400);
	writel(0x9000b,0x106);
	writel(0xd00e7,0x400);
	writel(0x90017,0x0);
	writel(0x90026,0x38);

	// [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1600MHz, Programming Seq0BDLY0 to 0x64
	writel(0x2000b, dram_freq == 0 ? 0x64  : dram_freq == 1 ? 0x53  : 0x4b);
	// [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1600MHz, Programming Seq0BDLY1 to 0xc8
	writel(0x2000c, dram_freq == 0 ? 0xc8  : dram_freq == 1 ? 0xa6  : 0x96);
	// [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1600MHz, Programming Seq0BDLY2 to 0x7d0
	writel(0x2000d, dram_freq == 0 ? 0x7d0 : dram_freq == 1 ? 0x682 : 0x5dc);
	// [phyinit_I_loadPIEImage] Pstate=0,  Memclk=1600MHz, Programming Seq0BDLY3 to 0x2c
	writel(0x2000e,0x2c);

	if (pstate_num > 1)
	{
		// [phyinit_I_loadPIEImage] Pstate=1,  Memclk=1066MHz, Programming Seq0BDLY0 to 0x42
		writel(0x12000b,0x42);
		// [phyinit_I_loadPIEImage] Pstate=1,  Memclk=1066MHz, Programming Seq0BDLY1 to 0x85
		writel(0x12000c,0x85);
		// [phyinit_I_loadPIEImage] Pstate=1,  Memclk=1066MHz, Programming Seq0BDLY2 to 0x534
		writel(0x12000d,0x534);
		// [phyinit_I_loadPIEImage] Pstate=1,  Memclk=1066MHz, Programming Seq0BDLY3 to 0x2c
		writel(0x12000e,0x2c);
	}

	if (pstate_num > 2)
	{
		// [phyinit_I_loadPIEImage] Pstate=2,  Memclk=667MHz, Programming Seq0BDLY0 to 0x29
		writel(0x22000b,0x29);
		// [phyinit_I_loadPIEImage] Pstate=2,  Memclk=667MHz, Programming Seq0BDLY1 to 0x53
		writel(0x22000c,0x53);
		// [phyinit_I_loadPIEImage] Pstate=2,  Memclk=667MHz, Programming Seq0BDLY2 to 0x341
		writel(0x22000d,0x341);
		// [phyinit_I_loadPIEImage] Pstate=2,  Memclk=667MHz, Programming Seq0BDLY3 to 0x2c
		writel(0x22000e,0x2c);
	}

	writel(0x9000c,0x0);
	writel(0x9000d,0x173);
	writel(0x9000e,0x60);
	writel(0x9000f,0x6110);
	writel(0x90010,0x2152);
	writel(0x90011,0xdfbd);
	writel(0x90012,0xffff);
	writel(0x90013,0x6152);

	// [phyinit_I_loadPIEImage] Pstate=0, Programming F0RC0A=a6 
	// [phyinit_I_loadPIEImage] Pstate=0, Programming F0RC3x=361 
	// [phyinit_I_loadPIEImage] Pstate=0, Programming F0RC5x=500 
	// [phyinit_I_loadPIEImage] Pstate=0, Programming AcsmPlayback0x0 to 0xa6
	writel(0x40080, dram_freq == 0 ? 0xa6  : dram_freq == 1 ? 0xa4  : 0xa3);
	// [phyinit_I_loadPIEImage] Pstate=0, Programming AcsmPlayback1x0 to 0x0
	writel(0x40081,0x0);
	// [phyinit_I_loadPIEImage] Pstate=0, Programming AcsmPlayback0x1 to 0x361
	writel(0x40082, dram_freq == 0 ? 0x361 : dram_freq == 1 ? 0x347 : 0x339);
	// [phyinit_I_loadPIEImage] Pstate=0, Programming AcsmPlayback1x1 to 0x0
	writel(0x40083,0x0);
	// [phyinit_I_loadPIEImage] Pstate=0, Programming AcsmPlayback0x2 to 0x100
	writel(0x40084,0x100);
	// [phyinit_I_loadPIEImage] Pstate=0, Programming AcsmPlayback1x2 to 0x1
	writel(0x40085,0x1);

	if (pstate_num > 1)
	{
		// [phyinit_I_loadPIEImage] Pstate=1, Programming F0RC0A=a2 
		// [phyinit_I_loadPIEImage] Pstate=1, Programming F0RC3x=32c 
		// [phyinit_I_loadPIEImage] Pstate=1, Programming F0RC5x=500 
		// [phyinit_I_loadPIEImage] Pstate=1, Programming AcsmPlayback0x0 to 0xa2
		writel(0x140080,0xa2);
		// [phyinit_I_loadPIEImage] Pstate=1, Programming AcsmPlayback1x0 to 0x0
		writel(0x140081,0x0);
		// [phyinit_I_loadPIEImage] Pstate=1, Programming AcsmPlayback0x1 to 0x32c
		writel(0x140082,0x32c);
		// [phyinit_I_loadPIEImage] Pstate=1, Programming AcsmPlayback1x1 to 0x0
		writel(0x140083,0x0);
		// [phyinit_I_loadPIEImage] Pstate=1, Programming AcsmPlayback0x2 to 0x100
		writel(0x140084,0x100);
		// [phyinit_I_loadPIEImage] Pstate=1, Programming AcsmPlayback1x2 to 0x1
		writel(0x140085,0x1);
	}

	if (pstate_num > 2)
	{
		// [phyinit_I_loadPIEImage] Pstate=2, Programming F0RC0A=a0 
		// [phyinit_I_loadPIEImage] Pstate=2, Programming F0RC3x=304 
		// [phyinit_I_loadPIEImage] Pstate=2, Programming F0RC5x=500 
		// [phyinit_I_loadPIEImage] Pstate=2, Programming AcsmPlayback0x0 to 0xa0
		writel(0x240080,0xa0);
		// [phyinit_I_loadPIEImage] Pstate=2, Programming AcsmPlayback1x0 to 0x0
		writel(0x240081,0x0);
		// [phyinit_I_loadPIEImage] Pstate=2, Programming AcsmPlayback0x1 to 0x304
		writel(0x240082,0x304);
		// [phyinit_I_loadPIEImage] Pstate=2, Programming AcsmPlayback1x1 to 0x0
		writel(0x240083,0x0);
		// [phyinit_I_loadPIEImage] Pstate=2, Programming AcsmPlayback0x2 to 0x100
		writel(0x240084,0x100);
		// [phyinit_I_loadPIEImage] Pstate=2, Programming AcsmPlayback1x2 to 0x1
		writel(0x240085,0x1);
	}

	// [phyinit_I_loadPIEImage] Programing Training Hardware Registers for mission mode retraining
	writel(0x400fd,0xf);
	writel(0x400f0,0x4040);
	// [phyinit_I_loadPIEImage] Turn on calibration and hold idle until dfi_init_start is asserted sequence is triggered.
	writel(0x20089,0x1);
	// [phyinit_I_loadPIEImage] Programming CalRate::CalInterval to 0x3
	// [phyinit_I_loadPIEImage] Programming CalRate::CalOnce to 0x0
	// [phyinit_I_loadPIEImage] Programming CalRate::CalRun to 0x1
	writel(0x20088,0x13);
	// [phyinit_I_loadPIEImage] Disabling Ucclk (PMU) and Hclk (training hardware)
	writel(0xc0080,0x0);
	// [phyinit_I_loadPIEImage] Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1. 
	writel(0xd0000,0x1);
	// [phyinit_I_loadPIEImage] End of dwc_ddrphy_phyinit_I_loadPIEImage()

#if 0
	//##############################################################
	//
	// dwc_ddrphy_phyinit_userCustom_customPostTrain is a user-editable function.
	//
	// See PhyInit App Note for detailed description and function usage
	// 
	//##############################################################
	// 
	//dwc_ddrphy_phyinit_userCustom_customPostTrain ();

	`include "sequences/phy/snps/userCustom_steps/userCustom_postTrain.sv" 

		// [dwc_ddrphy_phyinit_userCustom_customPostTrain] End of dwc_ddrphy_phyinit_userCustom_customPostTrain()
		// [dwc_ddrphy_phyinit_userCustom_J_enterMissionMode] Start of dwc_ddrphy_phyinit_userCustom_J_enterMissionMode()
		// 
		// 
		//##############################################################
		//
		// (J) Initialize the PHY to Mission Mode through DFI Initialization 
		//
		// Initialize the PHY to mission mode as follows: 
		//
		// 1. Set the PHY input clocks to the desired frequency. 
		// 2. Initialize the PHY to mission mode by performing DFI Initialization. 
		//    Please see the DFI specification for more information. See the DFI frequency bus encoding in section <XXX>.
		// Note: The PHY training firmware initializes the DRAM state. if skip 
		// training is used, the DRAM state is not initialized. 
		//
		//##############################################################
		// 
		//dwc_ddrphy_phyinit_userCustom_J_enterMissionMode ();

		// 
		// [dwc_ddrphy_phyinit_userCustom_J_enterMissionMode] End of dwc_ddrphy_phyinit_userCustom_J_enterMissionMode()
		// [dwc_ddrphy_phyinit_sequence] End of dwc_ddrphy_phyinit_sequence()
		// [dwc_ddrphy_phyinit_main] End of dwc_ddrphy_phyinit_main()
#endif
	userCustom_customPostTrain();
}

void run_training_firmware()
{
	execute_training_firmware();

	if (pstate_num > 1)
	{
		//##############################################################
		//
		// Step (E) Set the PHY input clocks to the desired frequency for pstate 1 
		// 
		// See PhyInit App Note for detailed description and function usage
		// 
		//##############################################################
		// 
		//dwc_ddrphy_phyinit_userCustom_E_setDfiClk (1);

		/* TODO - need to below things */
		/* rdata[0] = 1;
		   `include "sequences/phy/snps/userCustom_steps/userCustom_E_setDfiClk.sv" */

		// [phyinit_F_loadDMEM, 1D] Start of dwc_ddrphy_phyinit_F_loadDMEM (pstate=1, Train2D=0)
		//##############################################################
		//
		// (F) Load the 1D DMEM image and write the 1D Message Block parameters for the training firmware 
		// 
		// See PhyInit App Note for detailed description and function usage
		// 
		//##############################################################
		dmem_init(2);
		execute_training_firmware();
	}
	
	if (pstate_num > 2)
	{
		//##############################################################
		//
		// Step (E) Set the PHY input clocks to the desired frequency for pstate 2 
		// 
		// See PhyInit App Note for detailed description and function usage
		// 
		//##############################################################
		// 
		//dwc_ddrphy_phyinit_userCustom_E_setDfiClk (2);

		/* TODO - need to add below things */
		/* rdata[0] = 2;
		   `include "sequences/phy/snps/userCustom_steps/userCustom_E_setDfiClk.sv" */

		// [phyinit_F_loadDMEM, 1D] Start of dwc_ddrphy_phyinit_F_loadDMEM (pstate=2, Train2D=0)
		//##############################################################
		//
		// (F) Load the 1D DMEM image and write the 1D Message Block parameters for the training firmware 
		// 
		// See PhyInit App Note for detailed description and function usage
		// 
		//##############################################################
		dmem_init(3);
		execute_training_firmware();
	}
}
