#include "common.h"
#include "dmem.h"

void dmem_init(int pstate_num)
{
	unsigned int dmem_addr = DMEM_BASE_ADDR;

	/* Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
	   This allows the memory controller unrestricted access to the configuration CSRs. */
	writel(0xd0000,0x0);

	/* TODO - Completed */
	/* Need to update variable dmem data which is dependent on dram_freq, cs_dimm0. etc */
	for (int i = 0; i < (sizeof(dmem_data) / sizeof(dmem_data[0])); i++)
	{
		if(pstate_num == 1)
		{
			if((dmem_addr + i) == 0x54002)
				writel(0x54002, 0);
			else if((dmem_addr + i) == 0x54003)
				writel(0x54003, dram_freq == 0 ? 0xc80 : dram_freq == 1 ? 0xa6a : 0x960);
			else if((dmem_addr + i) == 0x54004)
				writel(0x54004, dfi_freq_ratio == 0 ? 0x1 : 0x2);
			else if((dmem_addr + i) == 0x54008)
			{
				int temp;
				temp = (cs_dimm0 == 4 ? 0x0f : cs_dimm0 == 2 ? 0x03 : cs_dimm0 == 1 ? 0x01 : 0x0);
				temp = temp << 8;
				temp = temp | (rank_num == 4 ? 0x0f : rank_num == 2 ? 0x03 : rank_num == 1 ? 0x01 : 0x00);
				writel(0x54008, temp);

				/* writel(0x54008, {8'(cs_dimm0 == 4 ? 8'h0f : cs_dimm0 == 2 ? 8'h03 : cs_dimm0 == 1 ? 8'h01 : 8'h0),
				   8'(rank_num == 4 ? 8'h0f : rank_num == 2 ? 8'h03 : rank_num == 1 ? 8'h01 : 8'h00)});*/
			}
			else if((dmem_addr + i) == 0x54009)
			{
				int temp;
				temp = (ad_mirror & (rank_num == 4) ? 0xa : ad_mirror & (rank_num == 2) ? 0x2 : 0x0);
				temp = temp << 8;
				temp = temp | (cs_dimm1 == 4 ? 0x0f : cs_dimm1 == 2 ? 0x03 : cs_dimm1 == 1 ? 0x01 : 0x0);
				writel(0x54009, temp);

				/* writel(0x54009, {8'(ad_mirror & (rank_num == 4) ? 8'ha : ad_mirror & (rank_num == 2) ? 8'h2 : 8'h0),
				 *                  8'(cs_dimm1 == 4 ? 8'h0f : cs_dimm1 == 2 ? 8'h03 : cs_dimm1 == 1 ? 8'h01 : 8'h0)}); */
			}
			else if((dmem_addr + i) == 0x5400b)
				writel(0x5400b, skip_training == 0 ? 0x31f : 0x1);
			else if((dmem_addr + i) == 0x5402f)
				writel(0x5402f, dram_freq == 0 ? 0xd54  : dram_freq == 1 ? 0xb44 : 0xd40);
			else if((dmem_addr + i) == 0x54031)
				writel(0x54031, dram_freq == 0 ? 0x228  : dram_freq == 1 ? 0x220 : 0x218);
			else if((dmem_addr + i) == 0x54035)
				writel(0x54035, dram_freq == 0 ? 0x104f : dram_freq == 1 ? 0xc4f : 0x84f);
			else if((dmem_addr + i) == 0x54070)
				writel(0x54070, dram_freq == 0 ? 0x6  : dram_freq == 1 ? 0x4  : 0x3);
			else if((dmem_addr + i) == 0x54071)
				writel(0x54071, 0x0 | (ad_mirror << 11) | (1 << 10) | ((cs_mode & 0x3) << 8) | 0);
				/* writel(0x54071, {4'h0, 1'(ad_mirror), 1'h1, 2'(cs_mode), 8'h0}); */
			else if((dmem_addr + i) == 0x54074)
				writel(0x54074, dram_freq == 0 ? 0x61 : dram_freq == 1 ? 0x47 : 0x39);
			else if((dmem_addr + i) == 0x5408b)
				writel(0x5408b, dram_freq == 0 ? 0x6  : dram_freq == 1 ? 0x4  : 0x3);
			else if((dmem_addr + i) == 0x5408c)
				writel(0x5408c, 0x0 | (ad_mirror << 11) | (1 << 10) | ((cs_mode & 0x3) << 8) | 0);
				/* writel(0x5408c, {4'h0, 1'(ad_mirror), 1'h1, 2'(cs_mode), 8'h0}); */
			else if((dmem_addr + i) == 0x5408f)
				writel(0x5408f, dram_freq == 0 ? 0x61 : dram_freq == 1 ? 0x47 : 0x39);
			else
				writel(dmem_addr + (i * 1), dmem_data[i]);
		}
		else if(pstate_num == 2)
		{
			if((dmem_addr + i) == 0x54002)
				writel(0x54002, 1);
			else if((dmem_addr + i) == 0x54003)
				writel(0x54003, 0x854);
			else if((dmem_addr + i) == 0x54004)
				writel(0x54004, dfi_freq_ratio == 0 ? 0x1 : 0x2);
			else if((dmem_addr + i) == 0x54008)
			{
				int temp;
				temp = (cs_dimm0 == 4 ? 0x0f : cs_dimm0 == 2 ? 0x03 : cs_dimm0 == 1 ? 0x01 : 0x0);
				temp = temp << 8;
				temp = temp | (rank_num == 4 ? 0x0f : rank_num == 2 ? 0x03 : rank_num == 1 ? 0x01 : 0x00);
				writel(0x54008, temp);

				/* writel(0x54008, {8'(cs_dimm0 == 4 ? 8'h0f : cs_dimm0 == 2 ? 8'h03 : cs_dimm0 == 1 ? 8'h01 : 8'h0),
				 *   	            8'(rank_num == 4 ? 8'h0f : rank_num == 2 ? 8'h03 : rank_num == 1 ? 8'h01 : 8'h00)}); */
			}
			else if((dmem_addr + i) == 0x54009)
			{
				int temp;
				temp = (ad_mirror & (rank_num == 4) ? 0xa : ad_mirror & (rank_num == 2) ? 0x2 : 0x0);
				temp = temp << 8;
				temp = temp | (cs_dimm1 == 4 ? 0x0f : cs_dimm1 == 2 ? 0x03 : cs_dimm1 == 1 ? 0x01 : 0x0);
				writel(0x54009, temp);

				/* writel(0x54009, {8'(ad_mirror & (rank_num == 4) ? 8'ha : ad_mirror & (rank_num == 2) ? 8'h2 : 8'h0),
				 *                  8'(cs_dimm1 == 4 ? 8'h0f : cs_dimm1 == 2 ? 8'h03 : cs_dimm1 == 1 ? 8'h01 : 8'h0)}); */
			}
			else if((dmem_addr + i) == 0x5400b)
				writel(0x5400b, skip_training == 0 ? 0x21f : 0x1);
			else if((dmem_addr + i) == 0x5402f)
				writel(0x5402f, 0x734);
			else if((dmem_addr + i) == 0x54031)
				writel(0x54031, 0x210);
			else if((dmem_addr + i) == 0x54035)
				writel(0x54035, 0x84f);
			else if((dmem_addr + i) == 0x54070)
				writel(0x54070, 0x2);
			else if((dmem_addr + i) == 0x54071)
				writel(0x54071, 0x0 | (ad_mirror << 12) | (1 << 11) | ((cs_mode & 0x3) << 8) | 0);
				/* writel(0x54071, {4'h0, 1'(ad_mirror), 1'h1, 2'(cs_mode), 8'h0}); */
			else if((dmem_addr + i) == 0x54074)
				writel(0x54074, 0x2c);
			else if((dmem_addr + i) == 0x5408b)
				writel(0x5408b, 0x2);
			else if((dmem_addr + i) == 0x5408c)
				writel(0x5408c, 0x0 | (ad_mirror << 12) | (1 << 11) | ((cs_mode & 0x3) << 8) | 0);
				/* writel(0x5408c, {4'h0, 1'(ad_mirror), 1'h1, 2'(cs_mode), 8'h0}); */
			else if((dmem_addr + i) == 0x5408f)
				writel(0x5408f, 0x2c);
			else
				writel(dmem_addr + (i * 1), dmem_data[i]);
		}
		else if(pstate_num == 3)
		{
			if((dmem_addr + i) == 0x54002)
				writel(0x54002, 2);
			else if((dmem_addr + i) == 0x54003)
				writel(0x54003, 0x536);
			else if((dmem_addr + i) == 0x54004)
				writel(0x54004, dfi_freq_ratio == 0 ? 0x1 : 0x2);
			else if((dmem_addr + i) == 0x54008)
			{
				int temp;
				temp = (cs_dimm0 == 4 ? 0x0f : cs_dimm0 == 2 ? 0x03 : cs_dimm0 == 1 ? 0x01 : 0x0);
				temp = temp << 8;
				temp = temp | (rank_num == 4 ? 0x0f : rank_num == 2 ? 0x03 : rank_num == 1 ? 0x01 : 0x00);
				writel(0x54008, temp);

				/* writel(0x54008, {8'(cs_dimm0 == 4 ? 8'h0f : cs_dimm0 == 2 ? 8'h03 : cs_dimm0 == 1 ? 8'h01 : 8'h0),
				   8'(rank_num == 4 ? 8'h0f : rank_num == 2 ? 8'h03 : rank_num == 1 ? 8'h01 : 8'h00)});*/
			}
			else if((dmem_addr + i) == 0x54009)
			{
				int temp;
				temp = (ad_mirror & (rank_num == 4) ? 0xa : ad_mirror & (rank_num == 2) ? 0x2 : 0x0);
				temp = temp << 8;
				temp = temp | (cs_dimm1 == 4 ? 0x0f : cs_dimm1 == 2 ? 0x03 : cs_dimm1 == 1 ? 0x01 : 0x0);
				writel(0x54009, temp);

				/* writel(0x54009, {8'(ad_mirror & (rank_num == 4) ? 8'ha : ad_mirror & (rank_num == 2) ? 8'h2 : 8'h0),
				 *                  8'(cs_dimm1 == 4 ? 8'h0f : cs_dimm1 == 2 ? 8'h03 : cs_dimm1 == 1 ? 8'h01 : 8'h0)}); */
			}
			else if((dmem_addr + i) == 0x5400b)
				writel(0x5400b, skip_training == 0 ? 0x21f : 0x1);
			else if((dmem_addr + i) == 0x5402f)
				writel(0x5402f, 0x104);
			else if((dmem_addr + i) == 0x54031)
				writel(0x54031, 0x200);
			else if((dmem_addr + i) == 0x54035)
				writel(0x54035, 0x4f);
			else if((dmem_addr + i) == 0x54070)
				writel(0x54070, 0x0);
			else if((dmem_addr + i) == 0x54071)
				writel(0x54071, 0x0 | (ad_mirror << 12) | (1 << 11) | ((cs_mode & 0x3) << 8) | 0);
				/* writel(0x54071, {4'h0, 1'(ad_mirror), 1'h1, 2'(cs_mode), 8'h0}); */
			else if((dmem_addr + i) == 0x54074)
				writel(0x54074, 0x4);
			else if((dmem_addr + i) == 0x5408b)
				writel(0x5408b, 0x0);
			else if((dmem_addr + i) == 0x5408c)
				writel(0x5408c, 0x0 | (ad_mirror << 12) | (1 << 11) | ((cs_mode & 0x3) << 8) | 0);
				/* writel(0x5408c, {4'h0, 1'(ad_mirror), 1'h1, 2'(cs_mode), 8'h0}); */
			else if((dmem_addr + i) == 0x5408f)
				writel(0x5408f, 0x4);
			else
				writel(dmem_addr + (i * 1), dmem_data[i]);
		}
	}


	/* Isolate the APB access from the internal CSRs by setting the MicroContMuxSel CSR to 1.
	   This allows the firmware unrestricted access to the configuration CSRs. */
	writel(0xd0000,0x1);
}
