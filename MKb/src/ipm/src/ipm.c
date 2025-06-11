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


#include "periph_csr_map.h"
#include "tb_defines.h"
#include "phy_csr_common_defines.h"
//#include <baremetal_int.c>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

// Scratchpad
unsigned char buf[20480] __attribute__((section (".myBufSection"))) __attribute__((__used__));
unsigned char buf1[180] __attribute__((section (".myBufSection"))) __attribute__((__used__));

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

const uint32_t cfg_wl = 10;
const uint32_t cfg_rl = 20;
const uint32_t cfg_tdqsck = 2;
const uint32_t cfg_tdqss = 1;
const uint32_t cfg_tphy_wrlat = cfg_wl + cfg_tdqss - 3;

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

int sizeoflog=0;


void print_info(char* format, ...) {
    // Need mechanism to figure out # of characters
    // so as to advance the pointer for the next print
    char temp_str[256]; // No one print_info statement can be longer than this
    va_list argList;
    #if IPM_PRINT_INFO
      va_start(argList, format);
      vsprintf(buf+sizeoflog,format, argList);
      vsprintf(buf1,format, argList);
      vsprintf(temp_str,format,argList);
      va_end(argList);
    #endif
    sizeoflog=sizeoflog+strlen(temp_str)+2;
    memset(buf1, '\0', sizeof(buf1));
}

void print_dbg(char* format, ...) {
    // Need mechanism to figure out # of characters
    // so as to advance the pointer for the next print
    char temp_str[256]; // No one print_info statement can be longer than this
    va_list argList;
    #if IPM_PRINT_DBG
      va_start(argList, format);
      vsprintf(buf+sizeoflog,format, argList);
      vsprintf(buf1,format, argList);
      vsprintf(temp_str,format,argList);
      va_end(argList);
    #endif
    sizeoflog=sizeoflog+strlen(temp_str)+2;
    memset(buf1, '\0', sizeof(buf1));
}

void print_err(char* format, ...) {
    // Need mechanism to figure out # of characters
    // so as to advance the pointer for the next print
    char temp_str[256]; // No one print_info statement can be longer than this
    va_list argList;
    va_start(argList, format);
    vsprintf(buf+sizeoflog,format, argList);
    vsprintf(buf1,format, argList);
    vsprintf(temp_str,format,argList);
    va_end(argList);
    sizeoflog=sizeoflog+strlen(temp_str)+2;
    memset(buf1, '\0', sizeof(buf1));
}

//-------------------------------------------------------------------------
// main function
//-------------------------------------------------------------------------


int ipm_init(void) {

  print_info("IPM::TRN::MAIN:: PHY one time settings start\n");
  phy_init(CH_MIN,CH_MAX);
  delay(100);
  phy_training(CH_MIN,CH_MAX);

  /*
  while (1) {
    asm volatile ("wfi");
  }
  */

  return 0;
}

