#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

typedef enum {
	TEST_SUCCESS,
	TEST_FAILURE
} e_status;

#define readc(a)      (*(volatile unsigned char *)(a))
#define writec(v, a)  (*(volatile unsigned char *)(a)) = (unsigned char)(v)
#define reads(a)      (*(volatile unsigned short *)(a))
#define writes(v, a)  (*(volatile unsigned short *)(a)) = (unsigned short)(v)
#define readl(a)      (*(volatile unsigned int *)(a))
#define writel(v, a)  (*(volatile unsigned int *)(a)) = (unsigned int)(v)
#define readw(a)      (*(volatile unsigned long long *)(a))
#define writew(v, a)  (*(volatile unsigned long long *)(a)) = (unsigned long long)(v)
 

#endif
