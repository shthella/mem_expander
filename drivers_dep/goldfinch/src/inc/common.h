#ifndef _COMMON_H
#define _COMMON_H 1

#include <stdio.h>
#include "uart.h"
#define ENABLE_PRINTF 1

#define DDR_ARCH_BASE_ADDR 0x22000000
#define DMEM_BASE_ADDR 0x54000

#ifdef ENABLE_PRINTF
#define readl(a)      (*(volatile unsigned int *)((DDR_ARCH_BASE_ADDR) + ((a) << 2)))
//#define readl(a) printf("Value %x\n", a)
#define writel(a, v)  printf("0x%x 0x%x\n", a, v)

////#define read_mc(a) printf("Value %x\n", a)
#define read_mc(a)      (*(volatile unsigned int *)(a))
#define write_mc(a, v)  printf("0x%x 0x%x\n", a, v)
//#define writel(a, v)  printf("Addr 0x%x Value 0x%x\n", a, v)
#else
/* readl() and writel() defined for ddr phy init */
#define readl(a)      (*(volatile unsigned int *)((DDR_ARCH_BASE_ADDR) + ((a) << 2)))
#define writel(a, v) (*(volatile unsigned int *)((DDR_ARCH_BASE_ADDR) + ((a) << 2))) = (unsigned int)(v)
/* read() and write() defined for reset of the ddr phy init */
#define write_mc(a, v)  (*(volatile unsigned int *)(a)) = (unsigned int)(v)
#define read_mc(a)      (*(volatile unsigned int *)(a))
#endif

/* Below variables updated from Flash */
extern unsigned int pstate_num;
extern unsigned int dram_freq;
extern unsigned int dfi_freq_ratio;
extern unsigned int x8_device;
extern unsigned int skip_training;
extern unsigned int cs_dimm0;
extern unsigned int cs_dimm1;
extern unsigned int rank_num;
extern unsigned int ad_mirror;
extern unsigned int cs_mode;

/* General purpose variables */
extern unsigned int addr, value, offset, offset1, offset2;
extern unsigned int addr1, addr2, g_offset;

extern void phy_config_init(void);
extern void skip_traininig_1_or_2(void);
extern void imem_init(void);
extern void dmem_init(int);
extern void run_training_firmware(void);
extern void load_phy_init_engine(void);
#endif
