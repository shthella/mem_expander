#include "common.h"

unsigned int spd_bytes[128];
unsigned int spd_index;

void spd_i2c_read(void)
{
	unsigned int addr, wrdata, rdata;
	unsigned int i2c_write_cmds = 0, loop = 0;
	unsigned int data_len = 0;

	//I2C fun_select
	addr = 0x20005110;
	wrdata = readl(addr);
	wrdata &= ~(0xF << 24); // Clear bits 27:24
	wrdata |= (0x3 << 24);  // Set bits 27:24 to 0x3
	wrdata &= ~(0xF << 8);  // Clear bits 11:8
	wrdata |= (0x3 << 8);   // Set bits 11:8 to 0x3
	writel(addr, wrdata);

	//I2C select - PMU ctrl register
	addr = 0x26000004;
	wrdata = readl(addr);
	wrdata |= (0x1 << 22);
	writel(addr, wrdata);

	addr = 0x20002010;
	writel(addr, 0x70707070);

	spd_index = 0;

	//First read and write cmds
	for(; i2c_write_cmds < 48; i2c_write_cmds++)
	{
		//I2C adress select and more
		addr = 0x20002000;
		wrdata = readl(addr); //reset - 0xa, 0x50db
		wrdata |= (0x1 << 0);
		wrdata |= (0x1 << 1);
		wrdata &= ~(0x3FF << 8);
		wrdata |= (0x55 << 8);
		wrdata &= ~(0xFF << 20);
		//wrdata |= (16 << 20); // Data Len
		//wrdata |= (255 << 20); // Data Len
		wrdata |= (7 << 20); // Data Len
		writel(addr, wrdata);

		// Poll for end of read trnasfer complete
		while((readl(0x20002004) & (1 << 0)) == 0)
		{
			// Busy wait until the bit is high
#if 0
			/* mean while check for fifo full condition and give i2c read cmd */
			rdata = readl(0x20002004);
			if(rdata & 0x4)
			{
				/* i2c read cmd */
				rdata = readl(0x2000208C);
			}
#endif
		}

		/* i2c read cmd */
		spd_bytes[spd_index] = readl(0x2000208C);
		spd_index++;

		/* i2c read cmd */
		spd_bytes[spd_index] = readl(0x2000208C);
		spd_index++;

		// Interrupt clear of i2c_end_int
		wrdata = readl(0x20002004);
		wrdata |= (1 << 16);
		writel(0x20002004, wrdata);

		// reset the I2C
		wrdata = readl(0x20002000);
		wrdata &= ~( 1 << 0);
		writel(0x20002000, wrdata);

		/* Adding delay after reset */
		while(loop <= 10000)
		{
			loop++;
		}

		loop = 0;
	}

	return;
}
