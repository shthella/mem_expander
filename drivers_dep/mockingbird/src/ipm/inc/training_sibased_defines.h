// Copyright (c) 2020 Blue Cheetah Analog Design, Inc. 
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.

#ifndef __TRAINING_DEFINES_H__
#define __TRAINING_DEFINES_H__

//------------------------------------------------------------------
//GENERAL DEFINES
//------------------------------------------------------------------
#define AFTER_POWER_ON_RESET_ACCESS_DELAY 12 //#500ns;
#define INTERMEDIATE_RESET_DELAY 1 //#5ns;
#define SMARTDV_VIP_BRINGUP_DELAY 3 //#100ns;
#define TOTAL_TRN_IDX 4 

#define IPM_PRINT_INFO 1  // Important information messages
#define IPM_PRINT_DBG 0   // Debug messages

//------------------------------------------------------------------
//TRAINING DEFINES
//------------------------------------------------------------------
#define SI_ENV 0         // Silicon settings vs sim settings
#if SI_ENV
  #define t_INIT0        (100*1  ) //#2ns   /* Assumed value */
  #define t_INIT1        (200*5  ) //#200ns //#200us /* Downscaled for faster simulation */
  #define t_INIT3        (200*5*10) //#200ns //#2ms /* Downscaled for faster simulation */
  #define t_INIT5        (100*50 ) //#2us
  #define t_ZQCAL        (100*125) //#5us // 1us min value
  #define t_ZQLAT        (100*1  )//#30ns // Max(30ns,8tCK)
#else
  #define t_INIT0        1   //#2ns   /* Assumed value */
  #define t_INIT1        5   //#200ns //#200us /* Downscaled for faster simulation */
  #define t_INIT3        5   //#200ns //#2ms /* Downscaled for faster simulation */
  #define t_INIT5        50  //#2us
  #define t_ZQCAL        125 //#5us // 1us min value
  #define t_ZQLAT         1  //#30ns // Max(30ns,8tCK)
#endif

#define t_VRCG_ENABLE   5  //#200ns
#define t_MRD          5   //#200ns;         // FIXME FLC Spec does not have this number
#define t_VREFLONG     6   //#250ns;      // FIXME FLC value not available. Using LP4x value
#define t_MRW  5               //# of dfi_clk cycle delays after MRW command. FIXME: get value for FLC
#define t_MPC  5               //# of dfi_clk cycle delays after an MPC command. FIXME: get value from FLC
#define t_WTR   1  //#7.5ns
#define t_PIPE_SETTLE 2
#define t_PATBUF_LPBK_DLY 1   //#20ns
#define t_DQSCK_MIN   1500    //#
#define t_DQSCK_MAX   2500    //ps
#define t_PIPE_RSTN 6 //#200ns //added mitzi
#define t_PIPEDELAY                5 //#200ns      // Conservative latency of write pipeline (CC/DQ/DQS etc)
#define t_CKCKEH 2 //#50ns
#define t_CKELCK 2//#50ns
#define t_XCBT                     7 // #300ns
#define t_CKEWAIT                  5 //#200ns       //Generic wait after CKE change
#define t_CKSTOP                   2
#define t_PTRN_DONE                8 // Extra wait for ptrn_done to de-assert
//-----------------------------------------------------------------
//Bits per slice
//------------------------------------------------------------------
#define DQ_BITS_PER_SLICE 17

//----------------------------------------------------
//------------ PHY Rx & Tx parameters: TT corner
//----------------------------------------------------
#define ZCODE_PU40 31   // 40 ohm
#define ZCODE_PD40 31   // 40 ohm
#define ZCODE_PU60 18
#define ZCODE_PD60 18
#define ZCODE_PU ZCODE_PU40
#define ZCODE_PD ZCODE_PD40
#define VREF_VDDQBY2    (256/2)     // vref=vddq/2
#define VREF_VDDQBY4    (256*3/4)     // vref=vddq/4
#define VREF_VDDQBY8    (256*7/8)     // vref=vddq/4

//----------------------------------------------------
//------------ DRAM Rx & Tx parameters: TT corner
//----------------------------------------------------
#define DRAM_DQ_DRV 0b110  // 40ohm. PDDS MRW table
#define DRAM_PU_CAL 0b010  // PDDS in DRAM MRW table

//----------------------------------------------------
//------------ Choose Re-training steps
//----------------------------------------------------
#define LPBK_RETRAIN 1
#define CROSS_RETRAIN 1
#define CA_RETRAIN 1
#define WRLVL_RETRAIN 1
#define RDPRE_RETRAIN 1
#define RDDQ_RETRAIN 1
#define WRDQ_RETRAIN 1

//----------------------------------------------------
//------------ MPC Opcodes         -------------------
//----------------------------------------------------
#define MPC_RD_FIFO         0x41//7'b1000001
#define MPC_RD_DQCAL        0x43//7'b1000011
#define MPC_WR_FIFO         0x47//7'b1000111
#define MPC_START_DQS_OSC   0x4b//7'b1001011
#define MPC_STOP_DQS_OSC    0x4d//7'b1001101
#define ZQCAL_START         0x4f//7'b1001111
#define ZQCAL_LATCH         0x51//7'b1010001

//----------------------------------------------------
//------------ Oscillator Thresholds -----------------
//----------------------------------------------------
#define PHY_OSC_THLD_HI     0.01  // %age variation on the high side to trigger retrain
#define PHY_OSC_THLD_LO     0.01
#define DRAM_OSC_THLD_HI    0.01
#define DRAM_OSC_THLD_LO    0.01

//-----------------------------
// Min max channel #s
//-----------------------------
#define GLB_CH_MIN 0
#define GLB_CH_MAX 1

//-----------------------------
// Training array sizes
//-----------------------------
#define TRNOPT_MAXLEN 100
#define TRNARR_MAXLEN 200
#define TOTAL_TRN_IDX 4

//------------------------
// PLL DLL paramters
//------------------------
#define PLL_ADJ_POS_VAL         500
#define PLL_ADJ_NEG_VAL         -500
#define PLL_ACCUM_MAN_VAL       0x8EA000

#define DLL_ACCUM_OVRD_VAL      0xFF00FF
#define DLL_LOCKING_PERIOD      3000
#define DLL_LOCK_SWING          1000000
#define DLL_ACCUM_DELAY_STEP    2000

//------------------------
// RX delay line paramters
//------------------------
#define UI_0P5 0
#define UI_1P5 1
#define RDQS_DLL UI_0P5

//------------------------
// Boot parameters
//------------------------
#define BOOT_CAP_EN     7 
#define BOOT_CC_SDL_DELAY  20
#define BOOT_CK_SDL_DELAY  0
#define BOOT_CC_NUI        0
#define BOOT_CK_NUI        1
#define BOOT_CROSS_SEL      0b1

//---------------------------
//------ CK default delay----
//---------------------------
#define CK_DELAY_UI 1          // High speed ck delay/position

//------------------------
// Delay Line PARAMETERS
//------------------------
#define SDL_MIN 0
#define SDL_MAX 20

//------------------------
// SDLCROSS Training Parameters
//------------------------
#define SDL_TRAIN_MAX_CODE 20
#define SDL_TRAIN_CAP_EN_MAX 7
#define SDL_TRAIN_BL 6
#define SDL_TRAIN_WDQS_SDL 0
#define CROSS_MIN 0
#define CROSS_MAX 1
#define SDLCROSS_MERGE_WRPCODE 1  //Option to average the wraparound code across bytes.
#define MAX_CROSS_SEL_ITER 80
#if SI_ENV
  #define RDEN_EXTRA_DSTDLY 70
#else
  #define RDEN_EXTRA_DSTDLY 0
#endif

//-------------------------
// Loopback parameters
//--------------------------
#define LPBK_TRAIN_WDQS_SDL 0
#define LPBK_TRAIN_WDQS_NUI 4
#define LPBK_TRAIN_WDQ_NUI  4
#define LPBK_TRAIN_LPBK_INT 0 // Internal vs external lpbk
#if SI_ENV
  #define LPBK_TRAIN_VREF_MIN 100
  #define LPBK_TRAIN_VREF_MAX 200
  #define LPBK_TRAIN_VREF_STEP 15
  #define LPBK_TRAIN_DELAY_STEP 1
  #define LPBK_OVRSAMPLE_CNT 16
  #define LPBK_TRAIN_PASS_REGION_THLD 6
#else
  #define LPBK_TRAIN_VREF_MIN 100
  #define LPBK_TRAIN_VREF_MAX 100
  #define LPBK_TRAIN_VREF_STEP 15
  #define LPBK_TRAIN_DELAY_STEP 4
  #define LPBK_OVRSAMPLE_CNT 1
  #define LPBK_TRAIN_PASS_REGION_THLD 4
#endif
#define LPBK_TRAIN_DELAY_MIN SDL_MIN
#define LPBK_TRAIN_DELAY_MAX SDL_MAX
#define LPBK_KICK 0x3
#define LPBK_VRET_LEN  ( ( LPBK_TRAIN_VREF_MAX  - LPBK_TRAIN_VREF_MIN  ) / LPBK_TRAIN_VREF_STEP  + 1 ) 
#define LPBK_HORI_LEN  ( ( LPBK_TRAIN_DELAY_MAX - LPBK_TRAIN_DELAY_MIN ) / LPBK_TRAIN_DELAY_STEP + 1 )
#define LPBK_MAX_LEN   ( LPBK_VRET_LEN*LPBK_HORI_LEN + 1)
#define LPBK_TRAIN_PASS_REGION_DIFF 1

//----------------------------
// CA TRAINING parameters
//----------------------------
#define t_CATRAIN_STEP    3  //#100ns;      // DRAM asynchronous delay in sending latched data to DQ
#define t_CAENT        6   //#250ns;         // FIXME FLC value not available. Using LP4x value
#define t_DSTRAIN                   4       // Setup time for vref on DQ during ca training. # dfi_clk_cycles
#define t_DHTRAIN       cwRD            4       // Hold time for vref on DQ during ca training. # dfi_clk_cycles

// CA_VREF min=18, max=47, mid=32
#if SI_ENV
  #define CA_TRAIN_VREF_MIN  32  
  #define CA_TRAIN_VREF_MAX  32
  #define CA_TRAIN_VREF_STEP 3
  #define CA_TRAIN_VREF_COARSE_STEP 4
  #define CA_TRAIN_DELAY_MIN_UI 1
  #define CA_TRAIN_DELAY_MIN_UI_FRACTION 2  // Fraction of a UI on top of MIN_UI to be added. 2 means 1/2 UI will be added
  #define CA_TRAIN_DELAY_MAX_UI 4
  #define CA_TRAIN_DELAY_MAX_UI_FRACTION 2
  #define CA_TRAIN_DELAY_STEP 1
  #define CA_TRAIN_DELAY_COARSE_STEP 4
  #define CA_TRAIN_OVRSAMPLE_CNT  16
  #define CA_EXTRA_SRCDLY_CH0   60   // Extra delay of CA serializer clock compared to WDQ2 serializer clk 
  #define CA_EXTRA_SRCDLY_CH1   20 
#else
  #define CA_TRAIN_VREF_MIN  32  
  #define CA_TRAIN_VREF_MAX  32
  #define CA_TRAIN_VREF_STEP 4
  #define CA_TRAIN_VREF_COARSE_STEP 4
  #define CA_TRAIN_DELAY_MIN_UI 1
  #define CA_TRAIN_DELAY_MIN_UI_FRACTION 2  // Fraction of a UI on top of MIN_UI to be added. 2 means 1/2 UI will be added
  #define CA_TRAIN_DELAY_MAX_UI 3
  #define CA_TRAIN_DELAY_MAX_UI_FRACTION 2
  #define CA_TRAIN_DELAY_STEP 4
  #define CA_TRAIN_DELAY_COARSE_STEP 4
  #define CA_TRAIN_OVRSAMPLE_CNT  1
  #define CA_EXTRA_SRCDLY_CH0   15   // Extra delay of CA serializer clock compared to WDQ2 serializer clk 
  #define CA_EXTRA_SRCDLY_CH1   10 
#endif
#define CA_TRAIN_PAT_EARLY 0x200
#define CA_TRAIN_PAT_MID   0x3FF
#define CA_TRAIN_PAT_LATE  0x001
#define CA_TRAIN_OFFSET 2
#define CA_TRAIN_CS_PBD_DELAY  31  // Offset between CA and CS during CA training
   // Extra delay of CA serializer clock compared to WDQ2 serializer clk 
#define CA_VRET_LEN  ( ( CA_TRAIN_VREF_MAX  - CA_TRAIN_VREF_MIN  ) / CA_TRAIN_VREF_STEP  + 1 ) 
#define CA_HORI_LEN  ( ( ( CA_TRAIN_DELAY_MAX_UI - CA_TRAIN_DELAY_MIN_UI ) * ( SDL_MAX + 2 ) ) / CA_TRAIN_DELAY_STEP + 1 ) 
#define CA_MAX_LEN   ( CA_VRET_LEN*CA_HORI_LEN + 1)
#define CA_TRAIN_PASS_REGION_THLD 6
#define CA_TRAIN_PASS_REGION_DIFF 3


//------------------------
// WRLVL TRAINING parameters
//------------------------
//Wrlvl training parameters. Wrlvl needs to start from 4UI
//inorder to leave time for SDL turnon
#define t_WLDQSEN               1  //#50ns   //>= 20*tck
#define t_WLWPRE                1  //#50ns   //>= 20*tck
#define t_WRLVL_TRAIN_STEP      3  //#100ns  //<20ns
#if SI_ENV
  #define WRLVL_TRAIN_DELAY_MIN_UI 5
  #define WRLVL_TRAIN_DELAY_MIN_UI_FRACTION 21
  #define WRLVL_TRAIN_DELAY_MAX_UI 8
  #define WRLVL_TRAIN_DELAY_MAX_UI_FRACTION 2
  #define WRLVL_TRAIN_DELAY_STEP 1
#else
  #define WRLVL_TRAIN_DELAY_MIN_UI 6
  #define WRLVL_TRAIN_DELAY_MIN_UI_FRACTION 8
  #define WRLVL_TRAIN_DELAY_MAX_UI 10
  #define WRLVL_TRAIN_DELAY_MAX_UI_FRACTION 2
  #define WRLVL_TRAIN_DELAY_STEP 3
#endif
#define WRLVL_TRAIN_OFFSET 0

//------------------------
// RDPRE TRAINING parameters
//------------------------
#define t_RDPRE_TRAIN_STEP 3  //#100ns
#define RDPRE_TRAIN_BL 8    // Burst length of rddqcal mpc
#if SI_ENV
  #define RDPRE_TRAIN_DELAY_MIN_UI 6
  #define RDPRE_TRAIN_DELAY_MIN_UI_FRACTION 10
  #define RDPRE_TRAIN_DELAY_MAX_UI 11
  #define RDPRE_TRAIN_DELAY_MAX_UI_FRACTION 2
  #define RDPRE_TRAIN_DELAY_STEP 1
  #define RDPRE_TRAIN_OFFSET 1 // #NUI to be offset from trained location
#else
  #define RDPRE_TRAIN_DELAY_MIN_UI 7
  #define RDPRE_TRAIN_DELAY_MIN_UI_FRACTION 20 // 1/20th of a UI. Basically 0 delay
  #define RDPRE_TRAIN_DELAY_MAX_UI 10
  #define RDPRE_TRAIN_DELAY_MAX_UI_FRACTION 20
  #define RDPRE_TRAIN_DELAY_STEP 3
  #define RDPRE_TRAIN_OFFSET 1 // #NUI to be offset from trained location
#endif

//------------------------
//Read DQ Training parameter
//------------------------
#define t_RDDQ_TRAIN_STEP 3  //#100ns
#define RDDQ_TRAIN_BL 8    // Burst length of rddqcal mpc
#if SI_ENV
  #define RDDQ_TRAIN_DELAY_MIN 0
  #define RDDQ_TRAIN_DELAY_MAX 20
  #define RDDQ_TRAIN_DELAY_STEP 1
  #define RDDQ_TRAIN_VREF_MIN  70 // Place holder value for rtl sim
  #define RDDQ_TRAIN_VREF_MAX  200 
  #define RDDQ_TRAIN_VREF_STEP 10
  #define RDDQ_TRAIN_OVRSAMPLE_CNT  16
#else
  #define RDDQ_TRAIN_DELAY_MIN 0
  #define RDDQ_TRAIN_DELAY_MAX 20
  #define RDDQ_TRAIN_DELAY_STEP 2
  #define RDDQ_TRAIN_VREF_MIN  100 // Place holder value for rtl sim
  #define RDDQ_TRAIN_VREF_MAX  100 
  #define RDDQ_TRAIN_VREF_STEP 25
  #define RDDQ_TRAIN_OVRSAMPLE_CNT  1
#endif
#define RDDQ_VRET_LEN  ( ( RDDQ_TRAIN_VREF_MAX  - RDDQ_TRAIN_VREF_MIN  ) / RDDQ_TRAIN_VREF_STEP  + 1 ) 
#define RDDQ_HORI_LEN  ( ( RDDQ_TRAIN_DELAY_MAX - RDDQ_TRAIN_DELAY_MIN )  / RDDQ_TRAIN_DELAY_STEP + 1 ) 
#define RDDQ_MAX_LEN   ( RDDQ_VRET_LEN*RDDQ_HORI_LEN + 1)
#define RDDQ_TRAIN_PASS_REGION_THLD 4
#define RDDQ_TRAIN_PASS_REGION_DIFF 1

//------------------------
//Write DQ Training parameter
//------------------------
#define t_WRDQ_TRAIN_STEP 3  //#100ns
#define WRDQ_TRAIN_BL 8    // Burst length of rddqcal mpc
#define WRDQ_TRAIN_MAXBL 16    // Max possible BL
#if SI_ENV
  #define WRDQ_TRAIN_DELAY_MIN_UI 2
  #define WRDQ_TRAIN_DELAY_MAX_UI 7
  #define WRDQ_TRAIN_DELAY_STEP 1
  #define WRDQ_TRAIN_VREF_MIN  24  //FLC Spec: Min= 18 Max=47
  #define WRDQ_TRAIN_VREF_MAX  40 
  #define WRDQ_TRAIN_VREF_STEP 2
  #define WRDQ_TRAIN_OVRSAMPLE_CNT  16
#else
  #define WRDQ_TRAIN_DELAY_MIN_UI 2
  #define WRDQ_TRAIN_DELAY_MAX_UI 7
  #define WRDQ_TRAIN_DELAY_STEP 3
  #define WRDQ_TRAIN_VREF_MIN  32  //FLC Spec: Min= 18 Max=47
  #define WRDQ_TRAIN_VREF_MAX  32 
  #define WRDQ_TRAIN_VREF_STEP 3
  #define WRDQ_TRAIN_OVRSAMPLE_CNT  1
#endif
#define WRDQ_VRET_LEN  ( ( WRDQ_TRAIN_VREF_MAX  - WRDQ_TRAIN_VREF_MIN  ) / WRDQ_TRAIN_VREF_STEP  + 1 ) 
#define WRDQ_HORI_LEN  ( ( ( WRDQ_TRAIN_DELAY_MAX_UI - WRDQ_TRAIN_DELAY_MIN_UI ) * ( SDL_MAX + 1 ) ) / WRDQ_TRAIN_DELAY_STEP + 1 ) 
#define WRDQ_MAX_LEN   ( WRDQ_VRET_LEN*WRDQ_HORI_LEN + 1)
#define WRDQ_TRAIN_PASS_REGION_THLD 6
#define WRDQ_TRAIN_PASS_REGION_DIFF 3
#define WRDQ_DIFF_TH 60  // Expressed as %UI. For e.g. 60 is 60% UI
#define DQS2DQ_TRAIN_PAT_POS 0x1abcd
#define DQS2DQ_TRAIN_PAT_NEG 0x1FFFF

//------------------------------------
//Serializer timing training parameter
//------------------------------------
#define t_SER_RST_DELAY 7       // Reset delay in ns
#define t_SER_RST_DELAY_INCR 3  // Reset delay increment in ns

//########## Write pipeline Signal Stretch Values ##############//
//2 tCK cycles (4UI) for preamble
#define STRCH_WDQS 4
//OE is asserted one tCK cycle early than DQ
#define STRCH_WDQ_OE `STRCH_WDQS+2
//OE is asserted one tCK cycle early than DQS
#define STRCH_WDQS_OE `STRCH_WDQS+2
//en_early is asserted one tCK cycle before OE. Has to be extended till DQ completes. One UI extra for MCD NUI switching missmatch
#define TDQS2DQ 4 //4UI set for now
#define STRCH_WRITE_EN_EARLY `STRCH_WDQS_OE+2+`TDQS2DQ+1

//########## Read pipeline Signal Stretch Values ##############//
#define STRCH_RDQSEN 0
//2 tCK cycles (4UI) for preamble + DQSEN is asserted one tCK early than RDQSEN 
#define STRCH_RXDQSEN `STRCH_RDQSEN+4+2
//2 tCK cycles (4UI) for preamble + DQEN is asserted one tCK early than RDQSEN 
#define STRCH_RXDQEN `STRCH_RDQSEN+4+2
//RDQSODTEN is asserted with RXDQSEN
#define STRCH_RDQSODTEN `STRCH_RDQSEN+4+2
//RDQODTEN is asserted with RXDQEN
#define STRCH_RDQODTEN `STRCH_RDQSEN+4+2
//RX_EN_EARLY is asserted two tCK early than RDQSEN
#define STRCH_READ_EN_EARLY `STRCH_RDQSEN+4+4

#define SEND 1
#define NOSEND 0

#define VR_DQ   0b1

#define IPM_DBG_LPBK		0
#define IPM_DBG_SDLCROSS    0
#define IPM_DBG_CROSS_EXTRA 0
#define IPM_DBG_CA 			0
#define IPM_DBG_WRLVL 		0
#define IPM_DBG_RDPRE 		0
#define IPM_DBG_RDDQ 		0
#define IPM_DBG_WRDQ 		0
#define IPM_DBG_NUI_CROSS 	0
#define IPM_DBG_FIND_OPT 	0
#define IPM_DBG_SDLCROSS_OPT    0   // cross-sel training optima
#define IPM_DBG_TRANS           0   // Transition detect
#define IPM_DBG_FIND_CROSS_NUI  0   // find_ana_cross_sel
#define IPM_DBG_SERMAR  0
#define IPM_DBG_ARR_RW 0
#define IPM_DBG_WRLAT 0

#define IPM_PRINT_EYE_PERBYTE_RDDQ 0
#define IPM_PRINT_EYE_PERBYTE_WRDQ 0
#define IPM_PRINT_EYE_PERBIT_WRDQ 0

#endif
