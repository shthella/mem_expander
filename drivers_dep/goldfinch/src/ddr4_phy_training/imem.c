#include "common.h"

void imem_init()
{
#if 0	
	unsigned int imem_addr = DMEM_BASE_ADDR;

	/* Enable access to the internal CSRs by setting the MicroContMuxSel CSR to 0.
	   This allows the memory controller unrestricted access to the configuration CSRs. */

	for (int i = 0; i < (sizeof(imem_data) / sizeof(imem_data[0])); i++)
	{
		writel(imem_addr + (i * 1), imem_data[i]);
	}

#endif
}

