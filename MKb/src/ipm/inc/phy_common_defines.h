// Copyright (c) 2020 Blue Cheetah Analog Design, Inc. 
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.

//------------------------------------------------------------------
//GENERAL DEFINES
//------------------------------------------------------------------
#define AFTER_POWER_ON_RESET_ACCESS_DELAY 11 //#500ns
#define INTERMEDIATE_RESET_DELAY 1 //#5ns
#define SMARTDV_VIP_BRINGUP_DELAY 5//#100ns
//------------------------------------------------------------------
//TRAINING DEFINES
//------------------------------------------------------------------
//#define t_INIT0  #2ns   /* Assumed value */
//#define t_INIT1  #200ns //#200us /* Downscaled for faster simulation */
//#define t_INIT3  #200ns //#2ms /* Downscaled for faster simulation */
//#define t_INIT5  #2us
//#define t_ZQCAL  #5us // 1us min value
//#define t_ZQLAT  #30ns // Max(30ns,8tCK)
//#define t_VRCG_ENABLE   #200ns 
//#define MCU_CLOCK      200000000
#define t_INIT0        1   //#2ns   /* Assumed value */
#define t_INIT1        5   //#200ns //#200us /* Downscaled for faster simulation */
#define t_INIT3        5   //#200ns //#2ms /* Downscaled for faster simulation */
#define t_INIT5        50  //#2us
#define t_ZQCAL        125 //#5us // 1us min value
#define t_ZQLAT         1  //#30ns // Max(30ns,8tCK)
#define t_VRCG_ENABLE   5  //#200ns

#define MRW0_ADDR  0
#define MRW1_ADDR  1
#define MRW2_ADDR  2
#define MRW3_ADDR  3
#define MRW4_ADDR  4
#define MRW5_ADDR  5
#define MRW6_ADDR  6
#define MRW7_ADDR  7
#define MRW8_ADDR  8
#define MRW9_ADDR  9
#define MRW10_ADDR 10
#define MRW11_ADDR 11
#define MRW12_ADDR 12
#define MRW13_ADDR 13
#define MRW14_ADDR 14
#define MRW15_ADDR 15
// Add other MRW later as per need
//#define MPC_RD_FIFO         7'b1000001
//#define MPC_RD_DQCAL        7'b1000011
//#define MPC_WR_FIFO         7'b1000111
//#define MPC_START_DQS_OSC   7'b1000111
//#define MPC_STOP_DQS_OSC    7'b1001101
//#define ZQCAL_START         7'b1001111
//#define ZQCAL_LATCH         7'b1010001
//
//#define CA_TRAIN_PAT_EARLY 10'h200
//#define CA_TRAIN_PAT_MID   10'h3FF
//#define CA_TRAIN_PAT_LATE  10'h001

//Wrlvl training parameters. Wrlvl needs to start from 4UI
//inorder to leave time for SDL turnon
#define WRLVL_TRAIN_DELAY_MIN 65
#define WRLVL_TRAIN_DELAY_MAX 90
#define WRLVL_TRAIN_DELAY_STEP 2

//Read preamble training parameter
#define RDPRE_TRAIN_BL 8    // Burst length of rdfifo cmd

#define RDPRE_TRAIN_DELAY_MIN 65
#define RDPRE_TRAIN_DELAY_MAX 100
#define RDPRE_TRAIN_DELAY_STEP 4


#define CA_VREF_MIN  47  // 'h40  Range[1]=1 ,value start 00_0000 
#define CA_VREF_MAX  47 //114 // 'h72  Range[1]=1  value  end 11_0010
#define CA_DELAY_INC_OFFSET 1  //not thre in sv FIXME

#define CA_TRAIN_DELAY_MIN 20      
#define CA_TRAIN_DELAY_MAX 60   // CC_PIPE_DLY + DLL DLY tatal 10 bit variable

#define DQ_VREF_MIN  32  // 'h40  Range[1]=1 ,value start 00_0000
#define DQ_VREF_MAX  32 // 'h72  = Range[1]=1  value  end 11_0010
#define DQ_DELAY_INC_OFFSET 1

#define DQ_WRITE_TRAIN_DELAY_MIN 100      //
#define DQ_WRITE_TRAIN_DELAY_MAX 550   // CC_PIPE_DLY + DLL DLY tatal 10 bit variable

//WDS PIPE n DLL Delay by yu
//#define WRITE_LEVEL_TRAIN_DELAY_MIN 0
//#define WRITE_LEVEL_TRAIN_DELAY_MAX 511
//#define WRITE_LEVEL_TRAIN_DELAY_INC_OFFSET 10
//
////read preamble delay :rdqsen_pipe_dly rdqsen_pipe_dll delay
//#define READ_PREAMBLE_DELAY_MIN 0
//#define READ_PREAMBLE_DELAY_MAX 1024
//#define READ_PREAMBLE_DELAY_INC_OFFSET 10

#define READ_DQ_TRAIN_DELAY_MIN 0
#define READ_DQ_TRAIN_DELAY_MAX 64
#define READ_DQ_TRAIN_DELAY_INC_OFFSET 1

//Clock Sync Algorithm Parameters
 //1/8th of dfi_clk period (45 degree)
#define CLK_SYNC_LOCK_LIMIT 45
 //1/10th of dfi_clk period (36 degree)
#define CLK_SYNC_DELTA_SHIFT 36

//########## Write pipeline Signal Stretch Values ##############//
//2 tCK cycles (4UI) for preamble
#define STRCH_WDQS 4
//OE is asserted one tCK cycle early than DQ
#define STRCH_WDQ_OE STRCH_WDQS+2
//OE is asserted one tCK cycle early than DQS
#define STRCH_WDQS_OE STRCH_WDQS+2
//en_early is asserted one tCK cycle before OE. Has to be extended till DQ completes. One UI extra for MCD NUI switching missmatch
#define TDQS2DQ 4 //4UI set for now
#define STRCH_WRITE_EN_EARLY STRCH_WDQS_OE+2+TDQS2DQ+1


//########## Read pipeline Signal Stretch Values ##############//
#define STRCH_RDQSEN 0
//2 tCK cycles (4UI) for preamble + DQSEN is asserted one tCK early than RDQSEN 
#define STRCH_RXDQSEN STRCH_RDQSEN+4+2
//2 tCK cycles (4UI) for preamble + DQEN is asserted one tCK early than RDQSEN 
#define STRCH_RXDQEN STRCH_RDQSEN+4+2
//RDQSODTEN is asserted with RXDQSEN
#define STRCH_RDQSODTEN STRCH_RDQSEN+4+2
//RDQODTEN is asserted with RXDQEN
#define STRCH_RDQODTEN STRCH_RDQSEN+4+2
//RX_EN_EARLY is asserted two tCK early than RDQSEN. +2 for odten to be sampled
//#define STRCH_READ_EN_EARLY STRCH_RDQSEN+4+4+2 acc to sv
#define STRCH_READ_EN_EARLY STRCH_RDQSEN+4+4



