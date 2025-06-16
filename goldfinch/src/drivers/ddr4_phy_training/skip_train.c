#include "common.h"


// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming TxDqsDlyTg3 to 0x198
void config_TxDqsDlyTg3()
{
        unsigned int base_addrs[] = {0x100d0, 0x101d0, 0x110d0, 0x111d0, 0x120d0, 0x121d0,
                0x130d0, 0x131d0, 0x140d0, 0x141d0, 0x150d0, 0x151d0,
                0x160d0, 0x161d0, 0x170d0, 0x171d0, 0x180d0, 0x181d0};
        unsigned int offset_addrs[] = {0x0, 0x1, 0x2, 0x3};
        unsigned int values[3] = {0x246, 0x20f, 0x204}; // Corresponding values for dram_freq 0, 1, and 2
        unsigned int l_offset = 0, l_value[3] = {0, 0x1d9, 0x198};

        // Determine the value to write based on dram_freq
        unsigned int value = values[(dram_freq == 0) ? 0 : (dram_freq == 1) ? 1 : 2];
        l_value[0] = value;

        for(int i = 0; i < pstate_num; i++)
        {
                for (int j = 0; j < sizeof(base_addrs) / sizeof(base_addrs[0]); j++)
                {
                        for (int k = 0; k < sizeof(offset_addrs) / sizeof(offset_addrs[0]); k++)
                        {
                                writel(base_addrs[j] + offset_addrs[k] + l_offset, l_value[i]);
                        }
                }
                l_offset += 0x100000;
        }
}

// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=0, Memclk=1600MHz, Programming TxDqDlyTg3 to 0x16
// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=1, Memclk=1066MHz, Programming TxDqDlyTg3 to 0x4a
// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming TxDqDlyTg3 to 0x49
void config_TxDqDlyTg3()
{
        unsigned int base_addrs[] = { 
					0x100c0, 0x101c0, 0x102c0, 0x103c0, 0x104c0, 0x105c0, 0x106c0, 0x107c0, 0x108c0,
					0x110c0, 0x111c0, 0x112c0, 0x113c0, 0x114c0, 0x115c0, 0x116c0, 0x117c0, 0x118c0,
					0x120c0, 0x121c0, 0x122c0, 0x123c0, 0x124c0, 0x125c0, 0x126c0, 0x127c0, 0x128c0,
					0x130c0, 0x131c0, 0x132c0, 0x133c0, 0x134c0, 0x135c0, 0x136c0, 0x137c0, 0x138c0,
					0x140c0, 0x141c0, 0x142c0, 0x143c0, 0x144c0, 0x145c0, 0x146c0, 0x147c0, 0x148c0,
					0x150c0, 0x151c0, 0x152c0, 0x153c0, 0x154c0, 0x155c0, 0x156c0, 0x157c0, 0x158c0,
					0x160c0, 0x161c0, 0x162c0, 0x163c0, 0x164c0, 0x165c0, 0x166c0, 0x167c0, 0x168c0,
					0x170c0, 0x171c0, 0x172c0, 0x173c0, 0x174c0, 0x175c0, 0x176c0, 0x177c0, 0x178c0,
					0x180c0, 0x181c0, 0x182c0, 0x183c0, 0x184c0, 0x185c0, 0x186c0, 0x187c0, 0x188c0,
				    };
        unsigned int offset_addrs[] = {0x0, 0x1, 0x2, 0x3};
        unsigned int values[3] = {0x16, 0x1f, 0x14}; // Corresponding values for dram_freq 0, 1, and 2
        unsigned int l_offset = 0, l_value[3] = {0, 0x4a, 0x49};

        // Determine the value to write based on dram_freq
        unsigned int value = values[(dram_freq == 0) ? 0 : (dram_freq == 1) ? 1 : 2];
        l_value[0] = value;

        for(int i = 0; i < pstate_num; i++)
        {
                for (int j = 0; j < sizeof(base_addrs) / sizeof(base_addrs[0]); j++)
                {
                        for (int k = 0; k < sizeof(offset_addrs) / sizeof(offset_addrs[0]); k++)
                        {
                                writel(base_addrs[j] + offset_addrs[k] + l_offset, l_value[i]);
                        }
                }
                l_offset += 0x100000;
        }
}

// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=0, Memclk=1600MHz, Programming RxEnDlyTg3 to 0x245
// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=1, Memclk=1066MHz, Programming RxEnDlyTg3 to 0x1d8
// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming RxEnDlyTg3 to 0x197
void config_RxEnDlyTg3()
{
        unsigned int base_addrs[] = {0x10080, 0x10180, 0x11080, 0x11180, 0x12080, 0x12180,
                0x13080, 0x13180, 0x14080, 0x14180, 0x15080, 0x15180,
                0x16080, 0x16180, 0x17080, 0x17180, 0x18080, 0x18180};
        unsigned int offset_addrs[] = {0x0, 0x1, 0x2, 0x3};
        unsigned int values[3] = {0x245, 0x20e, 0x203}; // Corresponding values for dram_freq 0, 1, and 2
        unsigned int l_offset = 0, l_value[3] = {0, 0x1d8, 0x197};

        // Determine the value to write based on dram_freq
        unsigned int value = values[(dram_freq == 0) ? 0 : (dram_freq == 1) ? 1 : 2];
        l_value[0] = value;

        for(int i = 0; i < pstate_num; i++)
        {
                for (int j = 0; j < sizeof(base_addrs) / sizeof(base_addrs[0]); j++)
                {
                        for (int k = 0; k < sizeof(offset_addrs) / sizeof(offset_addrs[0]); k++)
                        {
                                writel(base_addrs[j] + offset_addrs[k] + l_offset, l_value[i]);
                        }
                }
                l_offset += 0x100000;
        }
}

//##############################################################
//
// dwc_ddrphy_phyihunit_userCustom_customPreTrain is a user-editable function.
//
// See PhyInit App Note for detailed description and function usage
//
//##############################################################
void skip_traininig_1_or_2()
{
	int i;

	// [phyinit_userCustom_customPreTrain] Start of dwc_ddrphy_phyinit_userCustom_customPreTrain()
	// [phyinit_userCustom_customPreTrain] End of dwc_ddrphy_phyinit_userCustom_customPreTrain()

	if (skip_training != 0)
	{
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

		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=0, Memclk=1600MHz, Programming HwtMRL to 0x6
		offset = 0;
		for(i = 0; i < 9; i++)
		{
			writel(0x10020 + offset, dram_freq == 0 ? 0x6 : dram_freq == 1 ? 0x6 : 0x5);
			offset += 0x1000;
		}

		/* TODO - Done */
		writel(0x20020, dram_freq == 0 ? 0x6 : dram_freq == 1 ? 0x6 : 0x5);

		if (pstate_num > 1)
		{
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=1, Memclk=1066MHz, Programming HwtMRL to 0x5
			offset = 0;
			for(i = 0; i < 9; i++)
			{
				writel(0x110020 + offset,0x5);
				offset += 0x1000;
			}
			writel(0x120020,0x5);
		}

		if (pstate_num > 2)
		{
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming HwtMRL to 0x5
			offset = 0;
			for(i = 0; i < 9; i++)
			{
				writel(0x210020 + offset,0x5);
				offset += 0x1000;
			}
			writel(0x220020,0x5);
		}

		/* configure for pstate 1 & 2 */
		config_TxDqsDlyTg3();
		config_TxDqDlyTg3();
		config_RxEnDlyTg3();

		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Programming HwtCAMode to 0x2
		writel(0x20077,0x2);
		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=0, Memclk=1600MHz, Programming DllGainCtl::DllGainIV=0x4, DllGainTV=0x5
		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=0, Memclk=1600MHz, Programming DllGainCtl to 0x54
		writel(0x2007c,0x54);
		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=0, Memclk=1600MHz, Programming DllLockParam::LcdlSeed0 to 63 
		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=0, Memclk=1600MHz, Programming DllLockParam to 0x3f2
		writel(0x2007d, dram_freq == 0 ? 0x3f2 : dram_freq == 1 ? 0x4c2 : 0x542);

		/* TODO: I have added pstate_num conditions, in original sv file these checks are not there, need to confirm with bill */
		if(pstate_num > 1)
		{
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=1, Memclk=1066MHz, Programming DllGainCtl::DllGainIV=0x3, DllGainTV=0x5
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=1, Memclk=1066MHz, Programming DllGainCtl to 0x53
			writel(0x12007c,0x53);
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=1, Memclk=1066MHz, Programming DllLockParam::LcdlSeed0 to 95 
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=1, Memclk=1066MHz, Programming DllLockParam to 0x5f2
			writel(0x12007d,0x5f2);
		}

		/* TODO: I have added pstate_num conditions, in original sv file these checks are not there, need to confirm with bill */
		if(pstate_num > 2)
		{
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming DllGainCtl::DllGainIV=0x2, DllGainTV=0x4
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming DllGainCtl to 0x42
			writel(0x22007c,0x42);
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming DllLockParam::LcdlSeed0 to 151 
			// [dwc_ddrphy_phyinit_progCsrSkipTrain] Pstate=2, Memclk=667MHz, Programming DllLockParam to 0x972
			writel(0x22007d,0x972);
		}

		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Programming AcsmCtrl23 to 0x10f
		writel(0x400c0,0x10f);

		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Programming PllCtrl3 to 0x61f0
		writel(0x200cb,0x61f0);
	} // if (skip_training != 0)

	if (skip_training == 1)
	{
		// [dwc_ddrphy_phyinit_progCsrSkipTrain] Special skipTraining configuration to Prevernt DRAM Commands on the first dfi status interface handshake.
		// [dwc_ddrphy_phyinit_progCsrSkipTrain] In order to see this behavior, the frist dfi_freq should be in the range of 0x0f < dfi_freq_sel[4:0] < 0x14.
		writel(0x90028,0x0);
	}
	// [dwc_ddrphy_phyinit_progCsrSkipTrain] End of dwc_ddrphy_phyinit_progCsrSkipTrain()
}
