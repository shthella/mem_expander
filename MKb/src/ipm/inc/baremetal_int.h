// Copyright (c) 2020 Blue Cheetah Analog Design, Inc. 
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.

#ifndef __BAREMETAL_INT_H__
#define __BAREMETAL_INT_H__

#include <riscv_cpu.h>
#include <platform.h>

#if __riscv_xlen == 32
#define MCAUSE_INTR 0x80000000UL
#define MCAUSE_CAUSE 0x000003FFUL
#else
#define MCAUSE_INTR 0x8000000000000000UL
#define MCAUSE_CAUSE 0x00000000000003FFUL
#endif
#define MCAUSE_CODE(cause) (cause & MCAUSE_CAUSE)

/* Interrupt Specific defines - used for mtvec.mode field, which is bit[0] for
 * designs with CLINT, or [1:0] for designs with a CLIC */
#define MTVEC_MODE_CLINT_DIRECT 0x00
#define MTVEC_MODE_CLINT_VECTORED 0x01
#define MTVEC_MODE_CLIC_DIRECT 0x02
#define MTVEC_MODE_CLIC_VECTORED 0x03

/* Offsets for multi-core systems */
#define MSIP_PER_HART_OFFSET 0x4
#define MTIMECMP_PER_HART_OFFSET 0x8

#define CLIC_BASE_ADDR METAL_SIFIVE_CLIC0_0_BASE_ADDRESS
#define MSIP_BASE_ADDR(hartid) (CLIC_BASE_ADDR + METAL_SIFIVE_CLIC0_MSIP_BASE + (hartid * MSIP_PER_HART_OFFSET))
#define MTIMECMP_BASE_ADDR(hartid) (CLIC_BASE_ADDR + METAL_SIFIVE_CLIC0_MTIMECMP_BASE + (hartid * MTIMECMP_PER_HART_OFFSET))
#define MTIME_BASE_ADDR (CLIC_BASE_ADDR + METAL_SIFIVE_CLIC0_MTIME)
#define HART0_CLIC_OFFSET 0x00800000
#define HART0_CLIC_BASE_ADDR (CLIC_BASE_ADDR + HART0_CLIC_OFFSET)
#define HART0_CLICINTIP_ADDR(int_num) (HART0_CLIC_BASE_ADDR + METAL_SIFIVE_CLIC0_CLICINTIP_BASE + int_num)   /* one byte per enable */
#define HART0_CLICINTIE_ADDR(int_num) (HART0_CLIC_BASE_ADDR + METAL_SIFIVE_CLIC0_CLICINTIE_BASE + int_num)   /* one byte per enable */
#define HART0_CLICINTCFG_ADDR(int_num) (HART0_CLIC_BASE_ADDR + METAL_SIFIVE_CLIC0_CLICINTCTL_BASE + int_num)   /* one byte per enable */
#define HART0_CLICCFG_ADDR (HART0_CLIC_BASE_ADDR + METAL_SIFIVE_CLIC0_CLICCFG)   /* one byte per CLIC */
#define CLICCFG_NVBITS(x) ((x & 1) << 0)
#define CLICCFG_NLBITS(x) ((x & 0xF) << 1)
#define CLICCFG_NMBITS(x) ((x & 0x3) << 5)
#define PHY_EXT_INT_ID 16
#define MAX_LOCAL_INTS 16  /* local interrupts, not local external interrupts */
#define CLIC_VECTOR_TABLE_SIZE_MAX 1024
#define PHY_INT_ENABLE write_byte(HART0_CLICINTIE_ADDR(PHY_EXT_INT_ID), 1);
#define PHY_INT_EDISABLE write_byte(HART0_CLICINTIE_ADDR(PHY_EXT_INT_ID), 0);

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })
#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })
#define write_dword(addr, data) ((*(uint64_t *)(addr)) = data)
#define read_dword(addr) (*(uint64_t *)(addr))
#define write_word(addr, data) ((*(uint32_t *)(addr)) = data)
#define read_word(addr) (*(uint32_t *)(addr))
#define write_byte(addr, data) ((*(uint8_t *)(addr)) = data)
#define read_byte(addr) (*(uint8_t *)(addr))
#define CLICCFG_NVBITS(x) ((x & 1) << 0)
#define CLICCFG_NLBITS(x) ((x & 0xF) << 1)
#define CLICCFG_NMBITS(x) ((x & 0x3) << 5)

void interrupt_global_enable (void);
void interrupt_global_disable (void);
void configure_clic(void);
void __attribute__ ((interrupt("SiFive-CLIC-preemptible"))) software_handler (void);
void __attribute__ ((interrupt("SiFive-CLIC-preemptible"))) timer_handler (void);

void __attribute__((weak, interrupt)) __mtvec_clint_vector_table(void);
__attribute__((aligned(64))) uintptr_t __mtvt_clic_vector_table[CLIC_VECTOR_TABLE_SIZE_MAX];

// void interrupt_global_enable (void) {
//   uintptr_t m;
//   __asm__ volatile ("csrrs %0, mstatus, %1" : "=r"(m) : "r"(METAL_MIE_INTERRUPT));
// }

// void interrupt_global_disable (void) {
//   uintptr_t m;
//   __asm__ volatile ("csrrc %0, mstatus, %1" : "=r"(m) : "r"(METAL_MIE_INTERRUPT));
// }

// void configure_clic(void) {
//   uint32_t mode = MTVEC_MODE_CLIC_VECTORED;
//   uintptr_t mtvec_base, mtvt_base;
//   uint8_t cliccfg, nlbits;

//   /* Setup mtvec to point to our exception handler table using mtvec.base,
//   * and assign mtvec.mode = 3 for CLIC vectored mode of operation. The
//   * mtvec.mode field is bit[0] for designs with CLINT, or [1:0] using CLIC */
//   mtvec_base = (uintptr_t)&__mtvec_clint_vector_table;
//   write_csr (mtvec, (mtvec_base | mode));

//   /* Setup mtvt which is CLIC specific, to hold base address for interrupt handlers */
//   mtvt_base = (uintptr_t)&__mtvt_clic_vector_table;
//   write_csr (0x307, (mtvt_base));  /* 0x307 is CLIC CSR number */

//   /* Use cliccfg.NLBITS to set number of BITS to used to program the levels in clicintcfg.
//   * Use the macro below to put it in the right place.
//   *
//   *  >>> For designs with only clicintcfg[7:6] available, when nlbits=2,
//   *  clicintcfg[7:6] bits are used to determine levels only.
//   *
//   *  Only higher levels can preempt lower levels.
//   *  Priorities are used to break a tie if two interrupts of the same level arrive at the hart at the same time.
//   */
//   nlbits = 0x2;
//   cliccfg = (CLICCFG_NVBITS(0) | CLICCFG_NLBITS(nlbits) | CLICCFG_NMBITS(0));
//   write_byte(HART0_CLICCFG_ADDR, cliccfg);
// }

#endif
