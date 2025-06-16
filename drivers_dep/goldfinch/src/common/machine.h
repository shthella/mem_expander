/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */
/* ----------------------------------- */
/* ----------------------------------- */

#ifndef ASSEMBLY

#include <common/platform.h>

#ifdef __METAL_MACHINE_MACROS

#ifndef MACROS_IF_METAL_H
#define MACROS_IF_METAL_H

#ifndef __METAL_CLINT_NUM_PARENTS
#define __METAL_CLINT_NUM_PARENTS 0
#endif
#ifndef __METAL_PLIC_SUBINTERRUPTS
#define __METAL_PLIC_SUBINTERRUPTS 0
#endif
#ifndef __METAL_PLIC_NUM_PARENTS
#define __METAL_PLIC_NUM_PARENTS 0
#endif
#define __METAL_CLIC_SUBINTERRUPTS 80

#ifndef __METAL_CLIC_SUBINTERRUPTS
#define __METAL_CLIC_SUBINTERRUPTS 0
#endif

#endif /* MACROS_IF_METAL_H*/

#else /* ! __METAL_MACHINE_MACROS */

#ifndef MACROS_ELSE_METAL_H
#define MACROS_ELSE_METAL_H

#define METAL_MAX_UART_INTERRUPTS 0

#define METAL_MAX_CLINT_INTERRUPTS 0

#define __METAL_CLINT_NUM_PARENTS 0

#define __METAL_PLIC_SUBINTERRUPTS 0
#define METAL_MAX_PLIC_INTERRUPTS 0

#define __METAL_PLIC_NUM_PARENTS 0

#define __METAL_INTERRUPT_CONTROLLER_2000000_INTERRUPTS 4

#define __METAL_CLIC_SUBINTERRUPTS 80

#define METAL_MAX_CLIC_INTERRUPTS 4

#define __METAL_LOCAL_EXTERNAL_INTERRUPTS_0_INTERRUPTS 64

#define METAL_MAX_LOCAL_EXT_INTERRUPTS 64

#define METAL_MAX_GLOBAL_EXT_INTERRUPTS 0

#define __METAL_GPIO_20005000_INTERRUPTS 0

#define METAL_MAX_GPIO_INTERRUPTS 0

#define METAL_MAX_I2C0_INTERRUPTS 0

#define METAL_MAX_PWM0_INTERRUPTS 0

#define METAL_MAX_PWM0_NCMP 0

#define __METAL_SERIAL_20004000_INTERRUPTS 0

#define METAL_MAX_UART_INTERRUPTS 0

#define METAL_MAX_SIMUART_INTERRUPTS 0


#include <common/fixed-clock.h>
#include <memory.h>
#include <common/riscv_cpu.h>
#include <pmp.h>
#include <sifive_clic0.h>
#include <sifive_local-external-interrupts0.h>
#include <sifive_gpio0.h>
#include <sifive_spi0.h>
#include <sifive_uart0.h>

/* From subsystem_pbus_clock */
extern struct __metal_driver_fixed_clock __metal_dt_subsystem_pbus_clock;

extern struct metal_memory __metal_dt_mem_sys_sram_0_80000000;

extern struct metal_memory __metal_dt_mem_sys_sram_1_80040000;

extern struct metal_memory __metal_dt_mem_testram_20000000;

extern struct metal_memory __metal_dt_mem_testram_30000000;

extern struct metal_memory __metal_dt_mem_spi_20000000;

/* From cpu@0 */
extern struct __metal_driver_cpu __metal_dt_cpu_0;

extern struct __metal_driver_riscv_cpu_intc __metal_dt_cpu_0_interrupt_controller;

extern struct metal_pmp __metal_dt_pmp;

/* From interrupt_controller@2000000 */
extern struct __metal_driver_sifive_clic0 __metal_dt_interrupt_controller_2000000;

/* From local_external_interrupts_0 */
extern struct __metal_driver_sifive_local_external_interrupts0 __metal_dt_local_external_interrupts_0;

/* From gpio@20005000 */
extern struct __metal_driver_sifive_gpio0 __metal_dt_gpio_20005000;

/* From spi@20000000 */
extern struct __metal_driver_sifive_spi0 __metal_dt_spi_20000000;

/* From serial@20004000 */
extern struct __metal_driver_sifive_uart0 __metal_dt_serial_20004000;



/* --------------------- fixed_clock ------------ */
static __inline__ unsigned long __metal_driver_fixed_clock_rate(const struct metal_clock *clock)
{
	if ((uintptr_t)clock == (uintptr_t)&__metal_dt_subsystem_pbus_clock) {
		return METAL_FIXED_CLOCK__CLOCK_FREQUENCY;
	}
	else {
		return 0;
	}
}



/* --------------------- fixed_factor_clock ------------ */


/* --------------------- bl_secure0 ------------ */


/* --------------------- bl_sflash0 ------------ */


/* --------------------- qemu_imsic0 ------------ */


/* --------------------- qemu_uart0 ------------ */


/* --------------------- sifive_clint0 ------------ */


/* --------------------- cpu ------------ */
static __inline__ int __metal_driver_cpu_hartid(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 0;
	}
	else {
		return -1;
	}
}

static __inline__ int __metal_driver_cpu_timebase(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 1000000;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_cpu_interrupt_controller(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return &__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_cpu_num_pmp_regions(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return 4;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_buserror * __metal_driver_cpu_buserror(struct metal_cpu *cpu)
{
	if ((uintptr_t)cpu == (uintptr_t)&__metal_dt_cpu_0) {
		return NULL;
	}
	else {
		return NULL;
	}
}



/* --------------------- sifive_plic0 ------------ */


/* --------------------- sifive_buserror0 ------------ */


/* --------------------- sifive_clic0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_clic0_control_base(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_clic0_control_size(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_clic0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_MAX_CLIC_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_clic0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return (struct metal_interrupt *)&__metal_dt_cpu_0_interrupt_controller.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_clic0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 3;
	}
	else if (idx == 1) {
		return 3;
	}
	else if (idx == 2) {
		return 7;
	}
	else if (idx == 3) {
		return 11;
	}
	else if (idx == 4) {
		return 12;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_clic0_max_levels(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIFIVE_NUMLEVELS;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_clic0_num_subinterrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIFIVE_NUMINTS;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_clic0_num_intbits(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_interrupt_controller_2000000) {
		return METAL_SIFIVE_CLIC0_2000000_SIFIVE_NUMINTBITS;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_dutimer0 ------------ */


/* --------------------- sifive_local_external_interrupts0 ------------ */
static __inline__ struct metal_interrupt * __metal_driver_sifive_local_external_interrupts0_interrupt_parent(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return (struct metal_interrupt *)&__metal_dt_interrupt_controller_2000000.controller;
	}
	else {
		return NULL;
	}
}

static __inline__ int __metal_driver_sifive_local_external_interrupts0_num_interrupts(struct metal_interrupt *controller)
{
	if ((uintptr_t)controller == (uintptr_t)&__metal_dt_local_external_interrupts_0) {
		return METAL_MAX_LOCAL_EXT_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_local_external_interrupts0_interrupt_lines(struct metal_interrupt *controller, int idx)
{
	if (idx == 0) {
		return 16;
	}
	else if (idx == 1) {
		return 17;
	}
	else if (idx == 2) {
		return 18;
	}
	else if (idx == 3) {
		return 19;
	}
	else if (idx == 4) {
		return 20;
	}
	else if (idx == 5) {
		return 21;
	}
	else if (idx == 6) {
		return 22;
	}
	else if (idx == 7) {
		return 23;
	}
	else if (idx == 8) {
		return 24;
	}
	else if (idx == 9) {
		return 25;
	}
	else if (idx == 10) {
		return 26;
	}
	else if (idx == 11) {
		return 27;
	}
	else if (idx == 12) {
		return 28;
	}
	else if (idx == 13) {
		return 29;
	}
	else if (idx == 14) {
		return 30;
	}
	else if (idx == 15) {
		return 31;
	}
	else if (idx == 16) {
		return 32;
	}
	else if (idx == 17) {
		return 33;
	}
	else if (idx == 18) {
		return 34;
	}
	else if (idx == 19) {
		return 35;
	}
	else if (idx == 20) {
		return 36;
	}
	else if (idx == 21) {
		return 37;
	}
	else if (idx == 22) {
		return 38;
	}
	else if (idx == 23) {
		return 39;
	}
	else if (idx == 24) {
		return 40;
	}
	else if (idx == 25) {
		return 41;
	}
	else if (idx == 26) {
		return 42;
	}
	else if (idx == 27) {
		return 43;
	}
	else if (idx == 28) {
		return 44;
	}
	else if (idx == 29) {
		return 45;
	}
	else if (idx == 30) {
		return 46;
	}
	else if (idx == 31) {
		return 47;
	}
	else if (idx == 32) {
		return 48;
	}
	else if (idx == 33) {
		return 49;
	}
	else if (idx == 34) {
		return 50;
	}
	else if (idx == 35) {
		return 51;
	}
	else if (idx == 36) {
		return 52;
	}
	else if (idx == 37) {
		return 53;
	}
	else if (idx == 38) {
		return 54;
	}
	else if (idx == 39) {
		return 55;
	}
	else if (idx == 40) {
		return 56;
	}
	else if (idx == 41) {
		return 57;
	}
	else if (idx == 42) {
		return 58;
	}
	else if (idx == 43) {
		return 59;
	}
	else if (idx == 44) {
		return 60;
	}
	else if (idx == 45) {
		return 61;
	}
	else if (idx == 46) {
		return 62;
	}
	else if (idx == 47) {
		return 63;
	}
	else if (idx == 48) {
		return 64;
	}
	else if (idx == 49) {
		return 65;
	}
	else if (idx == 50) {
		return 66;
	}
	else if (idx == 51) {
		return 67;
	}
	else if (idx == 52) {
		return 68;
	}
	else if (idx == 53) {
		return 69;
	}
	else if (idx == 54) {
		return 70;
	}
	else if (idx == 55) {
		return 71;
	}
	else if (idx == 56) {
		return 72;
	}
	else if (idx == 57) {
		return 73;
	}
	else if (idx == 58) {
		return 74;
	}
	else if (idx == 59) {
		return 75;
	}
	else if (idx == 60) {
		return 76;
	}
	else if (idx == 61) {
		return 77;
	}
	else if (idx == 62) {
		return 78;
	}
	else if (idx == 63) {
		return 79;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_global_external_interrupts0 ------------ */


/* --------------------- sifive_gpio0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_gpio0_base(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20005000) {
		return METAL_SIFIVE_GPIO0_20005000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_gpio0_size(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20005000) {
		return METAL_SIFIVE_GPIO0_20005000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_gpio0_num_interrupts(struct metal_gpio *gpio)
{
	if ((uintptr_t)gpio == (uintptr_t)&__metal_dt_gpio_20005000) {
		return METAL_MAX_GPIO_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_gpio0_interrupt_parent(struct metal_gpio *gpio)
{
		return NULL;
}

static __inline__ int __metal_driver_sifive_gpio0_interrupt_lines(struct metal_gpio *gpio, int idx)
{
		return 0;
}



/* --------------------- sifive_gpio_button ------------ */


/* --------------------- sifive_gpio_led ------------ */


/* --------------------- sifive_gpio_switch ------------ */


/* --------------------- sifive_i2c0 ------------ */


/* --------------------- sifive_pwm0 ------------ */


/* --------------------- sifive_rtc0 ------------ */

static __inline__ unsigned long __metal_driver_sifive_spi0_control_base(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20000000) {
		return METAL_SIFIVE_SPI0_20000000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_control_size(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20000000) {
		return METAL_SIFIVE_SPI0_20000000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_spi0_clock(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20000000) {
		return (struct metal_clock *)&__metal_dt_subsystem_pbus_clock.clock;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_spi0_pinmux(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20000000) {
		return (struct __metal_driver_sifive_gpio0 *)&__metal_dt_interrupt_controller_2000000;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_output_selector(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20000000) {
		return 7;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_spi0_pinmux_source_selector(struct metal_spi *spi)
{
	if ((uintptr_t)spi == (uintptr_t)&__metal_dt_spi_20000000) {
		return 3;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_test0 ------------ */


/* --------------------- sifive_trace ------------ */

/* --------------------- sifive_trng0 ------------ */


/* --------------------- sifive_uart0 ------------ */
static __inline__ unsigned long __metal_driver_sifive_uart0_control_base(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return METAL_SIFIVE_UART0_20004000_BASE_ADDRESS;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_control_size(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return METAL_SIFIVE_UART0_20004000_SIZE;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_uart0_num_interrupts(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return METAL_MAX_UART_INTERRUPTS;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_interrupt * __metal_driver_sifive_uart0_interrupt_parent(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return NULL;
	}
	else {
		return 0;
	}
}

static __inline__ int __metal_driver_sifive_uart0_interrupt_line(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return 0;
	}
	else {
		return 0;
	}
}

static __inline__ struct metal_clock * __metal_driver_sifive_uart0_clock(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return (struct metal_clock *)&__metal_dt_subsystem_pbus_clock.clock;
	}
	else {
		return 0;
	}
}

static __inline__ struct __metal_driver_sifive_gpio0 * __metal_driver_sifive_uart0_pinmux(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return (struct __metal_driver_sifive_gpio0 *)&__metal_dt_gpio_20005000;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_output_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return 2;
	}
	else {
		return 0;
	}
}

static __inline__ unsigned long __metal_driver_sifive_uart0_pinmux_source_selector(struct metal_uart *uart)
{
	if ((uintptr_t)uart == (uintptr_t)&__metal_dt_serial_20004000) {
		return 3;
	}
	else {
		return 0;
	}
}



/* --------------------- sifive_simuart0 ------------ */


/* --------------------- sifive_wdog0 ------------ */


/* --------------------- sifive_fe310_g000_hfrosc ------------ */


/* --------------------- sifive_fe310_g000_hfxosc ------------ */


/* --------------------- sifive_fe310_g000_lfrosc ------------ */


/* --------------------- sifive_fe310_g000_pll ------------ */


/* --------------------- sifive_fe310_g000_prci ------------ */


#define __METAL_DT_MAX_MEMORIES 4

__asm__ (".weak __metal_memory_table");
struct metal_memory *__metal_memory_table[] = {
					&__metal_dt_mem_sys_sram_0_80000000,
					&__metal_dt_mem_sys_sram_1_80040000,
					&__metal_dt_mem_testram_20000000,
					&__metal_dt_mem_testram_30000000};

/* From serial@20004000 */
#define __METAL_DT_STDOUT_UART_HANDLE (&__metal_dt_serial_20004000.uart)

#define __METAL_DT_SERIAL_20004000_HANDLE (&__metal_dt_serial_20004000.uart)

#define __METAL_DT_STDOUT_UART_BAUD 115200

#define __METAL_DT_MAX_SECURES 0

__asm__ (".weak __metal_secure_table");
struct __metal_driver_bl_secure0 *__metal_secure_table[] = {
					NULL };
#define __METAL_DT_MAX_SFLASHS 0

__asm__ (".weak __metal_sflash_table");
struct __metal_driver_bl_sflash0 *__metal_sflash_table[] = {
					NULL };
#define __METAL_DT_MAX_IMSICS 0

__asm__ (".weak __metal_imsic_table");
struct __metal_driver_qemu_imsic0 *__metal_imsic_table[] = {
					NULL };
#define __METAL_DT_MAX_QEMU_UARTS 0

__asm__ (".weak __metal_qemu_uart_table");
struct __metal_driver_qemu_uart0 *__metal_qemu_uart_table[] = {
					NULL };
#define __METAL_DT_MAX_HARTS 1

__asm__ (".weak __metal_cpu_table");
struct __metal_driver_cpu *__metal_cpu_table[] = {
					&__metal_dt_cpu_0};

#define __METAL_DT_PMP_HANDLE (&__metal_dt_pmp)

/* From interrupt_controller@2000000 */
#define __METAL_DT_SIFIVE_CLIC0_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

#define __METAL_DT_INTERRUPT_CONTROLLER_2000000_HANDLE (&__metal_dt_interrupt_controller_2000000.controller)

#define __METAL_DT_MAX_DTIMERS 0

__asm__ (".weak __metal_dutimer_table");
struct __metal_driver_sifive_dutimer0 *__metal_dutimer_table[] = {
					NULL };
#define __MEE_DT_MAX_GPIOS 1

__asm__ (".weak __metal_gpio_table");
struct __metal_driver_sifive_gpio0 *__metal_gpio_table[] = {
					&__metal_dt_gpio_20005000};

#define __METAL_DT_MAX_BUTTONS 0

__asm__ (".weak __metal_button_table");
struct __metal_driver_sifive_gpio_button *__metal_button_table[] = {
					NULL };
#define __METAL_DT_MAX_LEDS 0

__asm__ (".weak __metal_led_table");
struct __metal_driver_sifive_gpio_led *__metal_led_table[] = {
					NULL };
#define __METAL_DT_MAX_SWITCHES 0

__asm__ (".weak __metal_switch_table");
struct __metal_driver_sifive_gpio_switch *__metal_switch_table[] = {
					NULL };
#define __METAL_DT_MAX_I2CS 0

__asm__ (".weak __metal_i2c_table");
struct __metal_driver_sifive_i2c0 *__metal_i2c_table[] = {
					NULL };
#define __METAL_DT_MAX_PWMS 0

__asm__ (".weak __metal_pwm_table");
struct __metal_driver_sifive_pwm0 *__metal_pwm_table[] = {
					NULL };
#define __METAL_DT_MAX_RTCS 0

__asm__ (".weak __metal_rtc_table");
struct __metal_driver_sifive_rtc0 *__metal_rtc_table[] = {
					NULL };
#define __METAL_DT_MAX_SPIS 1

__asm__ (".weak __metal_spi_table");
struct __metal_driver_sifive_spi0 *__metal_spi_table[] = {
					&__metal_dt_spi_20000000};

#define __METAL_DT_MAX_TRNGS 0

__asm__ (".weak __metal_trng_table");
struct __metal_driver_sifive_trng0 *__metal_trng_table[] = {
					NULL };
#define __METAL_DT_MAX_UARTS 1

__asm__ (".weak __metal_uart_table");
struct __metal_driver_sifive_uart0 *__metal_uart_table[] = {
					&__metal_dt_serial_20004000};

#define __METAL_DT_MAX_SIMUARTS 0

__asm__ (".weak __metal_simuart_table");
struct __metal_driver_sifive_simuart0 *__metal_simuart_table[] = {
					NULL };
#define __METAL_DT_MAX_WDOGS 0

__asm__ (".weak __metal_wdog_table");
struct __metal_driver_sifive_wdog0 *__metal_wdog_table[] = {
					NULL };
#endif /* MACROS_ELSE_METAL_H*/

#endif /* ! __METAL_MACHINE_MACROS */

#endif /* ! ASSEMBLY */
