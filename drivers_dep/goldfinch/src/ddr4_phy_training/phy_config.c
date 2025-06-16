#include "common.h"

void config_TxSlewRate(int pstate_num)
{
	if(pstate_num == 1)
	{
		offset1 = 0x1005f;
		offset2 = 0x1015f;
	} else if (pstate_num == 2) {
		offset1 = 0x11005f;
		offset2 = 0x11015f;
	} else if (pstate_num == 3) {
		offset1 = 0x21005f;
		offset2 = 0x21015f;
	}
	
	addr1 = offset1;
	addr2 = offset2;
	value = 0x2ff;
	offset = 0;

	for(int i = 0; i < 9; i++)
	{
		writel(addr1 + offset, value);
		writel(addr2 + offset, value);
		offset += 0x1000;
	}
}

void config_ATxSlewRate()
{
	// [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=0
	// [phyinit_C_initPhyConfig] Programming ATxSlewRate::ATxPreDrvMode to 0x3, ANIB=11
	addr = 0x55;
	offset = 0;
	for(int i = 0; i < 12; i++)
	{
		/* TODO - Done Separeted from 0x3ff to 0xff */
		if(((addr + offset) == 0x4055) || ((addr + offset) == 0x5055))
			writel(addr + offset,0xff);
		else 
			writel(addr + offset,0x3ff);
		offset +=0x1000;
	}
}

void config_EnableCsMulticast_to_ProcOdtTimeCtl()
{
	// [phyinit_C_initPhyConfig] Programming EnableCsMulticast to 0x0
	writel(0x20027,0x0);

	if(pstate_num > 0)
		writel(0x200c5, dram_freq == 0 ? 0x19 : dram_freq == 1 ? 0x19 : 0xa);
	// [phyinit_C_initPhyConfig] Pstate=0,  Memclk=1600MHz, Programming PllCtrl2 to 19 based on DfiClk frequency = 800.
	
	if(pstate_num > 1)
		writel(0x1200c5,0xa);
	// [phyinit_C_initPhyConfig] Pstate=1,  Memclk=1066MHz, Programming PllCtrl2 to a based on DfiClk frequency = 533.
	
	if(pstate_num > 2)
		writel(0x2200c5,0xb);
	// [phyinit_C_initPhyConfig] Pstate=2,  Memclk=667MHz, Programming PllCtrl2 to b based on DfiClk frequency = 333.
	
	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming ARdPtrInitVal to 0x2
	if(pstate_num > 0)
		writel(0x2002e,0x2);

	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming ARdPtrInitVal to 0x2
	if(pstate_num > 1)
		writel(0x12002e,0x2);

	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming ARdPtrInitVal to 0x1
	if(pstate_num > 2)
		writel(0x22002e,0x1);

	if (pstate_num > 0)
	{
		// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming DqsPreambleControl to 0x8
		writel(0x20024,0x8);
		// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming DbyteDllModeCntrl to 0x2
		writel(0x2003a,0x2);
		// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming DllLockParam to 0x212
		writel(0x2007d,0x212);
		// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming DllGainCtl to 0x61
		writel(0x2007c,0x61);
	}

	if (pstate_num > 1)
	{
		// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming DqsPreambleControl to 0x8
		writel(0x120024,0x8);
		// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming DbyteDllModeCntrl to 0x2
		writel(0x2003a,0x2); /* TODO - Done */
		// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming DllLockParam to 0x212
		writel(0x12007d,0x212);
		// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming DllGainCtl to 0x61
		writel(0x12007c,0x61);
	}

	if (pstate_num > 2)
	{
		// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming DqsPreambleControl to 0x8
		writel(0x220024,0x8);
		// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming DbyteDllModeCntrl to 0x2
		writel(0x2003a,0x2); /* TODO - Done */
		// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming DllLockParam to 0x212
		writel(0x22007d,0x212);
		// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming DllGainCtl to 0x61
		writel(0x22007c,0x61);
	}

	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming ProcOdtTimeCtl to 0x7
	writel(0x20056, dram_freq == 0 ? 0x7 : dram_freq == 1 ? 0x7 : 0x6);
	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming ProcOdtTimeCtl to 0x6
	if(pstate_num > 1)
		writel(0x120056,0x6);
	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming ProcOdtTimeCtl to 0xa
	if(pstate_num > 2)
		writel(0x220056,0xa);
}

void config_TxOdtDrvStren_to_TxImpedanceCtrl1()
{
	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming TxOdtDrvStren::ODTStrenN to 0x0
	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming TxOdtDrvStren::ODTStrenN to 0x0
	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming TxOdtDrvStren::ODTStrenN to 0x0
	g_offset = 0;
	for(int i = 0; i < pstate_num; i++)
	{
		addr1 = 0x1004d + g_offset;
		addr2 = 0x1014d + g_offset;
		offset = 0;
		value = 0x18;

		for(int j = 0; j < 9; j++)
		{
			writel(addr1 + offset, value);
			writel(addr2 + offset, value);
			offset += 0x1000;
		}
		g_offset += 0x100000;
	}

	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming TxImpedanceCtrl1::DrvStrenFSDqN to 0x18
	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming TxImpedanceCtrl1::DrvStrenFSDqN to 0x18
	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming TxImpedanceCtrl1::DrvStrenFSDqN to 0x18
	g_offset = 0;
	for(int i = 0; i < pstate_num; i++)
	{
		addr1 = 0x10049 + g_offset;
		addr2 = 0x10149 + g_offset;
		offset = 0;
		value = 0x618;

		for(int j = 0; j < 9; j++)
		{
			writel(addr1 + offset, value);
			writel(addr2 + offset, value);
			offset += 0x1000;
		}
		g_offset += 0x100000;
	}
}

void config_ADrvStrenP_to_DMIPinPresent()
{
	int i;

	addr = 0x43;
	offset = 0;
	value = 0x3ff;

	// [phyinit_C_initPhyConfig] Programming ATxImpedance::ADrvStrenN to 0x1f
	for(int i = 0; i < 12; i++)
	{
		writel(addr + offset, value);
		offset += 0x1000;
	}

	// [phyinit_C_initPhyConfig] Programming DfiMode to 0x1
	writel(0x20018,0x1);

	// [phyinit_C_initPhyConfig] Programming DfiCAMode to 0x2
	writel(0x20075,0x2);

	// [phyinit_C_initPhyConfig] Programming CalDrvStr0::CalDrvStrPu50 to 0x0
	writel(0x20050,0x0);

	/* TODO - Done based on pstate num below registers will be loaded */
	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming CalUclkInfo::CalUClkTicksPer1uS to 0x320
	if(pstate_num > 0)
		writel(0x20008, dram_freq == 0 ? 0x320 : dram_freq == 1 ? 0x29b : 0x258);

	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming CalUclkInfo::CalUClkTicksPer1uS to 0x215
	if(pstate_num > 1)
		writel(0x120008,0x215);

	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming CalUclkInfo::CalUClkTicksPer1uS to 0x14e
	if(pstate_num > 2)
		writel(0x220008,0x14e);

	// [phyinit_C_initPhyConfig] Programming CalRate::CalOnce to 0x0
	writel(0x20088,0x3);


	// [phyinit_C_initPhyConfig] Pstate=0, Programming DqDqsRcvCntrl to 0x5b1
	g_offset = 0;
	for(int i = 0; i < pstate_num; i++)
	{
		addr1 = 0x10043 + g_offset;
		addr2 = 0x10143 + g_offset;
		offset = 0;
		value = 0x5b1;

		// [phyinit_C_initPhyConfig] Pstate=0, Programming VrefInGlobal to 0x1f8
		writel(0x200b2 + g_offset,0x1f8);

		for(int j = 0; j < 9; j++)
		{
			writel(addr1 + offset, value);
			writel(addr2 + offset, value);
			offset += 0x1000;
		}
		g_offset += 0x100000;
	}

	// [phyinit_C_initPhyConfig] Programming MemAlertControl2::MALERTSyncBypass to 0x0
	writel(0x2005b,0x7529);
	writel(0x2005c,0x0);

	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming DfiFreqRatio_p0 to 0x1
	if(pstate_num > 0)
		writel(0x200fa, dfi_freq_ratio); //16'(dfi_freq_ratio));

	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming DfiFreqRatio_p1 to 0x1
	if(pstate_num > 1)
		writel(0x1200fa, dfi_freq_ratio); //16'(dfi_freq_ratio));

	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming DfiFreqRatio_p2 to 0x1
	if(pstate_num > 2)
		writel(0x2200fa, dfi_freq_ratio); //16'(dfi_freq_ratio));

	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming TristateModeCA::DDR2TMode_p0 to 0x0
	if(pstate_num > 0)
		writel(0x20019,0x5);

	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming TristateModeCA::DDR2TMode_p1 to 0x0
	if(pstate_num > 1)
		writel(0x120019,0x5);

	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming TristateModeCA::DDR2TMode_p2 to 0x0
	if(pstate_num > 2)
		writel(0x220019,0x5);

	// [phyinit_C_initPhyConfig] Programming DfiFreqXlat*
	for(i = 0; i < 7; i++)
		writel(0x200f0 + i,0x5555);

	writel(0x200f0 + i,0xf000); /* TODO - DONE ADDRESS 0X200F7 value supposed to be 0x5555 but in .sv value is 0xf000 */
	offset = 0;
	for(int i = 0; i < 9; i++)
	{
		// [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.0
		// [phyinit_C_initPhyConfig] Disabling Lane 8 Receiver to save power.8
		writel(0x1004a + offset,0x500);
		offset += 0x1000;
	}

	// [phyinit_C_initPhyConfig] Programming MasterX4Config::X4TG to 0x0
	writel(0x20025, x8_device ? 0x0 : 0xf);
	
	// [phyinit_C_initPhyConfig] Pstate=0, Memclk=1600MHz, Programming DMIPinPresent::RdDbiEnabled to 0x0
	writel(0x2002d,0x0);
	
	// [phyinit_C_initPhyConfig] Pstate=1, Memclk=1066MHz, Programming DMIPinPresent::RdDbiEnabled to 0x0
	if(pstate_num > 1)
		writel(0x12002d,0x0);

	// [phyinit_C_initPhyConfig] Pstate=2, Memclk=667MHz, Programming DMIPinPresent::RdDbiEnabled to 0x0
	if(pstate_num > 2)
		writel(0x22002d,0x0);
	writel(0x2002c,0x0);

	// [phyinit_C_initPhyConfig] End of dwc_ddrphy_phyinit_C_initPhyConfig()
}

//##############################################################
//
// Step (C) Initialize PHY Configuration 
//
// Load the required PHY configuration registers for the appropriate mode and memory configuration
//
//##############################################################
// [phyinit_C_initPhyConfig] Start of dwc_ddrphy_phyinit_C_initPhyConfig()
void phy_config_init()
{
	int i = 0;

	for(i = 0; i < pstate_num; i++)
		config_TxSlewRate(i+1);

	config_ATxSlewRate();
	config_EnableCsMulticast_to_ProcOdtTimeCtl();
	config_TxOdtDrvStren_to_TxImpedanceCtrl1();
	config_ADrvStrenP_to_DMIPinPresent();
}

