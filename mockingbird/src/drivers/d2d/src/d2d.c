#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

#include "d2d.h"

uint32_t d2d_phy_read(uint32_t  regAddr, uint32_t regVal){
	//printf("Read addr:0x%08x, data:0x%x \n", (regAddr&0xFFFF0000|((regAddr&0xFFFF)<<1)), regVal);
	uint32_t addrVal = ((regAddr&0xFFFF)<<1);
	addrVal = (regAddr&0xFFFE0000) | addrVal;
    return readl(addrVal);
}

uint32_t d2d_phy_write(uint32_t  regAddr, uint32_t regVal){
	//printf("Write addr:0x%08x, data:0x%x \n", (regAddr&0xFFFF0000|((regAddr&0xFFFF)<<1)), regVal);
	uint32_t addrVal = ((regAddr&0xFFFF)<<1);
	addrVal = (regAddr&0xFFFE0000) | addrVal;
    writel(regVal, addrVal);
    return 0;
}

uint32_t d2d_ll_read(uint32_t regAddr, uint32_t regVal){
	//printf("Read addr:0x%08x, data:0x%x\n", regAddr, regVal);
	return readl(regAddr);
}

uint32_t d2d_ll_write(uint32_t regAddr, uint32_t regVal){
	//printf("Write addr:0x%08x, data:0x%x \n", regAddr, regVal);
	writel(regVal, regAddr);
	return 0;
}

