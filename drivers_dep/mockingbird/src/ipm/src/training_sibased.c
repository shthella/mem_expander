// Copyright (c) 2020 Blue Cheetah Analog Design, Inc.
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.

//**************************************************************************
//INCLUDE FILES
//**************************************************************************

#include <periph_csr_map.h>
#include <tb_defines.h>

#include <phy_csr_common_defines.h>
#include <baremetal_int.h>
//#include <baremetal_int.c>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

// Scratchpad
extern unsigned char buf[20480] __attribute__((section (".myBufSection"))) __attribute__((__used__));
extern unsigned char buf1[180] __attribute__((section (".myBufSection"))) __attribute__((__used__));

//**************************************************************************
//DEFINES
//**************************************************************************
#define BIT_SET(x,m,y)  ( (x) = ( ((x) & ~(1L<<(m))) | ((y)<<(m)) ) )
#define	BIT_GET(x,m)  (((x)  &  (1L<<(m))) >> (m))
#define BITS_SET(x,m,n,y) ( (x) = ((x) & ~((~(~0L<<((m)-(n)+1)))<<(n))) | ((y)<<(n)) )
#define BITS_GET(x,m,n)  (( (x)  &   (~(~0L<<((m)-(n)+1)))<<(n)) >> (n) )
#define BITS_2SCOMP(x)  ((~x) + 1)

//**************************************************************************
// Macros Based on compile flags
//**************************************************************************
#define WL_SETA 0
#define WL_SETB 1

#ifdef CHANNEL0_ONLY
  #define CH_MIN  0
  #define CH_MAX  0
#elif CHANNEL1_ONLY
  #define CH_MIN  1
  #define CH_MAX  1
#else
  #define CH_MIN  0
  #define CH_MAX  1
#endif
/*
 const uint32_t cfg_wl = 10;
 const uint32_t cfg_tdqss = 1;
 const uint32_t cfg_tphy_wrlat = cfg_wl + cfg_tdqss - 3;
*/

/*
void apb_poll_field(uint32_t field_code, uint16_t val) {
  uint16_t field_val = apb_read_field(field_code);
  while (field_val != val) {
    field_val = apb_read_field(field_code);
  }
}

void apb_poll_field_ch(uint32_t field_code, uint16_t val, uint32_t ch) {
  apb_poll_field(field_code + ch * CH_ADDR_OFFSET, val);
}

void delay(uint32_t training_time){
  uint32_t num_read = training_time;
#ifdef APB_10X
  num_read = num_read*10;
#elif APB_50X
  num_read = num_read*50;
#endif
  uint16_t read_data;
  for (int i = 0 ; i <= num_read; i++){
    read_data = apb_read(WDQ_PIPE_DLY_D0R0F0_ADDR); 
  }
} 

//-------------------------------------------------------------------------
// Training related tasks
//-------------------------------------------------------------------------


void clear_scratchpad() {
  memset(buf, '\0', sizeof(buf));
  memset(buf1, '\0', sizeof(buf1));
}
*/




//-------------------------------------------------------------------------
//PHY ISR: Handle PHY interrupt and determine interrupt type
//-------------------------------------------------------------------------

void phy_isr(int id, void *data) {
  // Determine which interrupt occurred
//  print_info("IPM:INTR: Inside PHY ISR E:\n");
  if(INTR_DFI_INIT_START & INTR_DFI_INIT_START_INTR_DFI_INIT_START_MASK) {
//   print_info("IPM:INTR: Requesting phy_training E:\n");
   phy_training(CH_MIN,CH_MAX);
  }else if (INTR_DFI_INIT_START & INTR_DFI_INIT_START_INTR_DFI_CTRLUPD_REQ_MASK) {
    //ctrlupd_isr();
  } else if (INTR_DFI_INIT_START & INTR_DFI_INIT_START_INTR_DFI_LP_CTRL_WAKEUP_CHNG_MASK) {
    //lp_isr();
  } else {
   // print_err("IPM:INTR: Interrupt not understood E:\n");
    // Clear all phy interrupts
    // WARNING: This ignores all unhandled interrupts!
    INTR_DFI_INIT_START = 0xFFFF;
    //metal_interrupt_clear(clic, phy_irq);
  } 
}

//-------------------------------------------------------------------------
// main function
//-------------------------------------------------------------------------

int training_main (void) {
  uint8_t clicintcfg;
  /* Write mstatus.mie = 0 to disable all machine interrupts prior to setup */
  
 // interrupt_global_disable();
  //configure_clic();

/* Program the level in clicintcfg.  Since we have nlbits=2, the upper
  * two bits of clicintcfg control the level, while the lower bits control the priority.
  * Here, we are going to leave the priority field 0x0, but depending on how many
  * clicintcfg bits are available, those can also be customized based on the application.
  *
  * Here, we enable local interrupt lines and setup handlers in the vector table.
  */
  clicintcfg = (3 << 6);
  __mtvt_clic_vector_table[PHY_EXT_INT_ID] = (uintptr_t)&phy_isr;
  write_byte(HART0_CLICINTCFG_ADDR(PHY_EXT_INT_ID), clicintcfg);
  PHY_INT_ENABLE;

  //PHY initial settings - Pll configuration and One time setting after reset
 // print_info("IPM::TRN::MAIN:: PHY one time settings start\n");
  phy_init(CH_MIN,CH_MAX);

  /* Write mstatus.mie = 1 to enable all machine interrupts */
 // print_info("IPM::TRN::MAIN:: Enable interrupts\n");
//  interrupt_global_enable();

  while (1) {
    asm volatile ("wfi");
  }

  return 0;
}

