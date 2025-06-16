// Copyright (c) 2020 Blue Cheetah Analog Design, Inc.
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.


#include <reg_mnemonic.c>
#include <training_sibased_defines.h>
#include <tb_defines.h>
#include <periph_csr_map.h>
#include <phy_csr_common_defines.h>

#define BIT_SET(x,m,y)  ( (x) = ( ((x) & ~(1L<<(m))) | ((y)<<(m)) ) )
#define	BIT_GET(x,m)  (((x)  &  (1L<<(m))) >> (m))
#define BITS_SET(x,m,n,y) ( (x) = ((x) & ~((~(~0L<<((m)-(n)+1)))<<(n))) | ((y)<<(n)) )
#define BITS_GET(x,m,n)  (( (x)  &   (~(~0L<<((m)-(n)+1)))<<(n)) >> (n) )
#define BITS_2SCOMP(x)  ((~x) + 1)

const unsigned int PTRN_EN_CC                 =              0b1;
const unsigned int PTRN_EN_CK                 =             0b10;
const unsigned int PTRN_EN_DQWR_DATA          =         0b111100;
const unsigned int PTRN_EN_DQWR_BYTE0         =         0b000100;
const unsigned int PTRN_EN_DQWR_BYTE1         =         0b001000;
const unsigned int PTRN_EN_DQWR_BYTE2         =         0b010000;
const unsigned int PTRN_EN_DQWR_BYTE3         =         0b100000;
const unsigned int PTRN_EN_DQRD_EN            =     0b1111000000;
const unsigned int PTRN_EN_DQRD_DATA          = 0b11110000000000;
const unsigned int PTRN_EN_DQWR_DQRD_DATA     = 0b11110000111100;

const unsigned int XORESETS_SET = 0;//Active low setting
const unsigned int XORESETS_CLEAR = 1;

const unsigned int PTRNBUF_CK_STOP   = 0b111100;
const unsigned int PTRNBUF_CK_START  = 0b001100;
const unsigned int PTRNBUF_CK_ENABLE = 0b001111;
const unsigned int PTRNBUF_INIT      = 0b000000;

unsigned int CC_XOVR_OLD=0;

unsigned int MRW_DATA[2][33];  // [#ch][#mrw]

unsigned int DRAM_RL[4];
unsigned int DRAM_WL_A[4];
unsigned int DRAM_WL_B[4];
unsigned int DRAM_NWR[4];
unsigned int DRAM_NRTP[4];
unsigned int DRAM_RL_VAL[4];       // [#lat_idx]
unsigned int DRAM_WL_A_VAL[4];     // [#lat_idx]
unsigned int DRAM_WL_B_VAL[4];     // [#lat_idx]
unsigned int DRAM_NWR_VAL[4];      // [#lat_idx]
unsigned int DRAM_NRTP_VAL[4];     // [#lat_idx]

//Freq idx based optimal values
unsigned int CC_VREF_OPT[2][TOTAL_TRN_IDX];                 // [#ch]       [#trn_idx]
unsigned int CC_DELAY_OPT[2][TOTAL_TRN_IDX];               // [#ch]       [#trn_idx]
unsigned int WRLVL_DELAY_OPT[2][4][TOTAL_TRN_IDX];         // [#ch][#byte][#trn_idx]
unsigned int RDEN_DELAY_OPT[2][4][TOTAL_TRN_IDX];          // [#ch][#byte][#trn_idx]
unsigned int RDQS_DELAY_OPT[2][4][TOTAL_TRN_IDX];          // [#ch][#byte][#trn_idx]
unsigned int RDQ_VREF_OPT[2][4][TOTAL_TRN_IDX];            // [#rank][#byte][#trn_idx]
unsigned int WRDQ_DELAY_OPT[2][4][TOTAL_TRN_IDX];          // [#ch][#byte][#trn_idx]
unsigned int WRDQ_VREF_OPT[2][TOTAL_TRN_IDX];              // [#ch][#trn_idx]
unsigned int SDL_WRP_CODE_OPT_CA[2][TOTAL_TRN_IDX];        // [#ch]       [#trn_idx]
unsigned int SDL_WRP_CODE_OPT_DQ[2][PHY_DQS_WIDTH][TOTAL_TRN_IDX]; 	// [#ch][#byte][#trn_idx]
unsigned int SDL_CAP_EN_OPT[TOTAL_TRN_IDX];         				// 			[#trn_idx]
unsigned int PBD_CAP_EN_OPT[TOTAL_TRN_IDX];         				//              [#trn_idx]

// Loopback and cross-sel optima
unsigned int LPBK_DELAY_OPT[2][PHY_DQS_WIDTH][TOTAL_TRN_IDX]={0};	// [#ch][#byte][#trn_idx]
unsigned int LPBK_VREF_OPT[2][PHY_DQS_WIDTH][TOTAL_TRN_IDX]={0};
unsigned int LPBK_CROSS_OPT[2][PHY_DQS_WIDTH][TOTAL_TRN_IDX]={0};
unsigned int LPBK_PASS_SIZE_OPT[2][PHY_DQS_WIDTH][TOTAL_TRN_IDX]={0};
unsigned int LPBK_WDQ_SDL[2][PHY_DQS_WIDTH][TOTAL_TRN_IDX]={0};

// Src data delays for ana xover. This typically does not change
// with trn_idx but it is built that way to be consistent with DSTDLY
unsigned int XOVR_SRCDLY_CC[2][TOTAL_TRN_IDX];       // [#ch][#trn_idx]
unsigned int XOVR_SRCDLY_CK[2][TOTAL_TRN_IDX];       // [#ch][#trn_idx]
unsigned int XOVR_SRCDLY_WDQS[2][4][TOTAL_TRN_IDX];  // [#ch][#byte][#trn_idx]
unsigned int XOVR_SRCDLY_RDEN[2][4][TOTAL_TRN_IDX];  // [#ch][#byte][#trn_idx]

// Dst delays
unsigned int XOVR_DSTDLY_CK[2][TOTAL_TRN_IDX];      // [#ch][#trn_idx]
unsigned int XOVR_DSTDLY_CC[2][TOTAL_TRN_IDX];      // [#ch][#trn_idx]
unsigned int XOVR_DSTDLY_WDQS[2][4][TOTAL_TRN_IDX]; // [#ch][#byte][#trn_idx]
unsigned int XOVR_DSTDLY_RDEN[2][4][TOTAL_TRN_IDX]; // [#ch][#byte][#trn_idx]

// Transition data used for cdc crossing
unsigned int XOVR_TRANS_DQ[2][PHY_DQS_WIDTH][2][SDL_MAX+1]; 	//[#ch][#byte][#cross_sel][#sdlcode]
unsigned int XOVR_TRANS_RDEN[2][PHY_DQS_WIDTH][2][SDL_MAX+1];//[#ch][#byte][#cross_sel][#sdlcode]
// For convinience of pointer reference keep CA same dimensions as DQ and just use byte_idx=0
unsigned int XOVR_TRANS_CA[2][PHY_DQS_WIDTH][2][SDL_MAX+1]; 	//[#ch]       [#cross_sel][#sdlcode]

// For convinience of pointer reference keep CA same dimensions as DQ and just use byte_idx=0
int XOVR_THLD_CA[2][3][PHY_DQS_WIDTH][TOTAL_TRN_IDX];	   				//[#ch][lo,hi,cross]           [#trn_idx]
int XOVR_THLD_WDQ[2][3][PHY_DQS_WIDTH][TOTAL_TRN_IDX];	//[#ch][lo,hi,cross][#byte_idx][#trn_idx]
int XOVR_THLD_RDEN[2][3][PHY_DQS_WIDTH][TOTAL_TRN_IDX];	//[#ch][lo,hi,cross][#byte_idx][#trn_idx]//DFI and DRAM Timing variables for each training scenario

// Src data delays for ana xover. This typically does not change
// with trn_idx but it is built that way to be consistent with DSTDLY
// This is not used anymore

// Dest clk delays for ana xover.
// This varies with freq idx since intrinsic delay of DLL
// changes with freq
// This is no used anymore

//DFI and DRAM Timing variables for each training scenario
// This need not be per channel since both channels will
// be operating with identical paramters
unsigned int T_DRAM_RL[TOTAL_TRN_IDX];     // [#trn_idx]
unsigned int T_DRAM_WL[TOTAL_TRN_IDX];     // [#trn_idx]
unsigned int T_DRAM_NWR[TOTAL_TRN_IDX];    // [#trn_idx]
unsigned int T_DRAM_RL_VAL[TOTAL_TRN_IDX];       // [#trn_idx]
unsigned int T_DRAM_WL_VAL[TOTAL_TRN_IDX];       // [#trn_idx]
unsigned int T_DRAM_NWR_VAL[TOTAL_TRN_IDX];      // [#trn_idx]
unsigned int T_DRAM_NRTP[TOTAL_TRN_IDX];         // [#trn_idx]
unsigned int T_DRAM_NRTP_VAL[TOTAL_TRN_IDX];     // [#trn_idx]
unsigned int T_PHY_WRCSGAP[TOTAL_TRN_IDX];       // [#trn_idx]
unsigned int T_PHY_WRLAT[TOTAL_TRN_IDX];         // [#trn_idx]
unsigned int T_PHY_WRCSLAT[TOTAL_TRN_IDX];       // [#trn_idx]
unsigned int T_RDDATA_EN[TOTAL_TRN_IDX];         // [#trn_idx]
unsigned int T_PHY_RDCSLAT[TOTAL_TRN_IDX];       // [#trn_idx]
unsigned int T_CAS2CAS_DELAY_MIN[TOTAL_TRN_IDX]; // [#trn_idx]

//Retraining global parameters
unsigned int PHY_OSC_COUNT[2][4][TOTAL_TRN_IDX];       // [#byte_idx][#trn_idx]
unsigned int DRAM_OSC_COUNT[2][4][TOTAL_TRN_IDX];      // [#byte_idx][#trn_idx]

unsigned int RDDQ_TRAIN_INV[PHY_DQS_WIDTH];
unsigned int RDDQ_TRAIN_PAT;
unsigned int WRDQ_TRAIN_PAT[WRDQ_TRAIN_MAXBL][PHY_DQS_WIDTH];     // [#burst][#dq]
unsigned int WRDQ_TRAIN_PAT_LPBK[WRDQ_TRAIN_MAXBL][PHY_DQS_WIDTH];// [#burst][#dq]

unsigned int CURR_CH=0;
unsigned int TRN_IDX_GBL=0;
unsigned int INIT_TRN_DONE[TOTAL_TRN_IDX]={0};  // [#trn_idx]

// Create struct for each training idx
typedef struct {
  unsigned int freq_idx;
  unsigned int dram_freq_idx;
  unsigned int dram_freq_idx_val;
  unsigned int pll_mult;
  unsigned int ui;
  unsigned int rden_extra_delay;
} TRN_INPUT;

TRN_INPUT TRN_SCN[TOTAL_TRN_IDX]; // [#trn_idx] how many training scenarios we want to store

void send_mpc_wr_rd_fifo_with_phy(int ch) ;

uint32_t pseudo_seed ;
void vs_srandom(uint32_t seed) {
        pseudo_seed += seed ;
}

void set_gbl_var() {

  // Training scenarios for running tests on
  // Dont change these definitions. If needed you can add new ones
  // For simplicity this table must correspond to USR_TRN_SCN in the test

  //Scn0 = 2133Mbps, intial training
  TRN_SCN[0].freq_idx=0b00000;
  TRN_SCN[0].ui=468;
  TRN_SCN[0].dram_freq_idx= 3;
  TRN_SCN[0].dram_freq_idx_val=2133;
  TRN_SCN[0].pll_mult=16; //[#freq_idx]
  TRN_SCN[0].rden_extra_delay=70;
  SDL_CAP_EN_OPT[0]=1;
  PBD_CAP_EN_OPT[0]=1;
	for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
		SDL_WRP_CODE_OPT_CA[ch][0]=18;
		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
			SDL_WRP_CODE_OPT_DQ[ch][byte_idx][0]=18;
		}
	}
  LPBK_WDQ_SDL[0][0][0]=0;
  LPBK_WDQ_SDL[0][1][0]=0;
  LPBK_WDQ_SDL[0][2][0]=0;
  LPBK_WDQ_SDL[0][3][0]=0;
  //Ch1
  LPBK_WDQ_SDL[1][0][0]=0;
  LPBK_WDQ_SDL[1][1][0]=0;
  LPBK_WDQ_SDL[1][2][0]=0;
  LPBK_WDQ_SDL[1][3][0]=0;

  //Scn1 = 2133Mbps, retrain
  TRN_SCN[1].freq_idx=0b00001;
  TRN_SCN[1].ui=468;
  TRN_SCN[1].dram_freq_idx= 3;
  TRN_SCN[1].dram_freq_idx_val=2133;
  TRN_SCN[1].pll_mult=16; //[#freq_idx]
  TRN_SCN[0].rden_extra_delay=70;
  SDL_CAP_EN_OPT[1]=1;
  PBD_CAP_EN_OPT[1]=1;
	for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
		SDL_WRP_CODE_OPT_CA[ch][1]=18;
		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
			SDL_WRP_CODE_OPT_DQ[ch][byte_idx][1]=18;
		}
	}
  LPBK_WDQ_SDL[0][0][1]=0;
  LPBK_WDQ_SDL[0][1][1]=0;
  LPBK_WDQ_SDL[0][2][1]=0;
  LPBK_WDQ_SDL[0][3][1]=0;
  //Ch1
  LPBK_WDQ_SDL[1][0][1]=0;
  LPBK_WDQ_SDL[1][1][1]=0;
  LPBK_WDQ_SDL[1][2][1]=0;
  LPBK_WDQ_SDL[1][3][1]=0;

  //Scn2 = 1866Mbps, initial training
  TRN_SCN[2].freq_idx=0b00100;
  TRN_SCN[2].ui=536;
  TRN_SCN[2].dram_freq_idx= 3;
  TRN_SCN[2].dram_freq_idx_val=1866;
  TRN_SCN[2].pll_mult=14; //[#freq_idx]
  TRN_SCN[0].rden_extra_delay=70;
  SDL_CAP_EN_OPT[2]=2;
  PBD_CAP_EN_OPT[2]=2;
	for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
		SDL_WRP_CODE_OPT_CA[ch][2]=17;
		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
			SDL_WRP_CODE_OPT_DQ[ch][byte_idx][2]=17;
		}
	}
  LPBK_WDQ_SDL[0][0][2]=0;
  LPBK_WDQ_SDL[0][1][2]=0;
  LPBK_WDQ_SDL[0][2][2]=0;
  LPBK_WDQ_SDL[0][3][2]=0;
  //Ch1
  LPBK_WDQ_SDL[1][0][2]=0;
  LPBK_WDQ_SDL[1][1][2]=0;
  LPBK_WDQ_SDL[1][2][2]=0;
  LPBK_WDQ_SDL[1][3][2]=0;

  //Scn3 = 1866Mbps, fsp switch, no retrain
  TRN_SCN[3].freq_idx=0b00101;
  TRN_SCN[3].ui=536;
  TRN_SCN[3].dram_freq_idx= 3;
  TRN_SCN[3].dram_freq_idx_val=1866;
  TRN_SCN[3].pll_mult=14; //[#freq_idx]
  TRN_SCN[0].rden_extra_delay=70;
  SDL_CAP_EN_OPT[3]=2;
  PBD_CAP_EN_OPT[3]=2;
  for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
		SDL_WRP_CODE_OPT_CA[ch][3]=17;
		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
			SDL_WRP_CODE_OPT_DQ[ch][byte_idx][3]=17;
		}
	}
  LPBK_WDQ_SDL[0][0][3]=0;
  LPBK_WDQ_SDL[0][1][3]=0;
  LPBK_WDQ_SDL[0][2][3]=0;
  LPBK_WDQ_SDL[0][3][3]=0;
  //Ch1
  LPBK_WDQ_SDL[1][0][3]=0;
  LPBK_WDQ_SDL[1][1][3]=0;
  LPBK_WDQ_SDL[1][2][3]=0;
  LPBK_WDQ_SDL[1][3][3]=0;

  //Default values for mrw from FLC spec
 for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
  MRW_DATA[ch][0]=0b00000000; //nRTP,Ltency mode, Referesh mode
  MRW_DATA[ch][1]=0b00000000; //RPST,nWR,RD-PRE,WR-PRE,BL
  MRW_DATA[ch][2]=0b00000000; //WR-LEV,WLS,WL,RL
  MRW_DATA[ch][3]=0b00010000; //PDDS, WR PST
  MRW_DATA[ch][4]=0b00000011; //TUF, Therm offset,Refresh rate
  MRW_DATA[ch][5]=0b00000000; // FLC Manufacturer ID
  MRW_DATA[ch][6]=0b00000000; // Revision ID-1
  MRW_DATA[ch][7]=0b00000000; // Revision ID-2
  MRW_DATA[ch][8]=0b00000000; // IO Width, density, type
  MRW_DATA[ch][9]=0b00000000; // Vendor specific register
  MRW_DATA[ch][10]=0b00010000; //PUDS, ZQ-Reset
  MRW_DATA[ch][11]=0b00000000; //RFU
  MRW_DATA[ch][12]=0b00100000; //VREF-CA
  MRW_DATA[ch][13]=0b00000000; //FSPOP,FSPWR,RRO,VRCG,CBT
  MRW_DATA[ch][14]=0b00100000; //Vref-DQ
  MRW_DATA[ch][15]=0b00000000; //PC0 Invert
  MRW_DATA[ch][16]=0b00000000; //PASR Bank Mask
  MRW_DATA[ch][17]=0b00000000; //PASR Bank Mask
  MRW_DATA[ch][18]=0b00000000; //Oscillator count
  MRW_DATA[ch][19]=0b00000000; //Oscillator count
  MRW_DATA[ch][20]=0b01010101; //PC1 invert
  MRW_DATA[ch][21]=0b00000000; // RFU
  MRW_DATA[ch][22]=0b00000000; // RFU
  MRW_DATA[ch][23]=0b00000001; //DQS interval timer run time setting
  MRW_DATA[ch][24]=0b00000000; // RFU
  MRW_DATA[ch][24]=0b00000000; // RFU
  MRW_DATA[ch][26]=0b00000000; //CMOS ring oscillator enable for VDD2L adj
  MRW_DATA[ch][27]=0b00000000; // RFU
  MRW_DATA[ch][27]=0b00000000; // RFU
  MRW_DATA[ch][29]=0b00000000; // RFU
  MRW_DATA[ch][30]=0b00000000; // RFU
  MRW_DATA[ch][31]=0b00000000; // RFU
  MRW_DATA[ch][32]=0b01011010; // DQ Calibration Pattern A
  }

  //Latency table based on FLC spec table 4.21
  //Index 0 => 10-266Mhz
  //Index 1 => 266-533Mhz
  //Index 2 => 533-800Mhz
  //Index 3 => 800-1066Mhz
  DRAM_RL_VAL[0]=6;
  DRAM_RL_VAL[1]=10;
  DRAM_RL_VAL[2]=14;
  DRAM_RL_VAL[3]=20;

  DRAM_RL[0]=0b000; //6;
  DRAM_RL[1]=0b001; //10;
  DRAM_RL[2]=0b010; //14;
  DRAM_RL[3]=0b011; //20;

  DRAM_WL_A[0]=0b000; //4
  DRAM_WL_A[1]=0b001; //6
  DRAM_WL_A[2]=0b010; //8
  DRAM_WL_A[3]=0b011; //10;

  DRAM_WL_B[0]=0b000; //4;
  DRAM_WL_B[1]=0b001; //8;
  DRAM_WL_B[2]=0b010; //12;
  DRAM_WL_B[3]=0b011; //18;

  DRAM_WL_A_VAL[0]=4;
  DRAM_WL_A_VAL[1]=6;
  DRAM_WL_A_VAL[2]=8;
  DRAM_WL_A_VAL[3]=10;

  DRAM_WL_B_VAL[0]=4;
  DRAM_WL_B_VAL[1]=8;
  DRAM_WL_B_VAL[2]=12;
  DRAM_WL_B_VAL[3]=18;

  DRAM_NWR[0]=0b000; //5
  DRAM_NWR[1]=0b001; //10
  DRAM_NWR[2]=0b010; //15
  DRAM_NWR[3]=0b011; //20

  DRAM_NWR_VAL[0]=5;
  DRAM_NWR_VAL[1]=10;
  DRAM_NWR_VAL[2]=15;
  DRAM_NWR_VAL[3]=20;

  DRAM_NRTP[0]=0b000;  //8;
  DRAM_NRTP[1]=0b000;  //8;
  DRAM_NRTP[2]=0b000;  //8;
  DRAM_NRTP[3]=0b000;  //8;

  DRAM_NRTP_VAL[0]=8;
  DRAM_NRTP_VAL[1]=8;
  DRAM_NRTP_VAL[2]=8;
  DRAM_NRTP_VAL[3]=8;

  //Set up rddq training pattern
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    RDDQ_TRAIN_INV[byte_idx] = 0x19292;
  }

  //Rddq training pattern
  RDDQ_TRAIN_PAT=0xA2;

  //Wrdq training pattern
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    // Training pattern used for WRDQ training
    WRDQ_TRAIN_PAT[0][byte_idx]  =  0x11111;
    WRDQ_TRAIN_PAT[1][byte_idx]  =  0x02222;
    WRDQ_TRAIN_PAT[2][byte_idx]  =  0x13333;
    WRDQ_TRAIN_PAT[3][byte_idx]  =  0x04444;
    WRDQ_TRAIN_PAT[4][byte_idx]  =  0x05555;
    WRDQ_TRAIN_PAT[5][byte_idx]  =  0x16666;
    WRDQ_TRAIN_PAT[6][byte_idx]  =  0x07777;
    WRDQ_TRAIN_PAT[7][byte_idx]  =  0x08888;
    WRDQ_TRAIN_PAT[8][byte_idx]  =  0x09999;
    WRDQ_TRAIN_PAT[9][byte_idx]  =  0x1aaaa;
    WRDQ_TRAIN_PAT[10][byte_idx] =  0x0bbbb;
    WRDQ_TRAIN_PAT[11][byte_idx] =  0x0cccc;
    WRDQ_TRAIN_PAT[12][byte_idx] =  0x0dddd;
    WRDQ_TRAIN_PAT[13][byte_idx] =  0x0eeee;
    WRDQ_TRAIN_PAT[14][byte_idx] =  0x1ffff;
    WRDQ_TRAIN_PAT[15][byte_idx] =  0x1c3c3;

    // Training pattern used for loopback
	  WRDQ_TRAIN_PAT_LPBK[0][byte_idx]  =  0x1ffff;
    WRDQ_TRAIN_PAT_LPBK[1][byte_idx]  =  0x1ffff;
    WRDQ_TRAIN_PAT_LPBK[2][byte_idx]  =  0x00000;
    WRDQ_TRAIN_PAT_LPBK[3][byte_idx]  =  0x00000;
    WRDQ_TRAIN_PAT_LPBK[4][byte_idx]  =  0x1ffff;
    WRDQ_TRAIN_PAT_LPBK[5][byte_idx]  =  0x1ffff;
    WRDQ_TRAIN_PAT_LPBK[6][byte_idx]  =  0x00000;
    WRDQ_TRAIN_PAT_LPBK[7][byte_idx]  =  0x00000;
    WRDQ_TRAIN_PAT_LPBK[8][byte_idx]  =  0x09999;
    WRDQ_TRAIN_PAT_LPBK[9][byte_idx]  =  0x1aaaa;
    WRDQ_TRAIN_PAT_LPBK[10][byte_idx] =  0x0bbbb;
    WRDQ_TRAIN_PAT_LPBK[11][byte_idx] =  0x0cccc;
    WRDQ_TRAIN_PAT_LPBK[12][byte_idx] =  0x0dddd;
    WRDQ_TRAIN_PAT_LPBK[13][byte_idx] =  0x0eeee;
    WRDQ_TRAIN_PAT_LPBK[14][byte_idx] =  0x1ffff;
    WRDQ_TRAIN_PAT_LPBK[15][byte_idx] =  0x1c3c3;
  }

  // Set src delays for ana xover
  for (unsigned int ch_idx=0; ch_idx<=1; ch_idx++) {
    for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
      for (unsigned int trn_idx=0;trn_idx<=1;trn_idx++) {
        XOVR_SRCDLY_CK[ch_idx][trn_idx]=0;
        XOVR_SRCDLY_CK[ch_idx][trn_idx+2]=0;
        XOVR_SRCDLY_CC[ch_idx][trn_idx]=0;
        XOVR_SRCDLY_CC[ch_idx][trn_idx+2]=0;
        XOVR_SRCDLY_WDQS[ch_idx][byte_idx][trn_idx]=0;
        XOVR_SRCDLY_WDQS[ch_idx][byte_idx][trn_idx+2]=0;
        XOVR_SRCDLY_RDEN[ch_idx][byte_idx][trn_idx]=0;
        XOVR_SRCDLY_RDEN[ch_idx][byte_idx][trn_idx+2]=0;
      }
    }
  }
  // Set dest delays
  #if SI_ENV
    // TBD: These values need to be revisited
    XOVR_DSTDLY_CK   [0]   [TRN_IDX_GBL] =  115;
    XOVR_DSTDLY_CK   [1]   [TRN_IDX_GBL] =  100;
    XOVR_DSTDLY_CC   [0]   [TRN_IDX_GBL] =  115;
    XOVR_DSTDLY_CC   [1]   [TRN_IDX_GBL] =  100;
    XOVR_DSTDLY_WDQS [0][0][TRN_IDX_GBL] =  70;
    XOVR_DSTDLY_WDQS [0][1][TRN_IDX_GBL] =  90;
    XOVR_DSTDLY_WDQS [0][2][TRN_IDX_GBL] =  130;
    XOVR_DSTDLY_WDQS [0][3][TRN_IDX_GBL] =  160;
    XOVR_DSTDLY_WDQS [1][0][TRN_IDX_GBL] =  150;
    XOVR_DSTDLY_WDQS [1][1][TRN_IDX_GBL] =  130;
    XOVR_DSTDLY_WDQS [1][2][TRN_IDX_GBL] =  100;
    XOVR_DSTDLY_WDQS [1][3][TRN_IDX_GBL] =  60;
    XOVR_DSTDLY_RDEN [0][0][TRN_IDX_GBL] =  190;
    XOVR_DSTDLY_RDEN [0][1][TRN_IDX_GBL] =  210;
    XOVR_DSTDLY_RDEN [0][2][TRN_IDX_GBL] =  250;
    XOVR_DSTDLY_RDEN [0][3][TRN_IDX_GBL] =  280;
  #else
    XOVR_DSTDLY_CK   [0]   [TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_CK   [1]   [TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_CC   [0]   [TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_CC   [1]   [TRN_IDX_GBL] =  0;   
    XOVR_DSTDLY_WDQS [0][0][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_WDQS [0][1][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_WDQS [0][2][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_WDQS [0][3][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_WDQS [1][0][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_WDQS [1][1][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_WDQS [1][2][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_WDQS [1][3][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_RDEN [0][0][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_RDEN [0][1][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_RDEN [0][2][TRN_IDX_GBL] =  0;
    XOVR_DSTDLY_RDEN [0][3][TRN_IDX_GBL] =  0;
  #endif

} // set_gbl_var

void reset_acsrs() {
    apb_write (PLL_ACSR_ADDR_ADDR      ,   0x5E00);
    apb_write (PLL_ACSR_DATA_IN_ADDR   ,   0x0000);
    apb_write (PLL_ACSR_ADDR_ADDR      ,   0x0000);
}

void ddr_analog_reset_acsrs(unsigned int ch) {
  apb_write_ch (ACSR_ADDR_0_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_0_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_0_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_1_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_1_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_1_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_2_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_2_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_2_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_3_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_3_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_3_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_4_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_4_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_4_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_5_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_5_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_5_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_6_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_6_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_6_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_7_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_7_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_7_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_8_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_8_ADDR,0x0000, ch);

  apb_write_ch (ACSR_ADDR_8_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_9_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_9_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_9_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_10_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_10_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_10_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_11_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_11_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_11_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_12_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_12_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_12_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_13_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_13_ADDR,0x0000, ch);
  apb_write_ch (ACSR_ADDR_13_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_14_ADDR, 0x5e00, ch);
  apb_write_ch (ACSR_WDATA_14_ADDR, 0x0000, ch);
  apb_write_ch (ACSR_ADDR_14_ADDR, 0x0000, ch);
}

void wait_ptrn_done(unsigned int ch) {
  apb_write_field_ch(M_GBL_PTRN_EN, 0b1, ch);
  apb_poll_field_ch(M_GBL_PTRN_EN, 0b0, ch);
  // Add delay so that ptrn_done_ack is de-asserted before starting next
  // operation. Enable for silicon but not for sims.
  #if SI_ENV
    delay(t_PTRN_DONE);
  #endif
}

void pll_config() {
  unsigned int csr_adj_pos_val;
  unsigned int csr_adj_neg_val;
  unsigned int csr_accum_man_val;

  unsigned int dll_locking_preiod;
  unsigned int dll_lock_swing;
  unsigned int dll_accum_delay_step;
  unsigned int dll_accum_ovrd_val;

  // accumulator increment / decrement step size
  csr_adj_pos_val = 500;
  //csr_adj_neg_val = BITS_2SCOMP(csr_adj_pos_val);
  csr_accum_man_val = 0x8EA000;

  dll_accum_ovrd_val = 0xFF00FF;        //Testcase hangs with this value runs unsigned into error
  dll_locking_preiod = 3000;
  dll_lock_swing = 1000000;
  dll_accum_delay_step = 2000;

  delay(1);

  // Example of synchronous writes int unsignedo APB
  // set up to count up and down with size of 500, and override the accum in the mid range
  apb_write_field          ( M_PLL_FREEZE,          1 );
  //apb_write_field          ( M_PLL_ADJ_POS_LO,          BITS_GET(csr_adj_pos_val,15,0));
 // apb_write_field          ( M_PLL_ADJ_POS_HI,          BITS_GET(csr_adj_pos_val,31,16));
 // apb_write_field          ( M_PLL_ADJ_NEG_LO,          BITS_GET(csr_adj_neg_val,15,0));
  //apb_write_field          ( M_PLL_ADJ_NEG_HI,          BITS_GET(csr_adj_neg_val,31,16));
  //apb_write_field          ( M_PLL_ACCUM_MAN_LO,    BITS_GET(csr_accum_man_val,15,0));
 // apb_write_field          ( M_PLL_ACCUM_MAN_HI,    BITS_GET(csr_accum_man_val,31,16));
  apb_write_field          ( M_PLL_ACCUM_OVRD  ,     1  );
  apb_write_field          ( M_PLL_FREEZE,           0  );

  delay(20);

  // reset all acsrs
  reset_acsrs();

  //Setting PLL to operate in by pass mode
  acsr_write_field         ( M_ANA_PLL_SEL_REFCLK_OUTPUT,      1);
  for (unsigned int idx=0; idx<2; idx++) {
    acsr_write_field         ( M_ANA_PLL_OUT_DIV_MODE[idx],      3 );
  }

  // make it accept external fsp
  apb_write_field          ( M_PLL_FREEZE,                  1 );
  apb_write_field          ( M_PLL_CSR_FSP_SEL_EXTERNAL,           1 );
  apb_write_field          ( M_PLL_FREEZE,          0 );

  // setup pll lock detect settings
  apb_write_field          ( M_PLL_FREEZE,                 1 );
  apb_write_field          ( M_PLL_CSR_LOCK_DET_THRESH_LO,         0xFFFF );
  apb_write_field          ( M_PLL_CSR_LOCK_DET_THRESH_HI,         0x0003 );
  apb_write_field          ( M_PLL_LOCK_DET_LOCKING_PERIOD,        1000 );
  apb_write_field          ( M_PLL_FREEZE,                     0 );

  delay(1);

  // setup the DLL csrs
  apb_write_field          ( M_PLL_FREEZE,                     1 );
  // increment
  apb_write_field          ( M_DLL_DELAY_STEP,   (1<<15) + dll_accum_delay_step );
  //apb_write_field          ( M_DLL_CLK_SWING_HI,  BITS_GET(dll_lock_swing, 22, 16) );
  //apb_write_field          ( M_DLL_CLK_SWING_LO,      BITS_GET(dll_lock_swing, 15, 0) );
  apb_write_field          ( M_DLL_CLK_LOCKING_PERIOD ,      dll_locking_preiod );
  apb_write_field          ( M_DFI_CLK_EN,                    1 );
  apb_write_field          ( M_DIV_DFI_DRT,                   1 );
  apb_write_field          ( M_DLL_DAC_OUT_EN,                1 );

  // override the counter value to mid range
 // apb_write_field          ( M_DLL_ACCUM_OVRD_VAL_HI,         BITS_GET(dll_accum_ovrd_val,23,16));
//  apb_write_field          ( M_DLL_ACCUM_OVRD_VAL_LO,         BITS_GET(dll_accum_ovrd_val,15,0));
  apb_write_field          ( M_DLL_ACCUM_OVRD,                 1);
  apb_write_field          ( M_PLL_FREEZE,                    0 );

  delay(100);

  // de-assert reset of dfi_div
  apb_write_field          ( M_DLL_DFI_DIV_RST_N,                   1 );
  apb_write_field          ( M_DLL_DAC_OUT_EN,                      1 );

  delay(10);

  // de-assert reset of precond
  apb_write_field          ( M_DLL_PRECOND_RST_N,                   1 );
  apb_write_field          ( M_DLL_DFI_DIV_RST_N,                   1 );
  apb_write_field          ( M_DLL_DAC_OUT_EN,                      1 );
  delay(10);

  // Removed the pipe resets from here and put them in the main test

}

void set_and_clear_xoresets(unsigned int write_data,unsigned int ch) {

   for (unsigned int idx=0; idx<10; idx++) {
      acsr_write_field_ch(M_ANA_CROSS_RESETN_CA[idx], write_data,ch);
   }

   acsr_write_field_ch(M_ANA_CROSS_RESETN_CS, write_data,ch);
   acsr_write_field_ch(M_ANA_CROSS_RESETN_RSTN, write_data,ch);
   acsr_write_field_ch(M_ANA_CROSS_RESETN_CKC, write_data,ch);
   acsr_write_field_ch(M_ANA_CROSS_RESETN_CKT, write_data,ch);
   acsr_write_field_ch(M_ANA_CROSS_RESETN_CKE, write_data,ch);

   for (unsigned int idx=0; idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1)); idx++) {
      acsr_write_field_ch(M_ANA_CROSS_RESETN_DQ[idx], write_data,ch);
   }

   for (unsigned int idx=0; idx<4; idx++) {
      acsr_write_field_ch(M_ANA_CROSS_RESETN_DMI[idx], write_data,ch);
      acsr_write_field_ch(M_ANA_CROSS_RESETN_DQSC[idx], write_data,ch);
      acsr_write_field_ch(M_ANA_CROSS_RESETN_DQST[idx], write_data,ch);
      acsr_write_field_ch(M_ANA_CROSS_RESETN_DQS[idx],  write_data,ch);
   }

}

void set_miscellaneous_fields_dmi_dq_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      acsr_write_field_ch(M_ANA_SEL_PUNB_DMI[idx],   CSR_DQDM_TX_SEL_PUNB,ch);
   }

   for (unsigned int idx=0; idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1)); idx++) {
      acsr_write_field_ch(M_ANA_SEL_PUNB_DQ[idx],  CSR_DQDM_TX_SEL_PUNB,ch);
   }

}

void set_duty_pn_dmi_dq_regs(unsigned int ch) {

   for (unsigned int idxf=0; idxf<2; idxf++) { // idxf ranges from 0 .. N_FSP-1
     for (unsigned int idx=0; idx<4; idx++) {
       acsr_write_field_ch(M_ANA_DUTYB_P_DMI[idx][idxf], CSR_DQDM_TX_DUTY_PN,ch);
       acsr_write_field_ch(M_ANA_DUTY_N_DMI[idx][idxf], CSR_DQDM_TX_DUTY_PN,ch);
     }

     for (unsigned int idx=0; idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1)); idx++) {
       acsr_write_field_ch(M_ANA_DUTYB_P_DQ[idx][idxf], CSR_DQDM_TX_DUTY_PN,ch);
       acsr_write_field_ch(M_ANA_DUTY_N_DQ[idx][idxf], CSR_DQDM_TX_DUTY_PN,ch);
     }
   }

}

void set_z_code_dmi_dq_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      acsr_write_field_ch(M_ANA_ZCODE_PUW_DMI[idx], CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_X_DMI[idx], CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PI_DMI[idx],CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDW_DMI[idx], CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDR_DMI[idx], CSR_DQDM_TX_ZCODE,ch);
   }

   for (unsigned int idx=0; idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1)); idx++) {
      acsr_write_field_ch(M_ANA_ZCODE_PUW_DQ[idx], CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_X_DQ[idx], CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PI_DQ[idx], CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDW_DQ[idx], CSR_DQDM_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDR_DQ[idx], CSR_DQDM_TX_ZCODE,ch);
   }

}

void set_fine_cross_sel_dmi_dq_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      for (unsigned int fsp=0; fsp<2; fsp++) {
         acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_DMI[idx][fsp], CSR_DQDM_TX_XOVER_FINE_CROSS_SEL,ch);
      }
   }

   for (unsigned int idx=0; idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1)); idx++) {
      for (unsigned int fsp=0; fsp<2; fsp++) {
        acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_DQ[idx][fsp], CSR_DQDM_TX_XOVER_FINE_CROSS_SEL,ch);
      }
   }

}

void set_dq_fine_cross_sel_dq_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      for (unsigned int fsp=0; fsp<2; fsp++) {
         acsr_write_field_ch(M_ANA_DQ_FINE_CROSS_SEL[idx][fsp], 0b1,ch);
      }
   }

}


void set_dq_fe_dac_dmi_dq_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_R[idx], CSR_DQDM_RX_DQ_FE_DAC_MAIN,ch);
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_DMI_R[idx], CSR_DQDM_RX_DQ_FE_DAC_KICK_HB,ch);
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_DMI_R[idx], CSR_DQDM_RX_DQ_FE_DAC_KICK_LB,ch);
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_DMI_R[idx], CSR_DQDM_RX_DQ_FE_DAC_ENB,ch);
      acsr_write_field_ch(M_ANA_DQ_FE_EN_DMI_R[idx],CSR_DQDM_RX_DQ_FE_EN,ch);
   }

   for (unsigned int idx=0; idx<4; idx++) {
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_F[idx], CSR_DQDM_RX_DQ_FE_DAC_MAIN,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_DMI_F[idx], CSR_DQDM_RX_DQ_FE_DAC_KICK_HB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_DMI_F[idx], CSR_DQDM_RX_DQ_FE_DAC_KICK_LB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_DMI_F[idx],CSR_DQDM_RX_DQ_FE_DAC_ENB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_EN_DMI_F[idx], CSR_DQDM_RX_DQ_FE_EN,ch);
   }

   for (unsigned int idx=0; idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1)); idx++) {
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_R[idx],CSR_DQDM_RX_DQ_FE_DAC_MAIN,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_R[idx], CSR_DQDM_RX_DQ_FE_DAC_KICK_HB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_R[idx], CSR_DQDM_RX_DQ_FE_DAC_KICK_LB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_R[idx], CSR_DQDM_RX_DQ_FE_DAC_ENB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_EN_R[idx],CSR_DQDM_RX_DQ_FE_EN,ch);
  }

   for (unsigned int idx=0; idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1)); idx++) {
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_F[idx], CSR_DQDM_RX_DQ_FE_DAC_MAIN,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_F[idx],CSR_DQDM_RX_DQ_FE_DAC_KICK_HB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_F[idx], CSR_DQDM_RX_DQ_FE_DAC_KICK_LB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_F[idx], CSR_DQDM_RX_DQ_FE_DAC_ENB,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_EN_F[idx], CSR_DQDM_RX_DQ_FE_EN,ch);
   }

}

void set_miscellaneous_fields_dqs_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      acsr_write_field_ch(M_ANA_SEL_PUNB_DQSC[idx],CSR_DQS_TX_SEL_PUNB,ch);
      acsr_write_field_ch(M_ANA_SEL_PUNB_DQST[idx], CSR_DQS_TX_SEL_PUNB,ch);

      acsr_write_field_ch(M_ANA_DQ_RESETN[idx], 0b1,ch); //dq_resetn
      acsr_write_field_ch(M_ANA_DQS_RESETN[idx], 0b1,ch);

      acsr_write_field_ch(M_ANA_EDGE_RESETB_DQS[idx], CSR_DQS_RXPBD_EDGE_RESETB,ch);
      acsr_write_field_ch(M_ANA_DQS_RD_EN_SEL[idx], CSR_DQS_RD_EN_SEL,ch);
   }

}

void set_duty_pn_dqs_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
     for (unsigned int idxf=0; idxf<2; idxf++) { //idxf ranges from 0 to N_FSP-1
      acsr_write_field_ch(M_ANA_DUTYB_P_DQSC[idx][idxf],  CSR_DQS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_DUTY_N_DQSC[idx][idxf],  CSR_DQS_TX_DUTY_PN,ch);

      acsr_write_field_ch(M_ANA_DUTYB_P_DQST[idx][idxf],  CSR_DQS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_DUTY_N_DQST[idx][idxf],  CSR_DQS_TX_DUTY_PN,ch);

      acsr_write_field_ch(M_ANA_DUTYB_P_DQS[idx][idxf], CSR_DQS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_DUTY_N_DQS[idx][idxf], CSR_DQS_TX_DUTY_PN,ch);

      // Need to also set duty cycle codes for PBDs in MDL
      // NOTE: Need to check if CSR_DQS_TX_DUTY_PN is the right setting for thse
      // -------
      // Set duty cycle for PBD creating DQS_DRVEN
      acsr_write_field_ch(M_ANA_PBD_DQS_DUTYB_CTRLP[idx][idxf], CSR_DQS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_PBD_DQS_DUTY_CTRLN[idx][idxf], CSR_DQS_TX_DUTY_PN,ch);
      // Set duty cycle for PBD creating DQ_DRVEN
      acsr_write_field_ch(M_ANA_PBD_DQ_DUTYB_CTRLP[idx][idxf], CSR_DQS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_PBD_DQ_DUTY_CTRLN[idx][idxf], CSR_DQS_TX_DUTY_PN,ch);
     }
   }

}

void set_z_code_dqs_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      acsr_write_field_ch(M_ANA_ZCODE_PUW_DQSC[idx],CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_X_DQSC[idx], CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PI_DQSC[idx],CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDW_DQSC[idx],CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDR_DQSC[idx],CSR_DQS_TX_ZCODE,ch);

      acsr_write_field_ch(M_ANA_ZCODE_PUW_DQST[idx],CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_X_DQST[idx], CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PI_DQST[idx], CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDW_DQST[idx],CSR_DQS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDR_DQST[idx],CSR_DQS_TX_ZCODE,ch);
   }

}

void set_fine_cross_sel_dqs_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
     for (unsigned int fsp=1; fsp<2; fsp++) {
       acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_DQSC[idx][fsp], CSR_DQS_TX_XOVER_FINE_CROSS_SEL,ch);
       acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_DQST[idx][fsp], CSR_DQS_TX_XOVER_FINE_CROSS_SEL,ch);
       acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_DQS[idx][fsp],  CSR_DQS_RX_XOVER_FINE_CROSS_SEL,ch);
       acsr_write_field_ch(M_ANA_DQS_FINE_CROSS_SEL[idx][fsp],  CSR_DQS_MDL_XOVER_FINE_CROSS_SEL,ch);
    }
   }

}

void set_non_zero_dmi_dq_regs(unsigned int ch) {

  set_miscellaneous_fields_dmi_dq_regs(ch);
  set_fine_cross_sel_dmi_dq_regs(ch);
  set_dq_fine_cross_sel_dq_regs(ch);
  set_z_code_dmi_dq_regs(ch);
  set_dq_fe_dac_dmi_dq_regs(ch);
  set_duty_pn_dmi_dq_regs(ch);

}

void set_non_zero_dqs_regs(unsigned int ch) {
  set_miscellaneous_fields_dqs_regs(ch);
  // Swapped order of set_duty and set_z to supress occurrence of spurious DQS edges during reset
  set_duty_pn_dqs_regs(ch);
  set_z_code_dqs_regs(ch);
  // set_dcode_idleb_dqsc_dqst_regs(ch);
  set_fine_cross_sel_dqs_regs(ch);
}

void set_retrain_defaults() {
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    apb_write_field(M_RETRAIN_FREEZE[byte_idx],0b1);
    apb_write_field(M_RETRAIN_REF_PER_MULT[byte_idx],CSR_RETRAIN_REF_PER_MULT);
    apb_write_field(M_RETRAIN_CYCLES[byte_idx],CSR_RETRAIN_CYCLES);
    // Min and max oscillator count will be initialized later since
    // they are freq dependent
    apb_write_field(M_RETRAIN_FREEZE[byte_idx],0b0);
  }
}

//---------------------------------------------------------------------------------------------------
// set_sdl_bank_en_ctrl :This method is used to set bank_en depending on delay value
//---------------------------------------------------------------------------------------------------
void set_sdl_bank_en_ctrl(  unsigned int delay, unsigned int *bank_en, unsigned int *ctrl) {

  if     (delay == 0)  { *bank_en = 0b0000; *ctrl = 0b00; }
  else if(delay == 1)  { *bank_en = 0b0000; *ctrl = 0b01; }
  else if(delay == 2)  { *bank_en = 0b0001; *ctrl = 0b00; }
  else if(delay == 3)  { *bank_en = 0b0001; *ctrl = 0b01; }
  else if(delay == 4)  { *bank_en = 0b0010; *ctrl = 0b00; }
  else if(delay == 5)  { *bank_en = 0b0010; *ctrl = 0b01; }
  else if(delay == 6)  { *bank_en = 0b0011; *ctrl = 0b00; }
  else if(delay == 7)  { *bank_en = 0b0011; *ctrl = 0b01; }
  else if(delay == 8)  { *bank_en = 0b0100; *ctrl = 0b00; }
  else if(delay == 9)  { *bank_en = 0b0100; *ctrl = 0b01; }
  else if(delay == 10) { *bank_en = 0b0101; *ctrl = 0b00; }
  else if(delay == 11) { *bank_en = 0b0101; *ctrl = 0b01; }
  else if(delay == 12) { *bank_en = 0b0110; *ctrl = 0b00; }
  else if(delay == 13) { *bank_en = 0b0110; *ctrl = 0b01; }
  else if(delay == 14) { *bank_en = 0b0111; *ctrl = 0b00; }
  else if(delay == 15) { *bank_en = 0b0111; *ctrl = 0b01; }
  else if(delay == 16) { *bank_en = 0b1000; *ctrl = 0b00; }
  else if(delay == 17) { *bank_en = 0b1000; *ctrl = 0b01; }
  else if(delay == 18) { *bank_en = 0b1001; *ctrl = 0b00; }
  else if(delay == 19) { *bank_en = 0b1001; *ctrl = 0b01; }
  else if(delay == 20) { *bank_en = 0b1001; *ctrl = 0b11; }

  #if SI_ENV
    if   (delay == 0)  { *bank_en = 0b0000; *ctrl = 0b00; }
  else if(delay == 1)  { *bank_en = 0b0000; *ctrl = 0b01; }
  else if(delay == 2)  { *bank_en = 0b0001; *ctrl = 0b11; }
  else if(delay == 3)  { *bank_en = 0b0001; *ctrl = 0b01; }
  else if(delay == 4)  { *bank_en = 0b0010; *ctrl = 0b00; }
  else if(delay == 5)  { *bank_en = 0b0010; *ctrl = 0b01; }
  else if(delay == 6)  { *bank_en = 0b0011; *ctrl = 0b11; }
  else if(delay == 7)  { *bank_en = 0b0011; *ctrl = 0b01; }
  else if(delay == 8)  { *bank_en = 0b0100; *ctrl = 0b00; }
  else if(delay == 9)  { *bank_en = 0b0100; *ctrl = 0b01; }
  else if(delay == 10) { *bank_en = 0b0101; *ctrl = 0b11; }
  else if(delay == 11) { *bank_en = 0b0101; *ctrl = 0b01; }
  else if(delay == 12) { *bank_en = 0b0110; *ctrl = 0b00; }
  else if(delay == 13) { *bank_en = 0b0110; *ctrl = 0b01; }
  else if(delay == 14) { *bank_en = 0b0111; *ctrl = 0b11; }
  else if(delay == 15) { *bank_en = 0b0111; *ctrl = 0b01; }
  else if(delay == 16) { *bank_en = 0b1000; *ctrl = 0b00; }
  else if(delay == 17) { *bank_en = 0b1000; *ctrl = 0b01; }
  else if(delay == 18) { *bank_en = 0b1001; *ctrl = 0b11; }
  else if(delay == 19) { *bank_en = 0b1001; *ctrl = 0b01; }
  else if(delay == 20) { *bank_en = 0b1001; *ctrl = 0b00; }
  #endif

}// set_sdl_bank_en_ctrl


//------------------------------------------------------------------------------
// CA delays for boot clk mode
//------------------------------------------------------------------------------
void configure_ca_boot(
		unsigned int cc_delay,
		unsigned int ck_delay,
		unsigned int cc_nui,
		unsigned int ck_nui,
		unsigned int cap_en,
		unsigned int cross_sel,
		unsigned int fsp,
		unsigned int ch) {

	unsigned int cc_bank_en;
	unsigned int cc_ctrl;
	unsigned int ck_bank_en;
	unsigned int ck_ctrl;

	// Gate the xover clocks before adjusting settings
	// CK shud already be stopped at this point. So, no need to add that step.
	acsr_write_field_ch(M_ANA_CA_CLK_EN,0b0,ch);
	acsr_write_field_ch(M_ANA_CK_CLK_EN,0b0,ch);
	acsr_write_field_ch(M_ANA_HV_CLK_EN,0b0,ch);

	// Set CC sdl delay
	set_sdl_bank_en_ctrl(cc_delay,&cc_bank_en,&cc_ctrl);
	acsr_write_field_ch(M_ANA_SDL_CA_CTRL[fsp], cc_ctrl, ch);
	acsr_write_field_ch(M_ANA_SDL_CA_BANK_EN[fsp], cc_bank_en, ch);
	acsr_write_field_ch(M_ANA_SDL_CA_CAP_EN[fsp], cap_en, ch);

	// Set CK sdl delay
	// HV controls CK
	set_sdl_bank_en_ctrl(ck_delay,&ck_bank_en,&ck_ctrl);
	acsr_write_field_ch(M_ANA_SDL_HV_CTRL[fsp], ck_ctrl, ch);
	acsr_write_field_ch(M_ANA_SDL_HV_BANK_EN[fsp], ck_bank_en, ch);
	acsr_write_field_ch(M_ANA_SDL_HV_CAP_EN[fsp], cap_en, ch);

	//Set Cross Sel
	acsr_write_field_ch(M_ANA_CROSS_SEL_CS[fsp],  cross_sel, ch);
	acsr_write_field_ch(M_ANA_CROSS_SEL_CKE[fsp], cross_sel, ch);
	acsr_write_field_ch(M_ANA_CROSS_SEL_RSTN[fsp],cross_sel, ch);
	acsr_write_field_ch(M_ANA_CROSS_SEL_CKC[fsp], cross_sel, ch);
	acsr_write_field_ch(M_ANA_CROSS_SEL_CKT[fsp], cross_sel, ch);

	for (unsigned int idx=0; idx<10; idx++) {
		acsr_write_field_ch(M_ANA_CROSS_SEL_CA[idx][fsp], cross_sel, ch);
	}

	//Set nui=0 for CA,CS and Nui=1 for CK so that relationship is corect.
	apb_write_field_ch(M_CC_PIPE_DLY_CA[fsp], cc_nui, ch);
	apb_write_field_ch(M_CC_PIPE_DLY_CS[fsp], cc_nui, ch);
	apb_write_field_ch(M_CK_PIPE_DLY[fsp], ck_nui,ch);

	// Enable the ccr xover clks after settings update
	delay(t_PIPE_SETTLE);
	acsr_write_field_ch(M_ANA_CA_CLK_EN,0b1,ch);
	acsr_write_field_ch(M_ANA_CK_CLK_EN,0b1,ch);
	acsr_write_field_ch(M_ANA_HV_CLK_EN,0b1,ch);

	// Let the clk run for a little bit
	delay(5);
}

void set_miscellaneous_fields_ccr_regs(unsigned int ch) {

   for (unsigned int idx=0; idx<10; idx++) {
      acsr_write_field_ch(M_ANA_SEL_PUNB_CA[idx],    CSR_CACS_TX_SEL_PUNB,ch);
   }

   acsr_write_field_ch(M_ANA_SEL_PUNB_CS,      CSR_CACS_TX_SEL_PUNB,ch);
   acsr_write_field_ch(M_ANA_SEL_PUNB_CKC,     CSR_CK_TX_SEL_PUNB,ch);
   acsr_write_field_ch(M_ANA_SEL_PUNB_CKT,     CSR_CK_TX_SEL_PUNB,ch);
   acsr_write_field_ch(M_ANA_LPBK_ENB_CA,      CSR_CA_MDL_LPBKENB,ch);

}

void set_duty_pn_ccr_regs(unsigned int ch) {

   for (unsigned int idxf=0; idxf<2; idxf++) { // idxf range 0 .. N_FSP-1
      acsr_write_field_ch(M_ANA_DUTYB_P_CS[idxf], CSR_CACS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_DUTY_N_CS[idxf], CSR_CACS_TX_DUTY_PN,ch);

      for (unsigned int idx=0; idx<10; idx++) {
        acsr_write_field_ch(M_ANA_DUTYB_P_CA[idx][idxf],CSR_CACS_TX_DUTY_PN,ch);
        acsr_write_field_ch(M_ANA_DUTY_N_CA[idx][idxf], CSR_CACS_TX_DUTY_PN,ch);
      }

      acsr_write_field_ch(M_ANA_DUTYB_P_CKC[idxf], CSR_CK_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_DUTY_N_CKC[idxf], CSR_CK_TX_DUTY_PN,ch);

      acsr_write_field_ch(M_ANA_DUTYB_P_CKT[idxf], CSR_CK_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_DUTY_N_CKT[idxf], CSR_CK_TX_DUTY_PN,ch);

      // Need to set duty cycle for all PBDs, including HVs
      // Check if CSR_CACS_TX_DUTY_PN is appropriate value for all of these
      // -----
      // Set duty cycle for RSTN
      acsr_write_field_ch(M_ANA_TX_PBD_DUTYB_CTRLP_RSTN[idxf], CSR_CACS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_TX_PBD_DUTY_CTRLN_RSTN[idxf], CSR_CACS_TX_DUTY_PN,ch);
      // Set duty cycle for CKE
      acsr_write_field_ch(M_ANA_TX_PBD_DUTYB_CTRLP_CKE[idxf], CSR_CACS_TX_DUTY_PN,ch);
      acsr_write_field_ch(M_ANA_TX_PBD_DUTY_CTRLN_CKE[idxf], CSR_CACS_TX_DUTY_PN,ch);
   }

}

void set_z_code_fsp0_fsp1_ccr_regs(unsigned int ch) {
   acsr_write_field_ch(M_ANA_ZCODE_PUW_CKC, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_X_CKC, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PI_CKC, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PDW_CKC, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PDR_CKC, CSR_CK_TX_ZCODE,ch);

   acsr_write_field_ch(M_ANA_ZCODE_PUW_CKT, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_X_CKT, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PI_CKT, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PDW_CKT, CSR_CK_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PDR_CKT, CSR_CK_TX_ZCODE,ch);

   acsr_write_field_ch(M_ANA_ZCODE_PUW_CS, CSR_CACS_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_X_CS, CSR_CACS_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PI_CS, CSR_CACS_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PDW_CS, CSR_CACS_TX_ZCODE,ch);
   acsr_write_field_ch(M_ANA_ZCODE_PDR_CS, CSR_CACS_TX_ZCODE,ch);

   for (unsigned int idx=0; idx<10; idx++) {
      acsr_write_field_ch(M_ANA_ZCODE_PUW_CA[idx], CSR_CACS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_X_CA[idx],   CSR_CACS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PI_CA[idx],  CSR_CACS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDW_CA[idx], CSR_CACS_TX_ZCODE,ch);
      acsr_write_field_ch(M_ANA_ZCODE_PDR_CA[idx], CSR_CACS_TX_ZCODE,ch);
   }

}

void set_fine_cross_sel_fsp0_fsp1_ccr_regs(unsigned int ch) {
   for (unsigned int idx=0; idx<10; idx++) {
      for (unsigned int fsp=0; fsp<2; fsp++) {
         acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_CA[idx][fsp], CSR_CACS_TX_XOVER_FINE_CROSS_SEL,ch);
      }
   }

   for (unsigned int fsp=0; fsp<2; fsp++) {
      acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_CS[fsp],   CSR_CACS_TX_XOVER_FINE_CROSS_SEL,ch);
      acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_RSTN[fsp], CSR_HV_TX_XOVER_FINE_CROSS_SEL,ch);
      acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_CKC[fsp],  CSR_CK_TX_XOVER_FINE_CROSS_SEL,ch);
      acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_CKT[fsp],  CSR_CK_TX_XOVER_FINE_CROSS_SEL,ch);
      acsr_write_field_ch(M_ANA_FINE_CROSS_SEL_CKE[fsp],  CSR_CK_TX_XOVER_FINE_CROSS_SEL,ch);
  }

}

void set_drven_clken_ccr_regs(unsigned int ch) {
   for (unsigned int idx=0; idx<10; idx++) {
      acsr_write_field_ch(M_ANA_DRVEN_CA[idx], CSR_CACS_TX_DRVEN_ON,ch);
   }

   acsr_write_field_ch(M_ANA_DRVEN_CKC, CSR_CK_TX_DRVEN_ON,ch);
   acsr_write_field_ch(M_ANA_DRVEN_CKT, CSR_CK_TX_DRVEN_ON,ch);
   acsr_write_field_ch(M_ANA_DRVEN_CS, CSR_CACS_TX_DRVEN_ON,ch);
   acsr_write_field_ch(M_ANA_CA_CLK_EN, CSR_CACS_TX_DRVEN_ON,ch);
   acsr_write_field_ch(M_ANA_CK_CLK_EN, CSR_CK_TX_DRVEN_ON,ch);
   acsr_write_field_ch(M_ANA_HV_CLK_EN,CSR_HV_TX_DRVEN_ON,ch);
}

void set_non_zero_ccr_regs(unsigned int ch) {
  set_miscellaneous_fields_ccr_regs(ch);
  set_duty_pn_ccr_regs(ch);
  set_z_code_fsp0_fsp1_ccr_regs(ch);
  set_fine_cross_sel_fsp0_fsp1_ccr_regs(ch);
  set_drven_clken_ccr_regs(ch);
}

//------------------------------------------------------------------------------
// set_tx_odt_vref_defaults
//------------------------------------------------------------------------------
void set_tx_odt_vref_defaults(unsigned int ch) {

  // Set TX zcodes
  // CA Zcode
  for (unsigned int bit_idx=0;bit_idx<=9; bit_idx++) {
    acsr_write_field_ch(M_ANA_ZCODE_PUW_CA[bit_idx],ZCODE_PU,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PDW_CA[bit_idx],ZCODE_PD,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PI_CA[bit_idx], 0,ch);
    acsr_write_field_ch(M_ANA_SEL_PUNB_CA[bit_idx],0b0,ch); // Nmos driver for low voltage operation
    //acsr_write_field_ch(M_ANA_SEL_PUNB_CA[bit_idx],0b1,ch); // Pmos driver for high voltage operation
  }

  //CS Zcode
  acsr_write_field_ch(M_ANA_ZCODE_PUW_CS,ZCODE_PU,ch);
  acsr_write_field_ch(M_ANA_ZCODE_PDW_CS,ZCODE_PD,ch);
  acsr_write_field_ch(M_ANA_ZCODE_PI_CS, 0,ch);
  acsr_write_field_ch(M_ANA_SEL_PUNB_CS,0b0,ch); // Nmos driver for low voltage operation
  //acsr_write_field_ch(M_ANA_SEL_PUNB_CS,0b1,ch); // Pmos driver for high voltage operation

  //CKC,CKT Zcode
  acsr_write_field_ch(M_ANA_ZCODE_PUW_CKT,ZCODE_PU,ch);
  acsr_write_field_ch(M_ANA_ZCODE_PDW_CKT,ZCODE_PD,ch);
  acsr_write_field_ch(M_ANA_ZCODE_PI_CKT, 0,ch);
  acsr_write_field_ch(M_ANA_SEL_PUNB_CKT,0b0,ch); // Nmos driver for low voltage operation
  //acsr_write_field_ch(M_ANA_SEL_PUNB_CKT,0b1,ch); // Pmos driver for high voltage operation

  acsr_write_field_ch(M_ANA_ZCODE_PUW_CKC,ZCODE_PU,ch);
  acsr_write_field_ch(M_ANA_ZCODE_PDW_CKC,ZCODE_PD,ch);
  acsr_write_field_ch(M_ANA_ZCODE_PI_CKC, 0,ch);
  acsr_write_field_ch(M_ANA_SEL_PUNB_CKC,0b0,ch); // Nmos driver for low voltage operation
  //acsr_write_field_ch(M_ANA_SEL_PUNB_CKC,0b1,ch); // Pmos driver for high voltage operation

  //DQ Zcode
  for (unsigned int bit_idx=0;bit_idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1));bit_idx++) {
    acsr_write_field_ch(M_ANA_ZCODE_PUW_DQ[bit_idx],ZCODE_PU,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PDW_DQ[bit_idx],ZCODE_PD,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PI_DQ[bit_idx], 0,ch);
    acsr_write_field_ch(M_ANA_SEL_PUNB_DQ[bit_idx],0b0,ch); // Nmos driver for low voltage operation
    //acsr_write_field_ch(M_ANA_SEL_PUNB_DQ[bit_idx],0b1,ch); // Pmos driver for high voltage operation
  }

  // DQSC DQST DMI Zcode
  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
    acsr_write_field_ch(M_ANA_ZCODE_PUW_DQST[byte_idx],ZCODE_PU,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PDW_DQST[byte_idx],ZCODE_PD,ch);
	// Siva try
    //acsr_write_field_ch(M_ANA_ZCODE_PI_DQST[byte_idx], 0,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PI_DQST[byte_idx], 1,ch);
    acsr_write_field_ch(M_ANA_SEL_PUNB_DQST[byte_idx],0b0,ch); // Nmos driver for low voltage operation
    //acsr_write_field_ch(M_ANA_SEL_PUNB_DQST[byte_idx],0b1,ch); // Pmos driver for high voltage operation

    acsr_write_field_ch(M_ANA_ZCODE_PUW_DQSC[byte_idx],ZCODE_PU,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PDW_DQSC[byte_idx],ZCODE_PD,ch);
    // Siva try
	//acsr_write_field_ch(M_ANA_ZCODE_PI_DQSC[byte_idx], 0,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PI_DQSC[byte_idx], 1,ch);
    acsr_write_field_ch(M_ANA_SEL_PUNB_DQSC[byte_idx],0b0,ch); // Nmos driver for low voltage operation
    //acsr_write_field_ch(M_ANA_SEL_PUNB_DQSC[byte_idx],0b1,ch); // Pmos driver for high voltage operation

    acsr_write_field_ch(M_ANA_ZCODE_PUW_DMI[byte_idx],ZCODE_PU,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PDW_DMI[byte_idx],ZCODE_PD,ch);
    //acsr_write_field_ch(M_ANA_ZCODE_PI_DMI[byte_idx], ZCODE_PU,ch);
    acsr_write_field_ch(M_ANA_ZCODE_PI_DMI[byte_idx], 0,ch);
    acsr_write_field_ch(M_ANA_SEL_PUNB_DMI[byte_idx],0b0,ch); // Nmos driver for low voltage operation
    //acsr_write_field_ch(M_ANA_SEL_PUNB_DMI[byte_idx],0b1,ch); // Pmos driver for high voltage operation
  }

  // Rx default settings. Unterminated. Choose vref=vddq/2
  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_F[byte_idx],VREF_VDDQBY2,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_R[byte_idx],VREF_VDDQBY2,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_EN_DMI_F[byte_idx],0b1,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_EN_DMI_R[byte_idx],0b1,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_DMI_F[byte_idx],0b0,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_DMI_R[byte_idx],0b0,ch);
  }

  for (unsigned int bit_idx=0;bit_idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1));bit_idx++) {
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_F[bit_idx],VREF_VDDQBY2,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_R[bit_idx],VREF_VDDQBY2,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_EN_F[bit_idx],0b1,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_EN_R[bit_idx],0b1,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_F[bit_idx],VREF_VDDQBY2,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_ENB_R[bit_idx],VREF_VDDQBY2,ch);
  }

} // set_tx_odt_vref_defaults

void set_dqs_invert(unsigned int write_dqs_invert,unsigned int ch) {

   for (unsigned int idx=0; idx<4; idx++) {
      acsr_write_field_ch(M_ANA_INV_SEL_DQS[idx], write_dqs_invert,ch);
   }

}

//------------------------------------------------------------------------------------
// PHY Initial settings
//------------------------------------------------------------------------------------
void phy_init() {

  // Clear the scratchpad
  clear_scratchpad();

  // Init has to be done for both channels since there are
  // parts of the firmware that apply to both channenls.
  for(unsigned int ch=GLB_CH_MIN;ch<GLB_CH_MAX+1;ch++) {
    if (INIT_TRN_DONE[ch]==0) {

      // Initialize oscillator counts
      for (unsigned int trn_idx=0; trn_idx<TOTAL_TRN_IDX;trn_idx++) {
        for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH; byte_idx++) {
          PHY_OSC_COUNT[ch][byte_idx][trn_idx]=0;
          DRAM_OSC_COUNT[ch][byte_idx][trn_idx]=0;
        }
      }
      print_info("IPM:INIT: Setting up onetime settings Ch%d E:\n",ch);

      //PLL one time settings
      print_dbg("IPM:INIT: PLL onetime settings ch%d E:\n",ch);
      pll_config() ;

      //reset all phy acsrs
      print_dbg("IPM:INIT: Reset all acsrs ch%d E:\n",ch);
      ddr_analog_reset_acsrs(ch);

      //Set xoresets
      print_dbg("IPM:INIT: Assert all xoresets ch%d E:\n",ch);
      set_and_clear_xoresets(XORESETS_SET,ch);

      //Clear xoresets
      print_dbg("IPM:INIT: De-assert all xoresets ch%d E:\n",ch);
      set_and_clear_xoresets(XORESETS_CLEAR,ch);

      // Set non-zero acsr DQ/DM registers
      print_dbg("IPM:INIT: Program DQ/DM non-zero csr's ch%d E:\n",ch);
      set_non_zero_dmi_dq_regs(ch);

      // Set non-zero acsr DQS registers
      print_dbg("IPM:INIT: Program DQS non-zero csr's ch%d E:\n",ch);
      set_non_zero_dqs_regs(ch);

      // Set defaults for retrain block
      print_dbg("IPM:INIT: Set re-training blk defaults ch%d E:\n",ch);
      set_retrain_defaults();

      //Configure CA delays for boot clock for FSP0
      print_dbg("IPM:INIT: Configure CA delays for boot clk ch%d E:\n",ch);
      configure_ca_boot(BOOT_CC_SDL_DELAY,BOOT_CK_SDL_DELAY,BOOT_CC_NUI,BOOT_CK_NUI,BOOT_CAP_EN,BOOT_CROSS_SEL,0,ch);

      // Set non-zero acsr in CCR block
      print_dbg("IPM:INIT: Program CCR  non-zero csr's ch%d E:\n",ch);
      set_non_zero_ccr_regs(ch);

      // set tx, odt and vref defaults
      print_dbg("IPM:INIT: Set Tx/ODT/Vref defaults ch%d E:\n",ch);
      set_tx_odt_vref_defaults(ch);

      if(RDQS_DLL == UI_0P5) {
          print_dbg("IPM:INIT: Set DLL to UI_0P5 Ch%d E:\n",ch);
          set_dqs_invert(0b0,ch);
      } else if(RDQS_DLL == UI_1P5) {
          print_dbg("IPM:INIT: Set DLL to UI_1P5 Ch%d E:\n",ch);
          set_dqs_invert(0b1,ch);
      } else {
        print_err("IPM:DQ_LPBK: ERROR! Invalid RDQS DLL setting %d\n",RDQS_DLL);
      }

      //FIX for TCCDmin+4 testcase since rx_en from RX ckt is going low and then
      //high hence actual data in fifo is overwritten by 0
      print_dbg("IPM:INIT: Set DQ Rx ON Ch%d E:\n",ch);
      for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
        apb_write_field_ch(M_OVR_RXDQEN[byte_idx], 0b11,ch);
      }
    }//init_done
  }// foreach ch

  // Release pipe resets. These registers are from channel-0 only
  print_info("IPM:INIT: De-assert pipe resets\n");
  apb_write_field(M_PIPE_RSTN, 0b1);	//sync_pipe_reset
  delay(INTERMEDIATE_RESET_DELAY);
  apb_write_field(M_SYNC_PIPE_RSTN, 0b1);	//pipe_rstn
  delay(t_PIPE_RSTN);

  // Set global variables that are required for training
  set_gbl_var();

}

void do_read_dll_accum_rst() {
  // DV for dll accumulator fix
  unsigned int accum_lo, accum_hi;

  accum_lo = apb_read_field(M_DLL_ACCUM_OBS_LO);
  accum_hi = apb_read_field(M_DLL_ACCUM_OBS_HI);

  if ((accum_hi == 0xFF) || (accum_lo ==0xFFFF)) {
    print_info("IPM:INIT: DLL Accum-hi 0x%0x Accum-lo 0x%0x E:",accum_hi,accum_lo);
  } else {
    print_err("IPM:INIT: ERROR! Incorrect accumulator value at reset. DLL Accum-hi 0x%0x Accum-lo 0x%0x E:",accum_hi,accum_lo);
  }
}

void stuff_ckhv_patbuf_new(unsigned int cke, unsigned int resetn, unsigned int ckdis, unsigned int send, unsigned int ch) {

  // Setup the buffer
  apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],cke,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],resetn,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],ckdis,ch);

  //delays can be taken care outside
  apb_write_field_ch(M_CKHV_PTRNBUF_DELAY[0],0x0,ch);

  // start and stop pointer
  apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 0x00,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);

  if (send==1) {
    apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
    wait_ptrn_done (ch);
  }
}

void shut_down_chnl(unsigned int ch) {
  // Set CKE low
  stuff_ckhv_patbuf_new(0b00,0b11,0b00,SEND,ch); // cke,resetn,ckdis,ch
  delay(t_CKELCK);

  // Stop the clk
  stuff_ckhv_patbuf_new(0b00,0b11,0b11,SEND,ch);
  delay(t_CKSTOP);

  //Disable the clken
  acsr_write_field_ch(M_ANA_CA_CLK_EN, 0b0,ch);
  acsr_write_field_ch(M_ANA_CK_CLK_EN, 0b0,ch);
  acsr_write_field_ch(M_ANA_HV_CLK_EN, 0b0,ch);
  delay(t_PIPE_SETTLE);
}

void stuff_ckhv_patbuf(unsigned int ckhv, unsigned int delay, unsigned int ch) {
  apb_write_ch(CKHV_PTRNBUF_CKE_0_ADDR, ckhv, ch);
  apb_write_ch(CKHV_PTRNBUF_DELAY_0_ADDR, delay, ch);
  apb_write_ch(CKHV_PTRNBUF_START_PTR_ADDR,0x0000,ch);
  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
  wait_ptrn_done(ch);
}

//------------------------------------------------------------------------------
// stuff_cc_patbuf: Insert a ca,cs pattern into one row of the cc pattern  buffer
//------------------------------------------------------------------------------
void stuff_cc_patbuf(unsigned int ca_neg_data, unsigned int ca_pos_data, unsigned int cs_neg_data, unsigned int cs_pos_data, unsigned int row_idx, unsigned int ch) {
  for(unsigned int idx=0;idx<10;idx++ ) {
    apb_write_field_ch(M_CC_PTRNBUF_CA[row_idx][idx],(BITS_GET(ca_neg_data,idx,idx)<<1)|BITS_GET(ca_pos_data,idx,idx),ch);
  }
  apb_write_field_ch(M_CC_PTRNBUF_CS[row_idx],(cs_neg_data<<1)|cs_pos_data,ch);
}

void send_mpc_through_ptrn_buf(unsigned int opc, unsigned int send, unsigned int ch) {
   unsigned int ca_pos = BIT_GET(opc,6) << 5;
   unsigned int ca_neg = BITS_GET(opc,5,0);

  stuff_cc_patbuf(ca_neg, ca_pos, 0, 1, 0, ch);
  apb_write_ch(CC_PTRNBUF_DELAY_0_ADDR,0x0,ch);
  stuff_cc_patbuf(0, 0, 0, 0, 1, ch);
  apb_write_ch(CC_PTRNBUF_DELAY_1_ADDR,t_MPC,ch);

  apb_write_ch(CC_PTRNBUF_START_PTR_ADDR,0x0100,ch);

  if (send==0b1) {
    apb_write_ch(CC_PTRN_EN_ADDR, PTRN_EN_CC,ch);
    wait_ptrn_done(ch);
  }
}


void send_mrw_through_ptrn_buf(unsigned int mrw_idx, unsigned int ch) {
  unsigned int opc;
  unsigned int addr;
  unsigned int ca_pos;
  unsigned int ca_neg ;

  opc=MRW_DATA[ch][mrw_idx];
  addr=mrw_idx;

  ca_pos = (BITS_GET(addr,5,0) << 4) | 0b0110;
  ca_neg = (opc << 2) | BITS_GET(addr,7,6);

  stuff_cc_patbuf(ca_neg, ca_pos, 0, 1, 0, ch);
  apb_write_ch(CC_PTRNBUF_DELAY_0_ADDR,0, ch);
  stuff_cc_patbuf(0, 0, 0, 0, 1, ch);
  apb_write_ch(CC_PTRNBUF_DELAY_1_ADDR, t_MRW, ch); 

  apb_write_ch(CC_PTRN_EN_ADDR, PTRN_EN_CC, ch);
  apb_write_ch(CC_PTRNBUF_START_PTR_ADDR, 0x0100, ch);
  wait_ptrn_done(ch);

  print_dbg("IPM:MRW-%d Opcode %x\n",addr,opc);

}

//------------------------------------------------------------------------------
// dram_init
//------------------------------------------------------------------------------
void dram_init(unsigned int ch_min, unsigned int ch_max) {

  //Since IPM memory internal reset is an OR of each channel resets
  //it is necessary to do atleast the reset step for both channels

  // t_INIT1 (200us) delay
  delay(t_INIT1);

  //RESET_n drive to 1 for both channels
  for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
    stuff_ckhv_patbuf(PTRNBUF_CK_START, 0, ch);
  }
  // t_INIT3 (2ms) delay
  delay(t_INIT3);

  // Set CKE=high
  //start pattern with default start and end pointer to drive RESET_n + CKE
  for (unsigned int ch=ch_min;ch<=ch_max;ch++) {
    stuff_ckhv_patbuf(PTRNBUF_CK_ENABLE, 0, ch);
  }
  // t_INIT5 delay ; Wait 2us
  delay(t_INIT5);

  for (unsigned int ch=ch_min;ch<=ch_max;ch++) {
    apb_write_ch(CC_RANK_SEL_PIPE_DLY_R0F0_ADDR, 0x2, ch);
    apb_write_ch(CC_RANK_SEL_PIPE_DLY_R0F1_ADDR, 0x2, ch);

    // MPC ZQ CAL START followed by DES
    send_mpc_through_ptrn_buf(ZQCAL_START,SEND,ch);
  }
  delay(t_ZQCAL);

  // MPC ZQ CAL LATCH followed by DES
  for (unsigned int ch=ch_min;ch<=ch_max;ch++) {
    send_mpc_through_ptrn_buf(ZQCAL_LATCH,SEND,ch);
  }
  delay(t_ZQLAT);

  // MRW_DATA[ch][13] = (MR13_FSP_OP << 7) |
  //                (MR13_FSP_WR << 6) |
  //                (MR13_DMD    << 5) |
  //                (MR13_RRO    << 4) |
  //                (MR13_VRCG   << 3) |
  //                (MR13_VRO    << 2) |
  //                (MR13_RPT    << 1) |
  //                (MR13_CBT    << 0) ;
  // DRAM requires VRCG enable: MR13 [OP3]=1 prior to FSP change.
  for (unsigned int ch=ch_min;ch<=ch_max;ch++) {
    BIT_SET(MRW_DATA[ch][13],3,0b1);
    send_mrw_through_ptrn_buf(13,ch);
  }
  delay(t_VRCG_ENABLE);
}

void send_sre_through_ptrn_buf(unsigned int ch) {

  //-------------------------------------------------------
  // CA Pattern Buffer Data
  //-------------------------------------------------------
  // Row-0 SRE, Row-1 NOP
  apb_write_ch(CC_PTRNBUF_CA0_0_ADDR,0b0000001111000000,ch);
  apb_write_ch(CC_PTRNBUF_CA8_0_ADDR,0b0000,ch);

  apb_write_ch(CC_PTRNBUF_CA0_1_ADDR,0x00,ch);
  apb_write_ch(CC_PTRNBUF_CA8_1_ADDR,0x00,ch);

  //-------------------------------------------------------
  // CA Pattern Buffer Delay
  //-------------------------------------------------------
  apb_write_ch(CC_PTRNBUF_DELAY_0_ADDR, 0x0,ch);
  apb_write_ch(CC_PTRNBUF_DELAY_1_ADDR, 0xA,ch); // Insert a small  delay after SRE. Strictly not required

  //-------------------------------------------------------
  // Start and stop pointer
  //-------------------------------------------------------
  apb_write_field_ch(M_CC_PTRNBUF_START_PTR, 0x00,ch);
  apb_write_field_ch(M_CC_PTRNBUF_STOP_PTR, 	0x01,ch);

  //-------------------------------------------------------
  // Flush the pattern buffer
  //-------------------------------------------------------
  apb_write_ch(CC_PTRN_EN_ADDR, PTRN_EN_CC,ch);
  wait_ptrn_done(ch);

} // send_sre_through_ptrn_buf

void config_dfi_dram_timing(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

  unsigned int lat_idx;
  unsigned int rd_dbi=0;
  unsigned int bl=8;

  // First get the latency for the given index
  lat_idx=TRN_SCN[TRN_IDX_GBL].dram_freq_idx;

  // TBD: Resolve diff between SI and sim environment
  #if SI_ENV
  T_PHY_WRLAT[TRN_IDX_GBL]=DRAM_WL_A_VAL[lat_idx]-1;
  #else
  T_PHY_WRLAT[TRN_IDX_GBL]=DRAM_WL_A_VAL[lat_idx]-2;
  #endif
  T_DRAM_WL_VAL[TRN_IDX_GBL]=DRAM_WL_A_VAL[lat_idx];
  T_DRAM_WL[TRN_IDX_GBL]=DRAM_WL_A[lat_idx];

  // Read timing Parameters
  T_RDDATA_EN[TRN_IDX_GBL]=DRAM_RL_VAL[lat_idx]-1;   // For low freq
  T_DRAM_RL_VAL[TRN_IDX_GBL]=DRAM_RL_VAL[lat_idx];
  T_DRAM_RL[TRN_IDX_GBL]=DRAM_RL[lat_idx];

  T_DRAM_NWR[TRN_IDX_GBL]=DRAM_NWR[lat_idx];
  T_DRAM_NWR_VAL[TRN_IDX_GBL]=DRAM_NWR_VAL[lat_idx];

  T_DRAM_NRTP[TRN_IDX_GBL]=DRAM_NRTP[lat_idx];
  T_DRAM_NRTP_VAL[TRN_IDX_GBL]=DRAM_NRTP_VAL[lat_idx];

  print_info("IPM:TIM: Data rate: %d  E:\n",TRN_SCN[TRN_IDX_GBL].dram_freq_idx_val);
  print_info("IPM:TIM: DBI_EN %d,  BL %d  E:\n",rd_dbi,bl);
  print_info("IPM:TIM: Freq Index: %d ,Latency Table index %d  E:\n",freq_idx,lat_idx);
  print_info("IPM:TIM: RL: %d, WL: %d, NWR: %d  E:\n",T_DRAM_RL_VAL[TRN_IDX_GBL],T_DRAM_WL_VAL[TRN_IDX_GBL],T_DRAM_NWR_VAL[TRN_IDX_GBL]);
  print_info("IPM:TIM: RDPRE: 1, WRPRE: 1  E:\n");
  print_info("IPM:TIM: TPHY_WRLAT %d, TPHY_WRCSLAT %d,  E:\n",T_PHY_WRLAT[TRN_IDX_GBL],T_PHY_WRCSLAT[TRN_IDX_GBL]);
  print_info("IPM:TIM: TRDDATA_EN %d, TPHY_RDCSLAT %d  E:\n",T_RDDATA_EN[TRN_IDX_GBL],T_PHY_RDCSLAT[TRN_IDX_GBL]);
}

//------------------------------------------------------------------------------
// Set cap_en for PBD:
//------------------------------------------------------------------------------
void set_pbd_cap_en(unsigned int fsp, unsigned int ch) {

  // Set PBD cap_en to same as SDL cap_en so that some scaling w.r.t. freq is maintained
  //`uvm_info(get_name(),$sformatf("IPM:SDL:PBD: Setting PBD cap_en to %0d ",PBD_CAP_EN_OPT[TRN_IDX_GBL]),UVM_NONE,ch);
  for (int idx=0;idx<=9;idx++) {
    acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_CA[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL],ch);
  }

  for (int idx=0;idx<=1;idx++) {
    acsr_write_field_ch(M_ANA_PBD_CAP_EN_DQS[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
  }

  acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_CS[fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
  acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_CKE[fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);

  for (int idx=0;idx<PHY_DQS_WIDTH;idx++) {
    acsr_write_field_ch(M_ANA_PBD_DQS_CAP_EN[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_TX_T_TX_PBD_CAP_EN_DQS[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_TX_C_TX_PBD_CAP_EN_DQS[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_RX_RXPBD_CAP_EN_R_DQS[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_RX_RXPBD_CAP_EN_F_DQS[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_RX_TXPBD_CAP_EN_DQS[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_DMI[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_DQ_FALL_RX_PBD_CAP_EN_DMI_F[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_DQ_RISE_RX_PBD_CAP_EN_DMI_R[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
  }

  acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_CKC[fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
  acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_CKT[fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
  acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_RSTN[fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);

  for (int idx=0;idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1));idx++) {
    acsr_write_field_ch(M_ANA_TX_PBD_CAP_EN_DQ[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_DQ_FALL_RX_PBD_CAP_EN_F[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
    acsr_write_field_ch(M_ANA_DQ_RISE_RX_PBD_CAP_EN_R[idx][fsp],PBD_CAP_EN_OPT[TRN_IDX_GBL] ,ch);
  }

} // set_pbd_cap_en

void reset_pll(unsigned int  fsp, unsigned int  freq_ratio, unsigned int  freq_idx) {

  //unsigned int csr_adj_pos_val=PLL_ADJ_POS_VAL;
  //unsigned int csr_adj_neg_val=PLL_ADJ_NEG_VAL;
  unsigned int csr_accum_man_val=PLL_ACCUM_MAN_VAL;

  apb_write_field(M_PLL_RSTN, 		0b0);

  // Set the accum override so that PLL started closer to lock value
  apb_write_field( M_PLL_FREEZE,          		0b1 );
  apb_write_field( M_PLL_ACCUM_MAN_LO,  		BITS_GET(csr_accum_man_val,15,0) );
  apb_write_field( M_PLL_ACCUM_MAN_HI,  		BITS_GET(csr_accum_man_val,31,16) );
  apb_write_field( M_PLL_ACCUM_OVRD  ,   		 0b1  );
  apb_write_field( M_PLL_FREEZE,          		0b0 );

}

void setup_fsps(unsigned int  fsp, unsigned int  freq_ratio, unsigned int  freq_idx) {

  // This function will take 3 division factors and writes 50% duty cycle settings fot fsp0,1,2.
  // out divider setting will be to output the pll out_clk
  unsigned int count_fsp;
  unsigned int div_fsp;
  //logic [5:0] count_fsp2;
  //IPM VCO will run same freq as LPX. We can use PLL output divider to further
  //divide vco freq by 4 to get required output
  div_fsp=TRN_SCN[TRN_IDX_GBL].pll_mult*2;
  count_fsp = (div_fsp >> 1) - 2;

  // Feedback divider
  acsr_write_field(M_ANA_PLL_FB_DIV_HCOUNT[fsp], count_fsp);
  acsr_write_field(M_ANA_PLL_FB_DIV_LCOUNT[fsp], count_fsp);

  // Take PLL out of bypass mode
  acsr_write_field(M_ANA_PLL_SEL_REFCLK_OUTPUT, 0b0);
  // %2 for PLL output
  acsr_write_field(M_ANA_PLL_OUT_DIV_MODE[fsp], 0b010);

  acsr_write_field(M_ANA_PLL_CP_BIAS_RES_CTRL[fsp], 0x1);
  acsr_write_field(M_ANA_PLL_CP_CMP_RES_CTRL[fsp], 0x1);

  // This one enables the PLL and de-assert divider's reset_n
  acsr_write_field(M_ANA_PLL_PLL_EN, 0b1);
  acsr_write_field(M_ANA_PLL_DIV_RST_N, 0b1);

} // setup_fsps

void reset_release_pipe_rstn() {

  // Assert pipe_rstn
  apb_write_field(M_SYNC_PIPE_RSTN, 0b0);//sync_pipe_reset
  apb_write_field(M_PIPE_RSTN, 0b0);//pipe_rstn
  delay(t_PIPE_RSTN);

  // Release pipe resets. These registers are from channel-0 only
  apb_write_field(M_SYNC_PIPE_RSTN, 0b1);//sync_pipe_reset
  delay(INTERMEDIATE_RESET_DELAY);
  apb_write_field(M_PIPE_RSTN, 0b1);//pipe_rstn
  delay(t_PIPE_RSTN);

}

void find_ana_cross_sel_nui( unsigned int delay_code, unsigned int wrp_code, unsigned int src_delay, unsigned int dest_delay, unsigned int *sdl_delay, unsigned int *cross_sel, unsigned int *nui) {

    int thld_low;
    int thld_high;
    unsigned int lsb;
    int signed zero_code=0;
    int signed nui_zero_code;
    int signed src_delay_tot=0;
    int signed neg_offset=0;
    int signed delay_code_int;

    //--------------------------------------------------------------------------//
    //------------------------ compute  sdl_delay-------------------------------//
    //--------------------------------------------------------------------------//
    // Threshold for cross_sel
    thld_low = wrp_code/4;
    thld_high= wrp_code*3/4;

    //Split delay into NUI and analog delay
    *nui=delay_code/(wrp_code+1);
    *sdl_delay = delay_code - *nui*(wrp_code+1);

    //--------------------------------------------------------------------------//
    //------------------------- compute nui   ----------------------------------//
    //--------------------------------------------------------------------------//
    lsb=TRN_SCN[TRN_IDX_GBL].ui/wrp_code; // indicate how many ps in one UI, 667mts -> 1500ps

    //src_delay_tot = src_delay+TRN_SCN[TRN_IDX_GBL].ui/2;
    src_delay_tot = src_delay;

    // First deal with the offset
    // Get nui with zero code. zero_code is relative intrinsic delay expressed in lsb
    zero_code = dest_delay/lsb-src_delay_tot/lsb;

    // if zer_code is -ve, it means src_delay > dest_delay
    // since clk is periodic , wrap it around to get postive numers
    if (zero_code < 0) {
        neg_offset = src_delay_tot/lsb-dest_delay/lsb;
        zero_code= wrp_code+1-neg_offset;
        nui_zero_code=zero_code/(wrp_code+1);
        nui_zero_code=-1-nui_zero_code;
    } else {
        nui_zero_code = zero_code/(wrp_code+1);
    }

    delay_code_int = *sdl_delay+zero_code;
    *nui=*nui+nui_zero_code;
    if (delay_code_int > wrp_code) {
        delay_code_int = delay_code_int - wrp_code - 1;
        *nui=*nui+1;
    }

    //Readjust nui if high threhold has been exceeded
    if (delay_code_int > thld_high) *nui=*nui+1;

    //--------------------------------------------------------------------------//
    //----------------------- compute crosssel  --------------------------------//
    //--------------------------------------------------------------------------//
    if ( (delay_code_int < thld_low) || (delay_code_int> thld_high) )
        *cross_sel = 0b1;
    else
        *cross_sel = 0b0;

    #if IPM_DBG_NUI_CROSS
      print_dbg("TRNINFO:CROSS_SEL: INP: DlyCode %d, WrpCode %d, SrcDelay: %d DstDelay: %d. INT: Delaycode int %d OUTP:  SDLCode %d, Cross_sel %d, NUI %d E:\n",delay_code,wrp_code,src_delay,dest_delay,delay_code_int,*sdl_delay,*cross_sel,*nui);
    #endif
} // find_ana_cross_sel_nui

//-------------------------------------------------------------------
// Given transition points find the cross_sel.
// Which ever transition point is further away, we assign cross-sel to
// value associated with that transition point
//--------------------------------------------------------------------
int find_cross_sel_com(
	unsigned int delay_code,
	unsigned int wrp_code,
	unsigned int cross_th1,
	unsigned int cross_th2) {

	int dist_th1;
	int dist_th2;
	unsigned int cross_out;

	if (delay_code > cross_th1) {
		dist_th1=delay_code-cross_th1;
	} else {
		dist_th1=cross_th1-delay_code;
	}
	if ( (wrp_code+1-dist_th1) < dist_th1) {
		dist_th1=wrp_code+1-dist_th1;
	}

	if (delay_code > cross_th2) {
		dist_th2=delay_code-cross_th2;
	} else {
		dist_th2=cross_th2-delay_code;
	}
	if ( (wrp_code+1-dist_th2) < dist_th2) {
		dist_th2=wrp_code+1-dist_th2;
	}

	if (dist_th1 > dist_th2) {
		cross_out = 0;
	} else {
		cross_out = 1;
	}
	return(cross_out);
}


void find_ana_cross_sel_nui_new(
	unsigned int delay_code,
	unsigned int wrp_code,
	unsigned int cross_th1,
	unsigned int cross_th2,
	unsigned int nui_incr,
	unsigned int byte_idx,
	unsigned int tran_array_flag, // DQ array or CA array
	unsigned int ch,
	unsigned int *sdl_delay,
	unsigned int *cross_sel,
	unsigned int *nui) {

	// Zero out the old stuff
	int sdl_delay_loc;
	int cross_sel_loc;
	int nui_loc;

	//--------------------------------------------------------------------------//
	//------------------------ compute  sdl_delay and nui ----------------------//
	//--------------------------------------------------------------------------//
	//Split delay into NUI and analog delay
	nui_loc=delay_code/(wrp_code+1);
	sdl_delay_loc = delay_code - nui_loc*(wrp_code+1);

	//---------------------------------------------------------------------------//
	//----------------------- compute crosssel and readjust NUI -----------------//
	//--------------------------------------------------------------------------//
	cross_sel_loc=find_cross_sel_com(sdl_delay_loc,wrp_code,cross_th1,cross_th2);
	unsigned int curr_val;
	if (tran_array_flag==1) {
		// If we are using the normalizer XOV_TRANS data then LPBK_CROSS_OPT is not needed
		curr_val=XOVR_TRANS_DQ[ch][byte_idx][cross_sel_loc][sdl_delay_loc];
	} else {
		// Siva try
		curr_val=XOVR_TRANS_CA[ch][0][cross_sel_loc][sdl_delay_loc];
	}

	// It just worked out this way
	nui_loc = nui_loc+ curr_val-1;

	if (nui_loc <0) {
		print_err("IPM:FIND_ANA_NUI: ERROR! Incorrect transition data %d. Please check cross-sel data  E:\n",curr_val);
		print_err("IPM:FIND_ANA_NUI: ERROR! Inputs Delay %d Wrpcode %d Crossth1 %d Crossth2 %d Byte %d Arrayflag %d Ch %d  E:\n",
			delay_code,wrp_code,cross_th1,cross_th2,byte_idx,tran_array_flag,ch);
	}

	// Assign to outputs
	*nui=nui_loc;
	*sdl_delay=sdl_delay_loc;
	*cross_sel=cross_sel_loc;

	#if IPM_DBG_FIND_CROSS_NUI
		print_dbg( "IPM:CROSS_NUI INP: Byte%d DlyCode %d, WrpCode %d, Cross_th1 %d Cross_th2 %d NUI Incr %d OUTP:  SDLCode %d, Cross_sel %d, NUI %d TRANS DATA %d  E:\n",
					byte_idx,delay_code,wrp_code,cross_th1,cross_th2,nui_incr,*sdl_delay,*cross_sel,*nui,curr_val);
	#endif

} // find_ana_cross_sel_nui_new


void set_ck_delay(unsigned int ck_delay,unsigned int fsp, unsigned int ck_dly_method, unsigned int ch) {

	unsigned int nui=0;
	unsigned int sdl_delay=0;
	unsigned int bank_en=0;
	unsigned int ctrl=0;
	unsigned int cross_sel=0;

	// gate the xover clocks before adjusting settings
	acsr_write_field_ch(M_ANA_CK_CLK_EN,0b0,ch);
	acsr_write_field_ch(M_ANA_HV_CLK_EN,0b0,ch);

	// Do the computations required to set digital and analog delays
	if ((ck_dly_method==0) || (CC_XOVR_OLD==1)) {
		find_ana_cross_sel_nui(ck_delay,SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL],XOVR_SRCDLY_CK[ch][TRN_IDX_GBL],XOVR_DSTDLY_CK[ch][TRN_IDX_GBL],&sdl_delay,&cross_sel,&nui);
	} else {
		find_ana_cross_sel_nui_new(
		ck_delay,
		SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL],
		XOVR_THLD_CA[ch][0][0][TRN_IDX_GBL],
		XOVR_THLD_CA[ch][1][0][TRN_IDX_GBL],
		XOVR_THLD_CA[ch][2][0][TRN_IDX_GBL],
		0,
		0,
		ch,
		&sdl_delay,
		&cross_sel,
		&nui);
	}
	set_sdl_bank_en_ctrl(sdl_delay,&bank_en,&ctrl);

	// Set the SDL delay. HV SDL cntrols CK
	acsr_write_field_ch(M_ANA_SDL_HV_CTRL[fsp], 	ctrl,ch);
	acsr_write_field_ch(M_ANA_SDL_HV_BANK_EN[fsp], 	bank_en,ch);
	// FYI this is not required to be written everytime. But it is convinient to take care here
	acsr_write_field_ch(M_ANA_SDL_HV_CAP_EN[fsp], SDL_CAP_EN_OPT[TRN_IDX_GBL],ch	);

	// Set the digital pipe delay
	apb_write_field_ch(M_CK_PIPE_DLY[fsp], nui,ch);

	// Set the xover
	acsr_write_field_ch(M_ANA_CROSS_SEL_CKC[fsp], cross_sel,ch);
	acsr_write_field_ch(M_ANA_CROSS_SEL_CKT[fsp], cross_sel,ch);

	// Enable the ccr xover clks after settings update
	delay(t_PIPE_SETTLE);
	acsr_write_field_ch(M_ANA_CK_CLK_EN,0b1,ch);
	acsr_write_field_ch(M_ANA_HV_CLK_EN,0b1,ch);

} // set_ck_delay

//---------------------------------------------------------------------------------------------------
// pll_freq_change_proc :This method is used to change the pll frequency. Steps are
//                       1. stop CK
//                       2. change freq, wait for pll lock
//                       3. if boot_clk_config is 1, wcross is configured for R->F boot clock
//                          and clock sync block reset is asserted
//                          else clock sync procedure is executed
//                       4. enable CK
//---------------------------------------------------------------------------------------------------
void pll_freq_change_procedure (
	unsigned int  fsp,
	unsigned int  freq_ratio,
	unsigned int  freq_idx,
	unsigned int  reset_n_val,
	unsigned int  cke0_val,
	unsigned int  ck_dly_method
	) {

    unsigned short accum_obsv_hi, accum_obsv_lo;
    unsigned int ck_delay;

    for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
      //First drive CKE low
      apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],0b00,ch); //BFS: CKE shud go low
      apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],BITS_GET(reset_n_val,1,0),ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],0b00,ch);

      //Added delay for PLL set up time
      apb_write_field_ch(M_CKHV_PTRNBUF_DELAY[0],0x10,ch);

      // Flush pattern buffer
      apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 0x00,ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);
      apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
      wait_ptrn_done (ch);

      //Wait before disabling clk
      delay(t_CKELCK);

      //Then STOP CK by driving CK_t low and CK_c high
      apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],0b11,ch);
      apb_write_field_ch(M_CK_HV_PTRN_EN,0b1,ch);
      wait_ptrn_done(ch);

      //CHK :
      apb_write_field_ch(M_CUR_FSP, fsp,ch);
    }

    //==================================================================
    //CLOCK SWITCHING - boot to HF
    //==================================================================
    // Reset PLL
    reset_pll(fsp, freq_ratio, freq_idx);
    delay(10);

    apb_write_field(M_PLL_RSTN, 		0b0);  //pll_rstn
    delay(10);

    // Reset DLL
    // Commenting this out seems to help with PLL lock
    // reset_dll();
    // delay(10);

    // set up frequency set points
    setup_fsps(fsp, freq_ratio, freq_idx);

    //Deassert PLL RESET 
    apb_write_field(M_PLL_RSTN, 		0b1);

    // Release accumulator from manual override
    apb_write( PLL_FREEZE_REGS_ADDR,          0x0001 );
    apb_write( PLL_ACCUM_OVRD_CTRL_ADDR  ,    0x0000 );
    apb_write( PLL_FREEZE_REGS_ADDR,          0x0000 );

    apb_poll_field(M_PLL_LOCK_DET_LOCKED,1);
    print_info("IPM:PLL/DLL: High freq PLL lock done E:\n");

    // gate the xover clocks before adjusting settings
    // Forthe HV outputs, stop the XOVER clk so that previous state is retained
    for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
      print_dbg("IPM:PLL/DLL: Lock: Set HV CLKEN=0 Ch%d  E:\n",ch);
      acsr_write_field_ch(M_ANA_HV_CLK_EN,0b0,ch);
      delay(t_PIPEDELAY);
    }

    // Reset and release the pipe resets
    print_dbg("IPM:PLL/DLL: Lock: Release pipe reset  E:\n");
    reset_release_pipe_rstn();
    // Make sure reset has propagated thru the pipeline
    delay(t_PIPE_RSTN);

    //Set reset back to high but dont start clk yet
    for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
      print_dbg("IPM:PLL/DLL: Lock: Restore resetn pipe to logic high Ch%d  E:\n",ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_CKE[1],		0b00,ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_RESET[1], BITS_GET(reset_n_val,1,0),ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[1], 0b11,ch); //BFS: Changed to 00
      apb_write_field_ch(M_CK_HV_PTRN_EN, 	0b1,ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x01,ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x01,ch);
      wait_ptrn_done(ch);
      delay(t_PIPE_SETTLE);

      //Configure CK pipe for high freq operation
      //Need NUI=1 for CK
      ck_delay=CK_DELAY_UI*(SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]+1);
      set_ck_delay(ck_delay,fsp,ck_dly_method,ch);
      delay(t_PIPE_SETTLE);
      print_dbg("IPM:PLL/DLL: Lock: Setting CK delay %d for high speed operation Ch%d  E:\n",ck_delay,ch);

      // Turn HV CLK back on after pattern buffer has driven the right value into
      // the pipeliness
      print_dbg("IPM:PLL/DLL: Lock: Set HV CLKEN=1 Ch%d  E:\n",ch);
      acsr_write_field_ch(M_ANA_HV_CLK_EN,0b1,ch);

      // Turn CK ON
      print_dbg("IPM:PLL/DLL: Lock: Start CK Ch%d  E:\n",ch);
      apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[1], 0b00,ch); //BFS: Changed to 00
      apb_write_field_ch(M_CK_HV_PTRN_EN, 	0b1,ch);
      wait_ptrn_done(ch);

      //Now assert CKE after clk start
      print_dbg("IPM:PLL/DLL: Lock: Restart CKE Ch%d  E:\n",ch);
      delay(t_CKCKEH);
      apb_write_field_ch(M_CKHV_PTRNBUF_CKE[1],		BITS_GET(cke0_val,1,0),ch);
      apb_write_field_ch(M_CK_HV_PTRN_EN, 	0b1,ch);
      wait_ptrn_done(ch);

    }
  } // pll_freq_change_procedure

void stop_ck(unsigned int cke_val,unsigned int reset_n_val, unsigned int ch) {
  //First drive CKE low
  apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],0b00,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],reset_n_val,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],0b00,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x00,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);

  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
  wait_ptrn_done(ch);

  //Wait before disabling clk
  delay(t_CKELCK);

  //Then STOP CK by driving CK_t low and CK_c high
  apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0], 	0b11,ch);

  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
  wait_ptrn_done(ch);
} // stop_ck

//------------------------------------------------------------------------------
// lpbk Pattern buffer programming
//------------------------------------------------------------------------------
void set_lpbk_patbuf(
  unsigned int fsp,
  unsigned int freq_ratio,
  unsigned int freq_idx,
  unsigned int invert,
  unsigned int ch) {

  unsigned int rdcs_val;
  unsigned int wrcs_val;
  unsigned int  write_dq_packed  [PHY_DQS_WIDTH][PHY_DQ_PER_DQS];
  unsigned int  write_dq_packed_0[PHY_DQS_WIDTH][PHY_DQ_PER_DQS];
  unsigned int  write_dq_packed_1[PHY_DQS_WIDTH][PHY_DQ_PER_DQS];

  // Initialize array holding pattern
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    for (unsigned int bit_idx=0;bit_idx< PHY_DQ_PER_DQS; bit_idx++) {
      write_dq_packed[byte_idx][bit_idx]=0;
      write_dq_packed_0[byte_idx][bit_idx]=0;
      write_dq_packed_1[byte_idx][bit_idx]=0;
    }
  }

  // Fill array holding data pattern
  for (unsigned int burst_idx=0;burst_idx<WRDQ_TRAIN_BL;burst_idx++) for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
   //   BIT_SET(write_dq_packed[byte_idx][bit_idx],burst_idx,BIT_GET(WRDQ_TRAIN_PAT_LPBK[burst_idx][byte_idx],bit_idx));
    }
    for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
    //  BIT_SET(write_dq_packed_1[byte_idx][bit_idx],burst_idx,BIT_GET(WRDQ_TRAIN_PAT_LPBK[burst_idx][byte_idx],bit_idx));
    }
  }

  // For stuffing with zeroes , we need an extra index.
  // So, set burst_idx=8 to zero
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
  //    BIT_SET(write_dq_packed[byte_idx][bit_idx],8,0b0);
    }
  }

  //ld_cnt=3 data is the ideal burst data, 0->1->2->3
  for (unsigned int burst_idx=0;burst_idx<WRDQ_TRAIN_BL;burst_idx=burst_idx+4) {
    for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
      for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
        //For ld_cnt=0, data will be 1->2->3->0->5->6->7->4
        //but as DQS will also get shifted so first data will be not there so
        //data will be 2->3->0->5->6->7->4
     //   BITS_SET(write_dq_packed_0[byte_idx][bit_idx], burst_idx+3, burst_idx, ((BIT_GET(write_dq_packed_1[byte_idx][bit_idx],burst_idx+3+2)<<3) | (BIT_GET(write_dq_packed_1[byte_idx][bit_idx],burst_idx+2)<<2) | (BIT_GET(write_dq_packed_1[byte_idx][bit_idx],burst_idx+1+2)<<1) | BIT_GET(write_dq_packed_1[byte_idx][bit_idx],burst_idx+0)));
      }
    }
  }

  // DQ pattern buffer programming
  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {

    // Strech value of WDQS set it to zero.
    apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp],0,ch);

    // Program the write dq pattern buffer

    // Ref from WR DQ
    for (unsigned int row_idx=0;row_idx<=(WRDQ_TRAIN_BL/2);row_idx++) {
    //for (int unsigned row_idx=0;row_idx<`WRDQ_TRAIN_BL/2;row_idx++) begin
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b1,ch);  //Assert wdqs for BL/2*tck
      apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }
    for (unsigned int row_idx=(WRDQ_TRAIN_BL/2);row_idx<=7;row_idx++) {
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b0,ch);  //De-assert wdqs
      apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }

    for (unsigned int bit_idx=0;bit_idx<PHY_DQ_PER_DQS;bit_idx++) {

			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][0][bit_idx], BITS_GET(write_dq_packed[byte_idx][bit_idx],1,0),ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][1][bit_idx], BITS_GET(write_dq_packed[byte_idx][bit_idx],3,2),ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][2][bit_idx], BITS_GET(write_dq_packed[byte_idx][bit_idx],5,4),ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][3][bit_idx], BITS_GET(write_dq_packed[byte_idx][bit_idx],7,6),ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][4][bit_idx], 0,ch);
      if(invert == 1){
      	//for write load count 1
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][5][bit_idx], ~BITS_GET(write_dq_packed_1[byte_idx][bit_idx],1,0),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][6][bit_idx], ~BITS_GET(write_dq_packed_1[byte_idx][bit_idx],3,2),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][7][bit_idx], ~BITS_GET(write_dq_packed_1[byte_idx][bit_idx],5,4),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][8][bit_idx], ~BITS_GET(write_dq_packed_1[byte_idx][bit_idx],7,6),ch);
      	//for write load count 0. Note that we are comparing only 7 bits. 8th bit is a zero.
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][9][bit_idx],  ~BITS_GET(write_dq_packed_0[byte_idx][bit_idx],1,0),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][10][bit_idx], ~BITS_GET(write_dq_packed_0[byte_idx][bit_idx],3,2),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][11][bit_idx], ~BITS_GET(write_dq_packed_0[byte_idx][bit_idx],5,4),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][12][bit_idx], ~BITS_GET(write_dq_packed_0[byte_idx][bit_idx],7,6),ch); // 8 is for stuffing zero

	      } else {
      	//for write load count 1
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][5][bit_idx], BITS_GET(write_dq_packed_1[byte_idx][bit_idx],1,0),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][6][bit_idx], BITS_GET(write_dq_packed_1[byte_idx][bit_idx],3,2),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][7][bit_idx], BITS_GET(write_dq_packed_1[byte_idx][bit_idx],5,4),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][8][bit_idx], BITS_GET(write_dq_packed_1[byte_idx][bit_idx],7,6),ch);
      	//for write load count 0
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][9][bit_idx],  BITS_GET(write_dq_packed_0[byte_idx][bit_idx],1,0),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][10][bit_idx], BITS_GET(write_dq_packed_0[byte_idx][bit_idx],3,2),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][11][bit_idx], BITS_GET(write_dq_packed_0[byte_idx][bit_idx],5,4),ch);
				apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][12][bit_idx], BITS_GET(write_dq_packed_0[byte_idx][bit_idx],7,6),ch);
      }
    }
    apb_write_field_ch(M_WDQ_PTRNBUF_START_PTR[byte_idx],0,ch);
    apb_write_field_ch(M_WDQ_PTRNBUF_STOP_PTR[byte_idx],4,ch);

  }
}

void set_kick(unsigned int kick, unsigned int ch) {

   for (unsigned int idx=0; idx<PHY_DQS_WIDTH; idx++) {
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_DMI_R[idx], 0b11,ch);
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_DMI_R[idx], kick,ch);
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_DMI_F[idx], 0b11,ch);
      acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_DMI_F[idx], kick,ch);
   }

   // for (unsigned int idx=0; idx<PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1); idx++) { // vsi try
   for (unsigned int idx=0; idx<PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1); idx++) {
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_R[idx], 0b11,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_R[idx], kick,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_LB_F[idx], 0b11,ch);
     acsr_write_field_ch(M_ANA_DQ_FE_DAC_KICK_HB_F[idx], kick,ch);
  }
  delay(1);
}

void set_wdq_delay_lpbk(
	unsigned int nui,
	unsigned int sdl,
	unsigned int cross_sel,
	unsigned int byte_start,
	unsigned int byte_stop,
	unsigned int fsp,
	unsigned int ch) {
	unsigned int nui_dly, nui_oe_dly, sdl_dly, sdl_bank_en, sdl_ctrl, sdl_cap_en;

	// Do the computations required to set digital and analog delays
	//find_ana_cross_sel_nui_trn_fw(delay,t_obj.TR_WRP_CODE_WDQ_SDL,t_obj.TR_ZOFFSET_CODE_WDQ_SDL,sdl_dly,cross_sel,nui_dly);
	//find_ana_cross_sel_nui_trn(delay,SDL_WRP_CODE_OPT_DQ[ch][TRN_IDX_GBL],XOVR_SRCDLY_WDQ[byte_idx][TRN_IDX_GBL],XOVR_DSTDLY_WDQ[byte_idx][TRN_IDX_GBL],&sdl_dly,&cross_sel,&nui_dly);

	sdl_dly=sdl;
	nui_dly=nui;

	set_sdl_bank_en_ctrl(sdl_dly,&sdl_bank_en,&sdl_ctrl);
	sdl_cap_en = SDL_CAP_EN_OPT[TRN_IDX_GBL];
	nui_oe_dly = nui_dly;

	for (unsigned int byte_idx=byte_start;byte_idx<=byte_stop;byte_idx++) {
		acsr_write_field_ch(M_ANA_SDL_DQ_CTRL[byte_idx][fsp], sdl_ctrl,ch);
		acsr_write_field_ch(M_ANA_SDL_DQ_BANK_EN[byte_idx][fsp], sdl_bank_en,ch);
		acsr_write_field_ch(M_ANA_SDL_DQ_CAP_EN[byte_idx][fsp], sdl_cap_en,ch);

		acsr_write_field_ch(M_ANA_DQ_CROSS_SEL[byte_idx][fsp], cross_sel,ch);
		acsr_write_field_ch(M_ANA_CROSS_SEL_DMI[byte_idx][fsp],cross_sel,ch);
		for (unsigned int dq_idx=byte_idx*(PHY_DQ_PER_DQS-1); dq_idx<byte_idx*(PHY_DQ_PER_DQS-1)+PHY_DQ_PER_DQS-1; dq_idx++)
			acsr_write_field_ch(M_ANA_CROSS_SEL_DQ[dq_idx][fsp],cross_sel,ch);

		apb_write_field_ch(M_WDQ_PIPE_DLY[byte_idx][fsp],nui_dly,ch);
		apb_write_field_ch(M_WDQ_PIPE_OE_DLY[byte_idx][fsp],nui_oe_dly,ch);
		apb_write_field_ch(M_W_DQ_CS_PIPE_DLY[byte_idx][fsp],nui_oe_dly,ch);
	}
}

void set_wdqs_delay_lpbk(
	unsigned int nui,
	unsigned int sdl,
	unsigned int cross_sel,
	unsigned int byte_start,
	unsigned int byte_stop,
	unsigned int  fsp,
	unsigned int ch) {

	unsigned int nui_wdqs;
	unsigned int sdl_delay_wdqs;
	unsigned int  bank_en_wdqs;
	unsigned int  ctrl_wdqs;
	unsigned int  cross_sel_wdqs;

	unsigned int nui_wdqs_oe;
	unsigned int nui_wdqs_early;
	unsigned int byte_idx;

	for(byte_idx=byte_start;byte_idx<=byte_stop;byte_idx++) {
		// Do the computations required to set digital and analog delays for WDQS
		nui_wdqs=nui;
		cross_sel_wdqs=cross_sel;
		sdl_delay_wdqs=sdl;

		set_sdl_bank_en_ctrl(sdl_delay_wdqs,&bank_en_wdqs,&ctrl_wdqs);

		// Anytime wdqs delay is set, there are dependent delays that go with that
		// also need to be set. Figure out the dependent delays
		nui_wdqs_oe=nui_wdqs;
		nui_wdqs_early=nui_wdqs;

		if ((nui_wdqs_oe<0) || (nui_wdqs_early<0)) {
			//`uvm_fatal("IPM:WRLVL:", $sformatf("-ve NUI delay encountered. Please check wdqs range. WDQSOE Delay: %d WDQS_EARLY Delay: %d",nui_wdqs_oe,nui_wdqs_early));
		}

		// Set the SDL delay
		acsr_write_field_ch(M_ANA_SDL_DQS_CTRL[byte_idx][fsp],ctrl_wdqs,ch);
		acsr_write_field_ch(M_ANA_SDL_DQS_BANK_EN[byte_idx][fsp],bank_en_wdqs,ch);
		acsr_write_field_ch(M_ANA_SDL_DQS_CAP_EN[byte_idx][fsp],SDL_CAP_EN_OPT[TRN_IDX_GBL],ch);

		// Set the xover
		acsr_write_field_ch(M_ANA_CROSS_SEL_DQSC[byte_idx][fsp],cross_sel_wdqs,ch);
		acsr_write_field_ch(M_ANA_CROSS_SEL_DQST[byte_idx][fsp],cross_sel_wdqs,ch);

		// Set the digital pipe delay
		apb_write_field_ch(M_WDQS_PIPE_DLY[byte_idx][fsp],nui_wdqs,ch);
		apb_write_field_ch(M_WDQS_PIPE_OE_DLY[byte_idx][fsp],nui_wdqs_oe,ch);
		apb_write_field_ch(M_WRITE_EN_EARLY_PIPE_DLY[byte_idx][fsp],nui_wdqs_early,ch);
		apb_write_field_ch(M_W_DQS_CS_PIPE_DLY[byte_idx][fsp],nui_wdqs_oe,ch);
	}

} // set_wdqs_delay_lpbk

//------------------------------------------------------------------------------
// Set rdqs delay
//------------------------------------------------------------------------------
void set_rdqs_delay(unsigned int rdqs_delay, unsigned int fsp, unsigned int byte_start, unsigned int byte_end, unsigned int ch) {

  unsigned int bank_en_rdqs;
  unsigned int ctrl_rdqs;

  set_sdl_bank_en_ctrl(rdqs_delay,&bank_en_rdqs,&ctrl_rdqs);
  for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
    acsr_write_field_ch(M_ANA_RXSDL_BANK_EN_R_DQS[byte_idx][fsp],bank_en_rdqs,ch);
    acsr_write_field_ch(M_ANA_RXSDL_BANK_EN_F_DQS[byte_idx][fsp],bank_en_rdqs,ch);

    acsr_write_field_ch(M_ANA_RXSDL_CTRL_R_DQS[byte_idx][fsp],ctrl_rdqs,ch);
    acsr_write_field_ch(M_ANA_RXSDL_CTRL_F_DQS[byte_idx][fsp],ctrl_rdqs,ch);

    acsr_write_field_ch(M_ANA_RXSDL_CAP_EN_DQS[byte_idx][fsp],SDL_CAP_EN_OPT[TRN_IDX_GBL],ch);
  }
}

// Improved function for finding vertical center
int find_optimal_com (
		uint8_t* result_ar,
		unsigned int col_width,
		unsigned int byte_start ,
		unsigned int byte_end,
		unsigned int vref_start,
		unsigned int vref_end,
		unsigned int vref_step,
		unsigned int delay_start,
		unsigned int delay_end,
		unsigned int delay_step,
		unsigned int pass_region_thld,
		unsigned int pass_region_diff,
		unsigned int dbg,
		unsigned int *vref_opt,
		unsigned int *delay_opt,
    unsigned int *passing_size_opt) {

	signed int pass_region=0, pass_region_opt=0 ;
	signed int start_pass=0 , end_pass=0 ;
	uint32_t prev_result=1 ,curr_result=1;
	static uint32_t vref_pass_region[TRNOPT_MAXLEN] = {0} ; //Contains all vref with maxpass region
	static uint32_t opt_delay[TRNOPT_MAXLEN] = {0} ;//optimal delay value for each vref
	static uint32_t opt_delay_size[TRNOPT_MAXLEN] = {0} ;//optimal delay passing region size for each vref
	uint32_t result_size=0, pass_region_size=0;
	uint32_t start_pass_found=0,end_pass_found=0;
	uint32_t found_window=0;
	uint32_t vref_index_opt ;
	uint32_t delay_index_opt ;
	uint32_t max_pass_region=0;

	// 31:24 is the vref start for wrdq training
	// 23:16 is the wrdq_delay_len, including the dummy parts not used
	// 04:04 is the lpbk_training flag
	// 03:00 is the debug flag
	uint32_t wrdq_trn_flag   = BIT_GET(dbg, 31) ;
	uint32_t vref_start_real = BITS_GET(dbg, 30, 24) ;
	uint32_t wrdq_delay_len  = BITS_GET(dbg, 23, 16) ;
	// we'll do lpbk_training many times, and most time cannot find the optimal
	// to avoid too many messaegs like "pass window not found"
	uint32_t lpbk_trn_flag   = BIT_GET(dbg, 4) ;
	dbg = BITS_GET(dbg, 3, 0) ;


	result_size = 0 ;
	// In the first iteration find the largest passing window. This will serve as reference for 2nd iteration
	for (int vref_index=vref_start;vref_index<=vref_end;vref_index=vref_index+vref_step) {
		start_pass=0;
		end_pass=0;
		pass_region=0;
		curr_result=1;
		prev_result=1;
		start_pass_found=0;
		end_pass_found=0;

		for (int delay_index=delay_start;delay_index<=delay_end;delay_index=delay_index+delay_step) {
			curr_result=0;
			// The purpose of this loop is to merge results of bytes as needed for e.g. in wrdq training
			for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
				if (wrdq_trn_flag) {
					curr_result=curr_result+result_ar[result_size*col_width+byte_start+(vref_index-vref_start_real)/vref_step*wrdq_delay_len*col_width];
				} else {
					curr_result=curr_result+result_ar[result_size*col_width+byte_idx];
				}
				// curr_result += result_ar[(vref_index-vref_start)/vref_step*delay_len*col_width + (delay_index-delay_start)/delay_step*col_width + byte_start] ;
			}
			result_size++;
			if (dbg==1) {
			print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] Curr Result %d E:\n", vref_index, delay_index, curr_result) ;
			}

			//Locate fail->pass or initial pass
			if ((curr_result==0) && ((prev_result>0)||(delay_index==0))) {
				start_pass = delay_index;
				start_pass_found=1;
				if (dbg==1) {
				print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] fail to pass, start_pass = %d E:\n", vref_index, delay_index, start_pass) ;
				}
			}
			//Locate pass-> fail or final pass
			if ((prev_result==0) && (curr_result>0)) {
				end_pass = delay_index-delay_step;
				end_pass_found=1;
				if (dbg==1) {
				print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] pass to fail, end_pass = %d E:\n", vref_index, delay_index, end_pass) ;
				}
			} else if ((curr_result==0) && (delay_index==delay_end)) {
				end_pass = delay_index;
				end_pass_found=1;
				if (dbg==1) {
				print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] final is pass, end_pass = %d E:\n", vref_index, delay_index, end_pass) ;
				}
			}

			// Calculate passing region
			if ((start_pass_found==1) && (end_pass_found==1)) {
				found_window=1;
				pass_region=end_pass-start_pass;

				if(pass_region>max_pass_region) {
					//store the result of max pass region
					max_pass_region=pass_region;
					if (dbg==1) {
					print_dbg("IPM:FIND_OPT: Iter 0 [vref_index: %d, delay_index: %d] First Iteration: New max passing window found. Startpass,endpass,Passing window = %d,%d,%d E:\n", vref_index, delay_index, start_pass,end_pass,pass_region);
					}
				}
				//Reset the flags so that next passing region can be found
				start_pass_found=0;
				end_pass_found=0;
			}
			prev_result=curr_result;
		}
	}

	if (found_window==0 ) {
		*vref_opt=0;
		*delay_opt=0;
		*passing_size_opt=0;
		return -1 ;
	} else if (max_pass_region < pass_region_thld) {
		*vref_opt=0;
		*delay_opt=0;
		*passing_size_opt=0;
		return -1 ;
	} else {
		found_window=0;
		pass_region_size=0;
		result_size=0;
		if (dbg==1) {
			print_dbg("IPM:FIND_OPT: First Iteration maxpass window %d  E:\n", max_pass_region) ;
		}

		for (int vref_index=vref_start;vref_index<=vref_end;vref_index=vref_index+vref_step) {
			start_pass=0;
			end_pass=0;
			pass_region=0;
			curr_result=1;
			prev_result=1;
			start_pass_found=0;
			end_pass_found=0;

			for (int delay_index=delay_start;delay_index<=delay_end;delay_index=delay_index+delay_step) {
				curr_result=0;
				// The purpose of this loop is to merge results of bytes as needed for e.g. in wrdq training
				for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
					if (wrdq_trn_flag) {
						curr_result=curr_result+result_ar[result_size*col_width+byte_start+(vref_index-vref_start_real)/vref_step*wrdq_delay_len*col_width];
					} else {
						curr_result=curr_result+result_ar[result_size*col_width+byte_idx];
					}
				}
				result_size++;
				if (dbg==1) {
					print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] Curr Result %d E:\n", vref_index, delay_index, curr_result) ;
				}

				//Locate fail->pass or initial pass
				if ((curr_result==0) && ((prev_result>0)||(delay_index==0))) {
					start_pass = delay_index;
					start_pass_found=1;
					if (dbg==1) {
						print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] fail to pass, start_pass = %d E:\n", vref_index, delay_index, start_pass) ;
					}
				}
				//Locate pass-> fail or final pass
				if ((prev_result==0) && (curr_result>0)) {
					end_pass = delay_index-delay_step;
					end_pass_found=1;
					if (dbg==1) {
						print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] pass to fail, end_pass = %d E:\n", vref_index, delay_index, end_pass) ;
					}
				} else if ((curr_result==0) && (delay_index==delay_end)) {
					end_pass = delay_index;
					end_pass_found=1;
					if (dbg==1) {
						print_dbg("IPM:FIND_OPT: [vref_index: %d, delay_index: %d] final is pass, end_pass = %d E:\n", vref_index, delay_index, end_pass) ;
					}
				}

				// Calculate passing region
				if ((start_pass_found==1) && (end_pass_found==1)) {
					found_window=1;
					pass_region=end_pass-start_pass;

					if(pass_region>=(max_pass_region-pass_region_diff)) {
						//store the result of max pass region
						vref_pass_region[pass_region_size] = vref_index;
						// opt_delay[pass_region_size] = ((start_pass+end_pass)/2);
						opt_delay[pass_region_size] = ((start_pass+end_pass)%2) ? ((start_pass+end_pass)/2)+1 : ((start_pass+end_pass)/2); // vsi try
						opt_delay_size[pass_region_size]=pass_region;
						if (dbg==1) {
							print_dbg("IPM:FIND_OPT: Iter1 [vref_index: %d, delay_index: %d] New max passing window found. Startpass,endpass,Passing window = %d,%d,%d MaxWindow Index=%d  E:\n", vref_index, delay_index, start_pass,end_pass,pass_region,pass_region_size);
						}
						pass_region_size++;
					}
					//Reset the flags so that next passing region can be found
					start_pass_found=0;
					end_pass_found=0;
				}
				prev_result=curr_result;
			}
		}
		// Get the optimal vref and delay
		if (found_window==1) { // If windowis found. Training pass
			curr_result=pass_region_size/2;
			*vref_opt=vref_pass_region[curr_result];
			*delay_opt=opt_delay[curr_result];
			*passing_size_opt=opt_delay_size[curr_result];

			if (dbg==1) {
				print_dbg("IPM:FIND_OPT: vertical pass_region %d horizonal pass_region %d  E:\n\n", pass_region_size, *passing_size_opt);
			}

			if ( (*passing_size_opt < pass_region_thld) ) {
				if (!lpbk_trn_flag) {
					print_err("IPM:FIND_OPT: ERROR! pass_region too small < 0x%x E:\n", pass_region_thld) ;
					print_err("IPM:FIND_OPT: vertical pass_region %d horizonal pass_region %d E:\n", pass_region_size, *passing_size_opt);
					print_err("IPM:FIND_OPT: curr vref_opt = %0d delay_opt = %d E:\n", *vref_opt, *delay_opt) ;
				}
				*vref_opt=0;
				*delay_opt=0;
				*passing_size_opt=0;
				return -1 ;
			} else {
				if (dbg==1) {
					print_dbg("IPM:FIND_OPT: Final vref_opt = %d, delay_opt = %d E:\n", *vref_opt, *delay_opt) ;
				}
			}
		} else { // Window is not found. Training fail.
			*vref_opt=0;
			*delay_opt=0;
			*passing_size_opt=0;
			return -1 ;
		}
	}

} // find_optimal_com

void reset_dqbyte_ovr(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {

  for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
    //Remove all the overrides
    apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_TXDQSOE[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_RXDQEN[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_RXDQSEN[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_DQODT[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_DQSODT[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_RDQSEN[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_WREN_EARLY[byte_idx],0b00,ch);
    apb_write_field_ch(M_OVR_RDEN_EARLY[byte_idx],0b00,ch);
  }
}

void reset_dqbyte_fifoptr(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
  for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
    //Reset read fifo point unsigneders. Keep them in reset. When required
    //later they can be de-asserted
    apb_write_field_ch(M_RDFIFO_RESET_N[byte_idx],0b0,ch);
  }
}

void reset_dqbyte_lpbk(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
  for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
    // Reset loopback sel
    acsr_write_field_ch(M_ANA_LPBK_SEL_DQS[byte_idx],0b0,ch);
    acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DMI[byte_idx], 0b0,ch);
    for (unsigned int i=0; i<(DQ_BITS_PER_SLICE-1); i++) acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DQ[i + (byte_idx*(DQ_BITS_PER_SLICE-1))], 0b0,ch);
  }
}

void reset_dqbyte_rdqsen(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
  for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
    //Dont bypass RDQSEN flop
    acsr_write_field_ch(M_ANA_DQS_RESET[byte_idx],0b1,ch);     // Reset DQS -ve edge flop
    acsr_write_field_ch(M_ANA_DQS_RD_EN_SEL[byte_idx],0b1,ch); // Dont bypass RDQSEN -ve edge flop
  }
}

void reset_dqbyte_edgecomb(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
	for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
		acsr_write_field_ch(M_ANA_EDGE_RESETB_DQS[byte_idx],0b0,ch);
	}

} // reset_dqbyte_edgecomb_trn

void reset_release_dqbyte_fifoptr(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
  for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
    //Reset read fifo point unsigneders. Keep them in reset. When required
    //later they can be de-asserted
    apb_write_field_ch(M_RDFIFO_RESET_N[byte_idx],0b1,ch);
  }
}

void reset_release_dqbyte_rdqsen(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
	for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
		//Dont bypass RDQSEN flop
		acsr_write_field_ch(M_ANA_DQS_RESET[byte_idx],0b0,ch);     // Deassert Reset DQS -ve edge flop
		acsr_write_field_ch(M_ANA_DQS_RD_EN_SEL[byte_idx],0b1,ch); // Dont bypass RDQSEN -ve edge flop
	}
}

void reset_release_dqbyte_edgecomb(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
	for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
		acsr_write_field_ch(M_ANA_EDGE_RESETB_DQS[byte_idx],0b1,ch);
	}

} // reset_release_dqbyte_edgecomb_trn

//---------------------------------------------------------------------------
// Reset DQ pipeline controls. Usually used to restore pipe after training
//---------------------------------------------------------------------------
void reset_dqbyte_controls(unsigned int byte_start, unsigned int byte_end, unsigned int ch) {

  //Reset pipe overrides
  reset_dqbyte_ovr(byte_start,byte_end,ch);

  //Reset read fifo point unsigneders
  reset_dqbyte_fifoptr(byte_start,byte_end,ch);

  //Reset loopback
  reset_dqbyte_lpbk(byte_start,byte_end,ch);

  //Reset rdqsen -ve egde flop
  reset_dqbyte_rdqsen(byte_start,byte_end,ch);

  // Reset edge combiner
  reset_dqbyte_edgecomb(byte_start,byte_end,ch);

  // Set the stretch value for DQS back to original value
  for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
    for (unsigned int fsp_idx=0;fsp_idx<=1;fsp_idx++) {
      apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp_idx],STRCH_WDQS,ch);
    }
  }

  // Release the resets for fifoptr and rden
  reset_release_dqbyte_fifoptr(byte_start,byte_end,ch);
  reset_release_dqbyte_rdqsen(byte_start,byte_end,ch);
  reset_release_dqbyte_edgecomb(byte_start,byte_end,ch);
}

void start_ck(unsigned int cke_val,unsigned int reset_n_val,unsigned int ch) {

  //Start CK
  apb_write_field_ch(M_CKHV_PTRNBUF_CKE[1], 0b00,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_RESET[1], 	reset_n_val,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[1], 	0b00,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x01,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x01,ch);

  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
  wait_ptrn_done(ch);

  delay(t_CKCKEH);

  //Now assert CKE after clk start
  apb_write_field_ch(M_CKHV_PTRNBUF_CKE[1],      (BITS_GET(cke_val,1,0)),ch);

  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
  wait_ptrn_done(ch);

} // start_ck

void read_rdq_patbuf_cmpr(unsigned int *cmpr_fail, unsigned int ch) {
  //vsi fix
  *cmpr_fail = 0;

  //This is the optimal way of reading; not working as ipm_csr.dfi_wr_mask_ptrn_buf is Z making per byte result not reliable
  //apb_read_field(M_RDQ_PTRNBUF_CMP_PF[byte_idx], /***/cmpr_fail);
  unsigned short read_data_0[PHY_DQS_WIDTH], read_data_1[PHY_DQS_WIDTH];
  read_data_0[0] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_0_PB0_ADDR,ch); // byte0 [15:0]
  read_data_1[0] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_1_PB0_ADDR,ch); // byte0 16
  read_data_0[1] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_0_PB1_ADDR,ch);
  read_data_1[1] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_1_PB1_ADDR,ch);
  read_data_0[2] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_0_PB2_ADDR,ch);
  read_data_1[2] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_1_PB2_ADDR,ch);
  read_data_0[3] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_0_PB3_ADDR,ch);
  read_data_1[3] =   apb_read_ch(RDQ_PTRNBUF_CMPR_PF_1_PB3_ADDR,ch);

  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
	  if ((read_data_0[byte_idx]>0)||(read_data_1[byte_idx]>0)) {
		  BIT_SET(*cmpr_fail,byte_idx,1);
	  }
	  else {
		  BIT_SET(*cmpr_fail,byte_idx,0);
	  }
  }
}

void set_rdq_vref_trn(int dac_code, int ch) {

  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_F[byte_idx],dac_code,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_R[byte_idx],dac_code,ch);
  }

  for (unsigned int bit_idx=0;bit_idx<(PHY_DQS_WIDTH*(PHY_DQ_PER_DQS-1));bit_idx++) {
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_F[bit_idx], dac_code,ch);
    acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_R[bit_idx], dac_code,ch);
  }
}

//--------------------------------------------------------------------------------------
// DQ LPBK: Do a 2-D eye scan to get lpbk timing prior to doing cross-sel
//--------------------------------------------------------------------------------------
void do_dq_patbuf_lpbk (unsigned int fsp,unsigned int  freq_ratio,unsigned int  freq_idx,unsigned int ch) {

	unsigned int  read_data;
	unsigned int  data_fail;
	unsigned int  lpbk_done=0;
	unsigned int  lpbk_done_raw=0;
	unsigned int  lpbk_pass[PHY_DQS_WIDTH]={0};
	unsigned int  loop_idx=0;
	unsigned int  cmpr_start_ptr;
	unsigned int  cmpr_stop_ptr;
	unsigned int  rfirst;
	unsigned int  nui;
	unsigned int  cmpr_ptr;
	static uint8_t lpbk_training_result[LPBK_VRET_LEN][LPBK_HORI_LEN][PHY_DQS_WIDTH] = {0};
	unsigned int rdqs_delay_idx, rdq_vref_idx;
	unsigned int curr_ptrcnt_even[PHY_DQS_WIDTH];
	unsigned int curr_ptrcnt_odd[PHY_DQS_WIDTH];
	unsigned int vref_opt,delay_opt;

	// First stop CK since asserting ld_cnt_reset will mess with CK
  stop_ck(0b00,0b11,ch);

	// Invert DQS since loopback inverts the clock
	#if LPBK_TRAIN_LPBK_INT
	  set_lpbk_patbuf(fsp,freq_ratio,freq_idx,1,ch);
	#else
	  set_lpbk_patbuf(fsp,freq_ratio,freq_idx,0,ch);
	#endif

	// DQS is always internal lpbk
	set_dqs_invert(0b1,ch);

	// Setup the pipelines for loopback
	for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
		// Set rfirst and nui
		rfirst     = 0b0 ;
		nui        = 0b1 ;
		apb_write_field_ch(M_RDPIPE_CONTROL[byte_idx][fsp],((nui<<1)|rfirst),ch);        // rfist as in lpbk dqs get invert

		// Transmit pipeline setup
		// Turn on the Transmit SDL
		apb_write_field_ch(M_OVR_WREN_EARLY[byte_idx],0b11,ch);
		// Oe can be kept zero since loopback is internal
		#if LPBK_TRAIN_LPBK_INT
			//apb_write_field_ch(M_OVR_TXDQSOE[byte_idx],0b01,ch);
			apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b01,ch);
		#else
			//apb_write_field_ch(M_OVR_TXDQSOE[byte_idx],0b11,ch);
			apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b11,ch);
		#endif

		apb_write_field_ch(M_OVR_TXDQSOE[byte_idx],0b01,ch);

		// Disable ODT since PBD has dependence on it
		apb_write_field_ch(M_OVR_DQODT[byte_idx],0b01,ch);
		apb_write_field_ch(M_OVR_DQSODT[byte_idx],0b01,ch);

		// Enable recevier
		apb_write_field_ch(M_OVR_RXDQSEN[byte_idx],0b11,ch);
		apb_write_field_ch(M_OVR_RXDQEN[byte_idx],0b11,ch);       // Enable DQ Rx

		// Enable receive SDL
		apb_write_field_ch(M_OVR_RDEN_EARLY[byte_idx],0b11,ch);

		// Override the DQS gating and keep DQS enabled
		acsr_write_field_ch(M_ANA_DQS_RD_EN_SEL[byte_idx],0b0,ch);
		apb_write_field_ch(M_OVR_RDQSEN[byte_idx],0b11,ch);

		/// Enable loopback for DQS
		acsr_write_field_ch(M_ANA_LPBK_SEL_DQS[byte_idx],0b1,ch);

		// Set the stretch value for DQS to zero
		apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp],0,ch);
	}

	//enable loopback for dq and DMI
	#if LPBK_TRAIN_LPBK_INT
		for (unsigned int i=0; i<((DQ_BITS_PER_SLICE-1) * (PHY_DQS_WIDTH-1)); i++) acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DQ[i], 0b1,ch);
		for (unsigned int i=0; i<PHY_DQS_WIDTH; i++)                           acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DMI[i], 0b1,ch);
	#else
		for (unsigned int i=0; i<((DQ_BITS_PER_SLICE-1) * (PHY_DQS_WIDTH-1)); i++) acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DQ[i], 0b0,ch);
		for (unsigned int i=0; i<PHY_DQS_WIDTH; i++)                           acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DMI[i], 0b0,ch);
	#endif

	// Set DAC kick to maximize margin
  #if SI_ENV
	  set_kick(LPBK_KICK,ch);
  #endif

	// Do a dummy pattern buffer enable to flush the pipelines.
	apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_DQRD_DATA, ch);
	wait_ptrn_done(ch);

  // Apply rd_cnt reset
  // Not needed
  // apply_rd_cnt_reset(loop_idx,0b00,0b11,ch);

  // Sweep cross-sel since it is not calibrated yet
  for (unsigned int cross_sel=CROSS_MIN;cross_sel<=CROSS_MAX;cross_sel++) {

    for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
      print_dbg("IPM:DQ_LPBK: loop_idx %d: Byte%d Using sdl %d  E:\n", loop_idx, byte_idx,LPBK_WDQ_SDL[ch][byte_idx][TRN_IDX_GBL]);
      set_wdq_delay_lpbk (LPBK_TRAIN_WDQ_NUI, LPBK_WDQ_SDL[ch][byte_idx][TRN_IDX_GBL],cross_sel,0,PHY_DQS_WIDTH-1,fsp,ch);
      set_wdqs_delay_lpbk(LPBK_TRAIN_WDQS_NUI,LPBK_WDQ_SDL[ch][byte_idx][TRN_IDX_GBL],cross_sel,0,PHY_DQS_WIDTH-1,fsp,ch);
    }

    apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_DQRD_DATA, ch);

    //2-D Sweep to get LPBK timing eye
    //Sweep Rx vref dac code
    for (unsigned int rdq_vref=LPBK_TRAIN_VREF_MIN;rdq_vref<=LPBK_TRAIN_VREF_MAX;rdq_vref+=LPBK_TRAIN_VREF_STEP) {
      set_rdq_vref_trn(rdq_vref,ch) ;
      rdq_vref_idx=(rdq_vref-LPBK_TRAIN_VREF_MIN) / LPBK_TRAIN_VREF_STEP ;

      // Sweep rdqs_delay.
      for (unsigned int rdqs_delay=LPBK_TRAIN_DELAY_MIN;rdqs_delay<=LPBK_TRAIN_DELAY_MAX;rdqs_delay+=LPBK_TRAIN_DELAY_STEP) {
        set_rdqs_delay(rdqs_delay, fsp, 0, PHY_DQS_WIDTH-1,ch);
        rdqs_delay_idx=(rdqs_delay-LPBK_TRAIN_DELAY_MIN) / LPBK_TRAIN_DELAY_STEP ;

        for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
          lpbk_pass[byte_idx]=1; // During oversample, if any iteration fails, we can reset this flag
        }

        // Set start and stop pointer based on ld_cnt
        // ld_cnt is reset to 1, so we can set cmpr_ptr to 5 always
        cmpr_ptr   =  5 ;

        for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
          // Updated expected data pointer based on ld_cnt. There is one for each value
          apb_write_field_ch(M_RDQ_PTRNBUF_START_PTR[byte_idx], cmpr_ptr,ch);
          apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_START_PTR[byte_idx],cmpr_ptr,ch);
          apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_STOP_PTR[byte_idx],cmpr_ptr+3,ch);
        }

        // Iterate oversample count
        for (unsigned int itr_idx=0; itr_idx<LPBK_OVRSAMPLE_CNT; itr_idx++) {
          // Reset and release the fifo pointers
          reset_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
          //reset_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
          reset_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch) ;

          reset_release_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
          reset_release_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

          // Do loopback by enabling the pattern buffer
          apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_DQRD_DATA, ch);
          wait_ptrn_done(ch);
          delay(t_PATBUF_LPBK_DLY);

          read_rdq_patbuf_cmpr(&data_fail, ch);
          for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
            curr_ptrcnt_even[byte_idx] =      apb_read_field_ch(M_RDFIFO_WRITE_POINTER_EVEN[byte_idx], ch);
            curr_ptrcnt_odd[byte_idx] =       apb_read_field_ch(M_RDFIFO_WRITE_POINTER_ODD[byte_idx], ch);

            // If iteration failed, then reset the pass flag
            if ( (BIT_GET(data_fail,byte_idx)==0b1)  || (curr_ptrcnt_even[byte_idx]!=4) || (curr_ptrcnt_odd[byte_idx]!=4)) {
              lpbk_pass[byte_idx]=0;
            }
            //Debug information
            #if IPM_DBG_LPBK_EXTRA
              for (unsigned int dq_idx=0;dq_idx<PHY_DQ_PER_DQS;dq_idx++) {
                unsigned int read_data = apb_read_field_ch(M_RDQ_PTRNBUF_DQ[byte_idx][cmpr_ptr][dq_idx],ch);
                unsigned int exp_data  = apb_read_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][cmpr_ptr][dq_idx],ch);
                print_dbg("IPM:DQ_LPBK: Byte%d DQbit%d Cross %d  Rdqvref %d Rdqsdelay %d Readdata 0x%x Expdata 0x%x DataFail %d ptrcnt_even %d ptrcnt_odd %d E:\n",
                  byte_idx,dq_idx, cross_sel, rdq_vref,rdqs_delay,read_data,exp_data,BIT_GET(data_fail,byte_idx),curr_ptrcnt_even[byte_idx],curr_ptrcnt_odd[byte_idx]);

              }
            #endif
          } // for byte_idx
        } // ovrsample
        #if IPM_DBG_LPBK_EXTRA
          print_dbg("\n");
        #endif

        // Update lpbk eye array
        for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
          // Array stores fail flag not pass flag
          lpbk_training_result[rdq_vref_idx][rdqs_delay_idx][byte_idx]=lpbk_pass[byte_idx] ? 0 :1 ;
        }

      } // for rdqs_delay
    } // for rdq_vref

    // 2-d Sweep is over. Now try to find center and store results
    for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
      unsigned int pass_size=0;

      find_optimal_com( (uint8_t *)lpbk_training_result, PHY_DQS_WIDTH,
            byte_idx, byte_idx,
            LPBK_TRAIN_VREF_MIN, LPBK_TRAIN_VREF_MAX,LPBK_TRAIN_VREF_STEP,
            LPBK_TRAIN_DELAY_MIN,LPBK_TRAIN_DELAY_MAX,LPBK_TRAIN_DELAY_STEP,
            LPBK_TRAIN_PASS_REGION_THLD,LPBK_TRAIN_PASS_REGION_DIFF,
            (IPM_DBG_LPBK && IPM_DBG_FIND_OPT) | (1<<4),
            // 1, // debug = 1
            &vref_opt, &delay_opt, &pass_size);

      print_dbg("Findopt result: Byte%d Cross %d Vrefopt %d Delayopt %d Passize %d  E:\n",byte_idx,cross_sel,vref_opt,delay_opt,pass_size);
      if ((vref_opt==LPBK_TRAIN_VREF_MIN) && (delay_opt==LPBK_TRAIN_DELAY_MIN)) {
        print_err("IPM:DQ_LPBK: ERROR! DQ Loopback failed for byte%d. Unable to find eye opening E: \n",byte_idx);
      } else {
        if (pass_size > LPBK_PASS_SIZE_OPT[ch][byte_idx][TRN_IDX_GBL]) { // If both cross=0 and cross=1 pass then choose the one with bigger window
          LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=delay_opt;
          LPBK_VREF_OPT[ch][byte_idx][TRN_IDX_GBL]=vref_opt;
          LPBK_CROSS_OPT[ch][byte_idx][TRN_IDX_GBL]=cross_sel;
          LPBK_PASS_SIZE_OPT[ch][byte_idx][TRN_IDX_GBL]=pass_size;
        }
      }
    }
  }

	// Print out the optima
	for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
		print_dbg("IPM:DQ_LPBK: LPBK Results Ch%d Byte%d LPBK_VREF_OPT %d LPBK_DELAY_OPT %d  LPBK_CROSS_OPT %d Pass Size Opt %d  E:\n",
			ch,byte_idx,LPBK_VREF_OPT[ch][byte_idx][TRN_IDX_GBL],LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL],LPBK_CROSS_OPT[ch][byte_idx][TRN_IDX_GBL],LPBK_PASS_SIZE_OPT[ch][byte_idx][TRN_IDX_GBL]);
	}

	// Restore pipeline defaults after loopback
	reset_dqbyte_controls(0,PHY_DQS_WIDTH-1,ch);

	// set dqs_invert as per input args
  if(RDQS_DLL == UI_0P5) {
		print_dbg("IPM:DQ_LPBK: Reverting to 0P5 DLL setting  E:\n");
		set_dqs_invert(0b0,ch);
  } else if(RDQS_DLL == UI_1P5) {
		print_dbg("IPM:DQ_LPBK: Reverting to 1P5 DLL setting  E:\n");
		set_dqs_invert(0b1,ch);
  } else {
    print_err("IPM:DQ_LPBK: ERROR! Invalid RDQS DLL setting %d\n",RDQS_DLL);
  }

	// Set the kick back to its default value
	set_kick(CSR_DQDM_RX_DQ_FE_DAC_KICK_HB,ch);

	// Restart CK
	start_ck(0b11,0b11,ch);
}

void do_dq_patbuf_lpbk_bypass (unsigned int fsp,unsigned int  freq_ratio,unsigned int  freq_idx,unsigned int ch) {
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=6;
    LPBK_VREF_OPT[ch][byte_idx][TRN_IDX_GBL]=100;
    LPBK_CROSS_OPT[ch][byte_idx][TRN_IDX_GBL]=1;
    LPBK_PASS_SIZE_OPT[ch][byte_idx][TRN_IDX_GBL]=8; // Dummy number
    print_dbg("IPM:DQ_LPBK: LPBK Results Ch%d Byte%d LPBK_VREF_OPT %d LPBK_DELAY_OPT %d  LPBK_CROSS_OPT %d Pass Size Opt %d  E:\n",
                ch,byte_idx,LPBK_VREF_OPT[ch][byte_idx][TRN_IDX_GBL],LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL],
                LPBK_CROSS_OPT[ch][byte_idx][TRN_IDX_GBL],LPBK_PASS_SIZE_OPT[ch][byte_idx][TRN_IDX_GBL]);
  }
}

void set_rdq_vref_trn_perbyte(
	unsigned int dac_code,
	unsigned int byte_start,
	unsigned int byte_end,
	unsigned int ch) {

	for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
		acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_R[byte_idx], dac_code,ch);
		acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_DMI_F[byte_idx], dac_code,ch);

		for (unsigned int idx=(byte_idx*(PHY_DQ_PER_DQS-1)); idx<(PHY_DQ_PER_DQS-1+(PHY_DQ_PER_DQS-1)*byte_idx); idx++) {
			acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_R[idx], dac_code,ch);
			acsr_write_field_ch(M_ANA_DQ_FE_DAC_MAIN_F[idx], dac_code,ch);
		}
	}
} // set_rdq_vref_trn

//------------------------------------------------------------------------
// Find transition point in the presence of noise/dither etc..
//------------------------------------------------------------------------
void find_optimal_sdlcross_com(
	unsigned int *result_ar,
	unsigned int col_width,
	unsigned int byte_idx,
	unsigned int dbg,
	unsigned int ch,
	unsigned int *cross_th1,
	unsigned int *cross_th2,
	unsigned int *nui_incr,
	unsigned int *wrp_code ) {

	unsigned int result_size=0;
	unsigned int curr_result;
	unsigned int curr_byte_idx;
	unsigned int curr_cross_idx;
	unsigned int curr_ch_idx;
	int tp[2][2]; //[#cross][#tp]
	unsigned int pattern[3]={0};

	for (unsigned int cross_sel=CROSS_MIN;cross_sel<=CROSS_MAX;cross_sel++) {
		unsigned int pat_start_found[3]={0};
		unsigned int pat_end_found[3]={0};
		unsigned int pat_start_idx[3]={0};
		unsigned int pat_end_idx[3]={0};
		unsigned int look_for_pat[3]={0};

		for (unsigned int delay=SDL_MIN;delay<=SDL_MAX;delay++) {
			curr_ch_idx=(col_width)*(CROSS_MAX+1)*(SDL_MAX+1)*ch;
			curr_byte_idx = (CROSS_MAX+1)*(SDL_MAX+1)*byte_idx;
			curr_cross_idx= (SDL_MAX+1)*cross_sel;
			curr_result=result_ar[curr_ch_idx+curr_byte_idx+curr_cross_idx+delay];

			// Mod: added pat_start_found condition
			if ((look_for_pat[0]==0) && (curr_result !=0) && (pat_start_found[0]==0)) {
				look_for_pat[0]=1;
				pattern[0]=curr_result;
			} else if ((look_for_pat[0]==0) && (curr_result ==0) && (pat_start_found[0]==0) && (delay==SDL_MIN)) {
				// this is for if we start with a zero/metastability point
				// In that case mark this as the first transition and start looking for the next transition
				pat_start_found[0]=1;
				pat_end_found[0]=1;
				pat_start_idx[0]=delay;
				pat_end_idx[0]=delay;
				look_for_pat[0]=1;
			}

			// Find transition of first pattern
			if (look_for_pat[0]==1) {
				if ((pat_start_found[0]==0) && (curr_result==pattern[0]))  {
					pat_start_found[0]=1;
					pat_start_idx[0]=delay;
				}
				if ((pat_start_found[0]==1) && (pat_end_found[0]==1) && (curr_result!=0)) {
					look_for_pat[0]=0;
					look_for_pat[1]=1;
					pattern[1]=curr_result;
				}
				if ((pat_start_found[0]==1) && (pat_end_found[0]==0) && (curr_result!=pattern[0])) {
					pat_end_found[0]=1;
					pat_end_idx[0]=delay-1;
				}
			}

			// Find transition of 2nd pattern.
			if (look_for_pat[1]==1) {
				if ((pat_start_found[1]==0) && (curr_result==pattern[1]))  {
					pat_start_found[1]=1;
					pat_start_idx[1]=delay;
				}
				if ((pat_start_found[1]==1) && (pat_end_found[1]==1) && (curr_result!=0)) {
					look_for_pat[1]=0;
					look_for_pat[2]=1;
					pattern[2]=curr_result;
				}
				if ((pat_start_found[1]==1) && (pat_end_found[1]==0) && (curr_result!=pattern[1]))  {
					pat_end_found[1]=1;
					pat_end_idx[1]=delay-1;
				} else if ((pat_start_found[1]==1) && (pat_end_found[1]==0) && (delay==SDL_MAX)) {
					pat_end_found[1]=1;
					pat_end_idx[1]=delay;
				}

			}

			// Find transition from 3 -> 0/End
			if (look_for_pat[2]==1) {
				if ((pat_start_found[2]==0) && (curr_result==pattern[2]))  {
					pat_start_found[2]=1;
					pat_start_idx[2]=delay;
				}
				if ((pat_start_found[2]==1) && (pat_end_found[2]==0) && (curr_result!=pattern[2])) {
					pat_end_found[2]=1;
					pat_end_idx[2]=delay-1;
				} else if ((pat_start_found[2]==1) && (pat_end_found[2]==0) && (delay==SDL_MAX)) {
					pat_end_found[2]=1;
					pat_end_idx[2]=delay;
				}
				if ((pat_start_found[2]==1) && (pat_end_found[2]==1)) {
					look_for_pat[2]=0;
				}
			}
		}

		// Figure out transition points
		// Add special case when transition/metastability happens on max code
		if (dbg==1) {
			print_dbg("IPM:SDLCROSS: Byte%d Cross %d pat1 start %d stop %d pat2 start %d stop %d pat3 start %d stop %d   E:\n",byte_idx, cross_sel, pat_start_idx[0],pat_end_idx[0],pat_start_idx[1],pat_end_idx[1],pat_start_idx[2],pat_end_idx[2]);
		}
		if ((pat_end_found[0]==1) && (pat_start_found[1]==1)) {
			tp[cross_sel][0]=(pat_end_idx[0]+pat_start_idx[1])/2;
		} else if ( (pat_end_found[0]==1) && (pat_start_found[1]==0) && (pat_end_idx[0]>= (SDL_MAX-2))) {
			tp[cross_sel][0]=(pat_end_idx[0]+CROSS_MAX)/2;
		} else {
			print_err("IPM:SDLCROSS: ERROR! Could not find first transition point  E:\n");
			print_err("IPM:SDLCROSS: pat_end_found[0]=%d pat_start_found[1]=%d pat_end_idx[0]=%d SDL_MAX-2=%d E:\n",
										  pat_end_found[0],pat_start_found[1],pat_end_idx[0],(SDL_MAX-2) );
		}

		if ((pat_end_found[1]==1) && (pat_start_found[2]==1)) {
			tp[cross_sel][1]=(pat_end_idx[1]+pat_start_idx[2])/2;
		} else {
			tp[cross_sel][1]=-1;
		}

	} // for

	//-----------------------------------------------------------------
	// Using the transition points, figure out the sdl_wrp_code
	// If there are 2 transition points then use that as the wrap code
	// If not use the spacing between tp of cross=0 and cross=1
	//-----------------------------------------------------------------
  unsigned int wrp_code_loc=0;
	if (tp[0][0] > tp[1][0]) {
		wrp_code_loc = (tp[0][0]-tp[1][0])*2;
	} else if (tp[0][0] < tp[1][0]) {
		wrp_code_loc = (tp[1][0]-tp[0][0])*2;
	} else {
		print_err("IPM:SDLCROSS: ERROR! Unknown transition point condition reached.Cross_th1 %d Cross_th2 %d  E:\n ",tp[0][0],tp[1][0]);
	}
	if (wrp_code_loc > SDL_MAX) {
			wrp_code_loc=SDL_MAX;
	}
	if (dbg==1) {
		print_dbg("IPM:SDLCROSS: Tp1 %d Tp2 %d SDLcode %d  E:\n",tp[0][0],tp[1][0],wrp_code_loc);
	}

  //-----------------------------------------------------------------------------
  // Find the nui crossing
  //------------------------------------------------------------------------------
	unsigned int cross_th1_loc = tp[0][0];
	unsigned int cross_th2_loc = tp[1][0];
	unsigned int xovr_out_curr=0;
	unsigned int xovr_out_prev=0;
	unsigned int cross_out=0;
	unsigned int nui_incr_loc=0;

	for (unsigned int sdl_delay=SDL_MIN; sdl_delay <= SDL_MAX; sdl_delay++) {
		curr_ch_idx=(col_width)*(CROSS_MAX+1)*(SDL_MAX+1)*ch;
		cross_out = find_cross_sel_com(sdl_delay,wrp_code_loc, cross_th1_loc,cross_th2_loc);
		curr_byte_idx = (CROSS_MAX+1)*(SDL_MAX+1)*byte_idx;
		curr_cross_idx= (SDL_MAX+1)*cross_out;
		xovr_out_curr=result_ar[curr_ch_idx+curr_byte_idx+curr_cross_idx+sdl_delay];
		if (xovr_out_curr== (xovr_out_prev+1)) {
			nui_incr_loc=sdl_delay;
		}
		if (dbg==1) {
		print_dbg("IPM:SDLCROSS: Sdl_code %d cross_sel %d Xovr_out %d NUI Incr %d  E:\n",sdl_delay,cross_out,xovr_out_curr,nui_incr_loc);
		}
		xovr_out_prev=xovr_out_curr;
	}

	if (dbg==1) {
		print_dbg("IPM:SDLCROSS: Cros_sel %d Tp1 %d Tp2 %d  E:\n",0,tp[0][0],tp[0][1]);
		print_dbg("IPM:SDLCROSS: Cros_sel %d Tp1 %d Tp2 %d  E:\n",1,tp[1][0],tp[1][1]);
	}

	// Figure out pass/fail flag. pattern[3] should contain unique entries. If not then transition data
	// is incorrect.
	if ( (pattern[0]==pattern[1]) || (pattern[1]==pattern[2]) || (pattern[0]==pattern[2])) { // Incorrect
		*cross_th1=0;
		*cross_th2=0;
		*wrp_code=0;
		*nui_incr=0;
	} else { // Correct
		*cross_th1=cross_th1_loc;
		*cross_th2=cross_th2_loc;
		*wrp_code=wrp_code_loc;
		*nui_incr=nui_incr_loc;
	}
}

//------------------------------------------------------------------------------
// lpbk Pattern buffer programming
//------------------------------------------------------------------------------
void set_sdlcross_patbuf(
  unsigned int fsp,
  unsigned int freq_ratio,
  unsigned int freq_idx,
  unsigned int invert,
  unsigned int ch) {

  unsigned int rdcs_val;
  unsigned int wrcs_val;

  unsigned int  write_dq_packed  [PHY_DQS_WIDTH][PHY_DQ_PER_DQS];
  unsigned int  write_dq_packed_lshift[PHY_DQS_WIDTH][PHY_DQ_PER_DQS];
  unsigned int  write_dq_packed_rshift[PHY_DQS_WIDTH][PHY_DQ_PER_DQS];
  unsigned int  write_dq_packed_rshift2[PHY_DQS_WIDTH][PHY_DQ_PER_DQS];

  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    for (unsigned int bit_idx=0;bit_idx< PHY_DQ_PER_DQS; bit_idx++) {
      write_dq_packed[byte_idx][bit_idx]=0;
      write_dq_packed_lshift[byte_idx][bit_idx]=0;
      write_dq_packed_rshift[byte_idx][bit_idx]=0;
      write_dq_packed_rshift2[byte_idx][bit_idx]=0;
    }
  }

  // Setup the unshifted version
  for (unsigned int burst_idx=0;burst_idx<SDL_TRAIN_BL;burst_idx++) {
	  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    	for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
      		BIT_SET(write_dq_packed[byte_idx][bit_idx],burst_idx,BIT_GET(WRDQ_TRAIN_PAT_LPBK[burst_idx][byte_idx],bit_idx));
		}
	  }
  }

  // Setup the left/right shifted version
  for (unsigned int burst_idx=0;burst_idx<SDL_TRAIN_BL;burst_idx++) for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
		// Lshift by 1
		if (burst_idx==0) {
			BIT_SET(write_dq_packed_lshift[byte_idx][bit_idx],burst_idx,0b0);
		} else {
			BIT_SET(write_dq_packed_lshift[byte_idx][bit_idx],burst_idx,BIT_GET(write_dq_packed[byte_idx][bit_idx],burst_idx-1));
		}
		// Rshift by 1
		if (burst_idx==(SDL_TRAIN_BL-1)) {
			BIT_SET(write_dq_packed_rshift[byte_idx][bit_idx],burst_idx,0b0);
		} else {
			BIT_SET(write_dq_packed_rshift[byte_idx][bit_idx],burst_idx,BIT_GET(write_dq_packed[byte_idx][bit_idx],burst_idx+1));
		}
		// Rshift by 2
		if ((burst_idx==(SDL_TRAIN_BL-1)) || (burst_idx==(SDL_TRAIN_BL-2))) {
			BIT_SET(write_dq_packed_rshift2[byte_idx][bit_idx],burst_idx,0b0);
		} else {
			BIT_SET(write_dq_packed_rshift2[byte_idx][bit_idx],burst_idx,BIT_GET(write_dq_packed[byte_idx][bit_idx],burst_idx+2));
		}
    }
  }

  // DQ pattern buffer programming
  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {

    // Strech value of WDQS set it to zero.
    apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp],0,ch);

    // Program the write dq pattern buffer
    // Ref from WR DQ
    for (unsigned int row_idx=0;row_idx<=(SDL_TRAIN_BL/2);row_idx++) {
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b1,ch);  //Assert wdqs for BL/2*tck
      apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }
    for (unsigned int row_idx=(SDL_TRAIN_BL/2);row_idx<=15;row_idx++) {
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b0,ch);  //De-assert wdqs
      apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }

    for (unsigned int bit_idx=0;bit_idx<PHY_DQ_PER_DQS;bit_idx++) {

			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][0][bit_idx], BITS_GET(write_dq_packed[byte_idx][bit_idx],1,0),ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][1][bit_idx], BITS_GET(write_dq_packed[byte_idx][bit_idx],3,2),ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][2][bit_idx], BITS_GET(write_dq_packed[byte_idx][bit_idx],5,4),ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][3][bit_idx], 0,ch);
      if(invert == 1){
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][4][bit_idx], ~BITS_GET(write_dq_packed_lshift[byte_idx][bit_idx],1,0),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][5][bit_idx], ~BITS_GET(write_dq_packed_lshift[byte_idx][bit_idx],3,2),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][6][bit_idx], ~BITS_GET(write_dq_packed_lshift[byte_idx][bit_idx],5,4),ch);

          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][7][bit_idx], ~BITS_GET(write_dq_packed_rshift[byte_idx][bit_idx],1,0),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][8][bit_idx], ~BITS_GET(write_dq_packed_rshift[byte_idx][bit_idx],3,2),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][9][bit_idx], ~BITS_GET(write_dq_packed_rshift[byte_idx][bit_idx],5,4),ch);

          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][10][bit_idx], ~BITS_GET(write_dq_packed_rshift2[byte_idx][bit_idx],1,0),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][11][bit_idx], ~BITS_GET(write_dq_packed_rshift2[byte_idx][bit_idx],3,2),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][12][bit_idx], ~BITS_GET(write_dq_packed_rshift2[byte_idx][bit_idx],5,4),ch);

      } else {

          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][4][bit_idx], BITS_GET(write_dq_packed_lshift[byte_idx][bit_idx],1,0),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][5][bit_idx], BITS_GET(write_dq_packed_lshift[byte_idx][bit_idx],3,2),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][6][bit_idx], BITS_GET(write_dq_packed_lshift[byte_idx][bit_idx],5,4),ch);

          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][7][bit_idx], BITS_GET(write_dq_packed_rshift[byte_idx][bit_idx],1,0),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][8][bit_idx], BITS_GET(write_dq_packed_rshift[byte_idx][bit_idx],3,2),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][9][bit_idx], BITS_GET(write_dq_packed_rshift[byte_idx][bit_idx],5,4),ch);

          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][10][bit_idx], BITS_GET(write_dq_packed_rshift2[byte_idx][bit_idx],1,0),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][11][bit_idx], BITS_GET(write_dq_packed_rshift2[byte_idx][bit_idx],3,2),ch);
          apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][12][bit_idx], BITS_GET(write_dq_packed_rshift2[byte_idx][bit_idx],5,4),ch);
      }
    }

    apb_write_field_ch(M_WDQ_PTRNBUF_START_PTR[byte_idx],0,ch);
    apb_write_field_ch(M_WDQ_PTRNBUF_STOP_PTR[byte_idx],3,ch);

  }
}

void normalize_trans_data(unsigned int ch){
	int start_code=2;

	for ( int byte=0;byte<PHY_DQS_WIDTH;byte++) {
		int delta = start_code-XOVR_TRANS_DQ[ch][byte][0][0];
		for ( int cross=0;cross<=1;cross++) {
			for (int sdl=SDL_MIN;sdl<=SDL_MAX;sdl++) {
				if (XOVR_TRANS_DQ[ch][byte][cross][sdl]>0) {
					XOVR_TRANS_DQ[ch][byte][cross][sdl]=XOVR_TRANS_DQ[ch][byte][cross][sdl]+delta;
				}
				if (XOVR_TRANS_DQ[ch][byte][cross][sdl]<0) {
					print_err("IPM:SDLCROSS:NORM: ERROR! Negative trans data is illegal. Ch%d Cross%d Byte%d SDL %d Trans %d\n",
							ch,cross,byte,sdl,XOVR_TRANS_DQ[ch][byte][cross][sdl]);
				}
			}
		}
	}

	// Print results
	for ( int cross=0;cross<=1;cross++) {
		for (int sdl=SDL_MIN;sdl<=SDL_MAX;sdl++) {
			print_dbg("IPM:SDLCROSS:NORM: Ch%d Cross %d sdl %d Pass0 %d Pass1 %d Pass2 %d Pass3 %d \n",
					ch,cross,sdl,XOVR_TRANS_DQ[ch][0][cross][sdl],XOVR_TRANS_DQ[ch][1][cross][sdl],
							  XOVR_TRANS_DQ[ch][2][cross][sdl],XOVR_TRANS_DQ[ch][3][cross][sdl]);
		}
	}
}

//------------------------------------------------------------------------------------------
// Function to shift trans data.
//------------------------------------------------------------------------------------------
void shift_trans_data(
	unsigned int *tran_in,
	int byte_idx_in,
	int byte_idx_out,
	int shift_val,
	int wrp_code,
	unsigned int ch,
	unsigned int *tran_out
) {
	int tran_prev[2][SDL_MAX+1]={0};
	int tran_next[2][SDL_MAX+1]={0};

	//Invert the shift
	int curr_data=0;

	// First create the left shifted and right shifter versions of the data
	for ( int cross=0;cross<=1;cross++) {
		int arr_ch_idx_in=(PHY_DQS_WIDTH)*(CROSS_MAX+1)*(SDL_MAX+1)*ch;
		int arr_byte_idx_in=(CROSS_MAX+1)*(SDL_MAX+1)*byte_idx_in;
		int arr_cross_idx=(SDL_MAX+1)*cross;
		int arr_idx_in=arr_ch_idx_in+arr_byte_idx_in+arr_cross_idx;

		for (int sdl=SDL_MIN;sdl<=SDL_MAX;sdl++) {
			curr_data=tran_in[arr_idx_in+sdl];
			if (curr_data==0) {
				tran_prev[cross][sdl]=0;
				tran_next[cross][sdl]=0;
			} else if (curr_data==1) {
				tran_prev[cross][sdl]=-1;
				tran_next[cross][sdl]=2;
			} else if (curr_data==2) {
				tran_prev[cross][sdl]=1;
				tran_next[cross][sdl]=3;
			} else if (curr_data==3) {
				tran_prev[cross][sdl]=2;
				tran_next[cross][sdl]=4;
			} else if (curr_data==4) {
				tran_prev[cross][sdl]=3;
				tran_next[cross][sdl]=5;
			} else {
				print_err("IPM:SDLCROSS: ERROR! Unknown trans data. Cross %d sdl %d Data %d \n", cross,sdl,curr_data);
			}
		}
	}


	//Figure out the shifted data based on shift amount
	for (int cross=0;cross<=1;cross++) {
		int arr_ch_idx_in=(PHY_DQS_WIDTH)*(CROSS_MAX+1)*(SDL_MAX+1)*ch;
		int arr_byte_idx_in=(CROSS_MAX+1)*(SDL_MAX+1)*byte_idx_in;

		int arr_ch_idx_out=(PHY_DQS_WIDTH)*(CROSS_MAX+1)*(SDL_MAX+1)*ch;
		int arr_byte_idx_out=(CROSS_MAX+1)*(SDL_MAX+1)*byte_idx_out;
		int arr_cross_idx=(SDL_MAX+1)*cross;

		int arr_idx_in=arr_ch_idx_in+arr_byte_idx_in+arr_cross_idx;
		int arr_idx_out=arr_ch_idx_out+arr_byte_idx_out+arr_cross_idx;

		for (int sdl=SDL_MIN;sdl<=SDL_MAX;sdl++) {
			int sdl_shift=sdl+shift_val;
			// If it is within existing data range its a simple assign
			if ((sdl_shift>=SDL_MIN) && (sdl_shift<=wrp_code)) {
				tran_out[arr_idx_out+sdl]=tran_in[arr_idx_in+sdl_shift];
			} else if (sdl_shift < SDL_MIN) {
				sdl_shift=sdl_shift+wrp_code+1;
				tran_out[arr_idx_out+sdl]=tran_prev[cross][sdl_shift];
			} else if (sdl_shift > wrp_code) {
				sdl_shift=sdl_shift-wrp_code-1;
				tran_out[arr_idx_out+sdl]=tran_next[cross][sdl_shift];
			}
			if ((tran_out[arr_idx_out+sdl] <0) || (tran_out[arr_idx_out+sdl]>4)) {
				print_err("IPM:SDLCROSS: ERROR! Incorrect data encountered while shifting. Cross %d sdl %d sdl_shift %d Data %d \n",
				cross,sdl,sdl_shift,tran_out[arr_idx_out+sdl]);
			}
		}
	}

}

void set_rden_sdlcross(unsigned int ch) {

	for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
		// Extra delay in rden path. PBD intrinsic delay
		// This will result in thresholds moving to the left
		int rden_extra_code =(RDEN_EXTRA_DSTDLY*SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL])/TRN_SCN[TRN_IDX_GBL].ui;
		XOVR_THLD_RDEN[ch][0][byte_idx][TRN_IDX_GBL]=XOVR_THLD_WDQ[ch][0][byte_idx][TRN_IDX_GBL]-rden_extra_code;
		XOVR_THLD_RDEN[ch][1][byte_idx][TRN_IDX_GBL]=XOVR_THLD_WDQ[ch][1][byte_idx][TRN_IDX_GBL]-rden_extra_code;
		//XOVR_THLD_RDEN[ch][2][byte_idx][TRN_IDX_GBL]=XOVR_THLD_WDQ[ch][2][byte_idx][TRN_IDX_GBL]-extra_code;

		// If cross-sel0 threhold is negative, we need to wrap it around and later account for this wrap around
		// in the xovr data
		if (XOVR_THLD_RDEN[ch][0][byte_idx][TRN_IDX_GBL] < 0) {
			XOVR_THLD_RDEN[ch][0][byte_idx][TRN_IDX_GBL]=XOVR_THLD_RDEN[ch][0][byte_idx][TRN_IDX_GBL]+SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]+1;
		}
		// If cross-sel1 threhold is negative, we need to wrap it around and later account for this wrap around
		// in the xovr data
		if (XOVR_THLD_RDEN[ch][1][byte_idx][TRN_IDX_GBL] < 0) {
			XOVR_THLD_RDEN[ch][1][byte_idx][TRN_IDX_GBL]=XOVR_THLD_RDEN[ch][1][byte_idx][TRN_IDX_GBL]+SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]+1;
		}
	}

	// Generate trans data by shiting the DQ code
	for (unsigned int byte_idx=0;byte_idx< PHY_DQS_WIDTH;byte_idx++) {
		int rden_extra_code = (RDEN_EXTRA_DSTDLY*SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL])/TRN_SCN[TRN_IDX_GBL].ui;
		#if IPM_DBG_SDLCROSS
		print_dbg("Byte%d Rden Extra delay %d Wrpcode %d UI %d Extracode %d \n",byte_idx,RDEN_EXTRA_DSTDLY,SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],TRN_SCN[TRN_IDX_GBL].ui,rden_extra_code);
		#endif
		shift_trans_data(XOVR_TRANS_DQ,byte_idx,byte_idx,rden_extra_code,SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],ch,XOVR_TRANS_RDEN);
	}

	//print out the shifted array
	#if IPM_DBG_SDLCROSS
	for (unsigned int cross=0;cross<=1;cross++) {
		for (unsigned int sdl_delay=SDL_MIN;sdl_delay<=SDL_MAX;sdl_delay++) {
			print_dbg("IPM:RDEN_SDLCROSS: Cross_sel %02d Rdendelay %02d  Pass0 %d Pass1 %d Pass2 %d Pass3 %d\n",
				cross,sdl_delay,
				XOVR_TRANS_RDEN[ch][0][cross][sdl_delay],XOVR_TRANS_RDEN[ch][1][cross][sdl_delay],
				XOVR_TRANS_RDEN[ch][2][cross][sdl_delay],XOVR_TRANS_RDEN[ch][3][cross][sdl_delay]);
		}
		print_dbg("\n\n");
	}
	#endif
}

void set_ca_sdlcross(unsigned int ch) {

	// Extra SRC delay in CA path.
	// This will result in thresholds moving to the right
	int ca_extra_code;
	int ref_dq;
	if (ch==0) {
		ca_extra_code=(CA_EXTRA_SRCDLY_CH0*SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL])/TRN_SCN[TRN_IDX_GBL].ui;
		ref_dq=2;
	} else {
		ca_extra_code=(CA_EXTRA_SRCDLY_CH1*SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL])/TRN_SCN[TRN_IDX_GBL].ui;
		ref_dq=2;
	}
	XOVR_THLD_CA[ch][0][0][TRN_IDX_GBL]=XOVR_THLD_WDQ[ch][0][ref_dq][TRN_IDX_GBL]+ca_extra_code;
	XOVR_THLD_CA[ch][1][0][TRN_IDX_GBL]=XOVR_THLD_WDQ[ch][1][ref_dq][TRN_IDX_GBL]+ca_extra_code;
	//XOVR_THLD_RDEN[ch][2][byte_idx][TRN_IDX_GBL]=XOVR_THLD_WDQ[ch][2][byte_idx][TRN_IDX_GBL]-extra_code;

	// If cross-sel1 threhold is > SDL_MAX, we need to wrap it around and later account for this wrap around
	// in the xovr data
	if (XOVR_THLD_CA[ch][1][0][TRN_IDX_GBL] > SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]) {
		XOVR_THLD_CA[ch][1][0][TRN_IDX_GBL]=XOVR_THLD_CA[ch][1][0][TRN_IDX_GBL]-SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]-1;
	}
	print_dbg(" Extracode %d \n",ca_extra_code);
	// If cross-sel0 threhold is > SDL_MAX something is amiss. There has to be a really large source delay for this to happen.
	// Based on timing reports this shud not happen.
	if (XOVR_THLD_CA[ch][0][0][TRN_IDX_GBL] > SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]) {
		print_err("IPM:CROSSEL: ERROR! Got > SDL MAX thresholds for CA cross_th1 %d. Check cross_sel data \n",XOVR_THLD_CA[ch][0][0][TRN_IDX_GBL]);
	}

	// Generate trans data by shifting the DQ code. Using DQ0 as reference
	// Since srcdelay of CA is > than srcdelay of DQ, the shift is negative
	shift_trans_data(XOVR_TRANS_DQ,ref_dq,0,-1*ca_extra_code,SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL],ch,XOVR_TRANS_CA);

	//print out the shifted array
	#if IPM_DBG_SDLCROSS
	for (unsigned int cross=0;cross<=1;cross++) {
		for (unsigned int sdl_delay=SDL_MIN;sdl_delay<=SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL];sdl_delay++) {
			print_dbg("IPM:CA_SDLCROSS: Cross_sel %d CA delay %02d  Pass0 %d  \n",
				cross,sdl_delay, XOVR_TRANS_CA[ch][0][cross][sdl_delay]);
		}
		print_dbg("\n\n");
	}
	#endif
}

//---------------------------------------------------------------------------------
// Take the transition data obtained from do_cross_sel_training and post process
// it. Generate ca and rden transition data
//---------------------------------------------------------------------------------
unsigned int cross_sel_postprocess(unsigned int ch) {

  unsigned int cross_th1=0;
  unsigned int cross_th2=0;
  unsigned int nui_incr=0;
  unsigned int sdl_wrap_code=0;
	unsigned int cross_sel_pass = 1;

	// Normalize XOVR_TRANS_DQ to 2-3-4 pattern so that the cross-sel data is
	// independent of loopback settings
  // Not sure if this is needed anymore
	// normalize_trans_data(ch);


	// Find sdl wrap code and cross-sel thresholds for each byte
	for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
		unsigned int cross_th1=0,cross_th2=0,sdl_wrap_code=0,nui_incr=0;
		find_optimal_sdlcross_com(XOVR_TRANS_DQ,PHY_DQS_WIDTH,
								byte_idx,IPM_DBG_SDLCROSS_OPT, ch,
								&cross_th1,&cross_th2,&nui_incr,&sdl_wrap_code);

		if ( (cross_th1==0) && (cross_th2==0) && (sdl_wrap_code==0)) {
			cross_sel_pass=0;
		}
		SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]=sdl_wrap_code;
		XOVR_THLD_WDQ[ch][0][byte_idx][TRN_IDX_GBL]=cross_th1;
		XOVR_THLD_WDQ[ch][1][byte_idx][TRN_IDX_GBL]=cross_th2;
		XOVR_THLD_WDQ[ch][2][byte_idx][TRN_IDX_GBL]=nui_incr;
		if (SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL] < 15) {
			print_err("IPM:CROSSEL: ERROR! SDL Wrp code %d too small. Look at cross sel data  E:\n",
			SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]);
		}
	}

	if (cross_sel_pass==1) {
		// Average the wraparound code across bytes if requested
		if (SDLCROSS_MERGE_WRPCODE==1) {
			unsigned int wrp_code_total=0,wrp_code_avg=0;
			for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
				wrp_code_total=wrp_code_total+SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL];
			}
			wrp_code_avg=wrp_code_total/PHY_DQS_WIDTH;
			for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
				SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]=wrp_code_avg;
			}
		}

		// Let CA group also have the same wrp code
		SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]=SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL];

		//RDEN has additional delay compared to WDQ clock path. So, need to adjust/shift the thresholds
		//and transition data to account for the delay
		set_rden_sdlcross(ch);

		//CA group has additional delay compared to WDQ0 clock path. So, adjust/shift the thresholds
		// and also shift transition data to account for the delay
		set_ca_sdlcross(ch);

		//Print results
		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {

			print_info("IPM:CROSSEL: WDQ Result Ch%d Byte%d SDL_WRP_CODE_OPT %02d Crossth1 %02d Crossth2 %02d  E:\n",
					ch,byte_idx, SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],
					XOVR_THLD_WDQ[ch][0][byte_idx][TRN_IDX_GBL],
					XOVR_THLD_WDQ[ch][1][byte_idx][TRN_IDX_GBL]);

			print_info("IPM:CROSSEL: RDEN Result Ch%d Byte%d SDL_WRP_CODE_OPT %02d Crossth1 %02d Crossth2 %02d  E:\n",
					ch,byte_idx, SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],
					XOVR_THLD_RDEN[ch][0][byte_idx][TRN_IDX_GBL],
					XOVR_THLD_RDEN[ch][1][byte_idx][TRN_IDX_GBL]);
		}

		print_info("IPM:CROSSEL: CA Result       Ch%d SDL_WRP_CODE_OPT %02d Crossth1 %02d Crossth2 %02d  E:\n",
				ch,SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL],
				XOVR_THLD_CA[ch][0][0][TRN_IDX_GBL],
				XOVR_THLD_CA[ch][1][0][TRN_IDX_GBL]);
	}
  return cross_sel_pass;
}

//-----------------------------------------------------------------------------
// Cross-sel training to calibrate delay element to 1UI and to find
// clock domain crossing transition points
//-----------------------------------------------------------------------------
int do_cross_sel_training (unsigned int fsp,unsigned int  freq_ratio,unsigned int  freq_idx,unsigned int ch) {

	unsigned int  read_data;
	unsigned int  data_fail;
	unsigned int  lpbk_done=0;
	unsigned int  lpbk_done_raw=0;
	unsigned int  cross_pass[4][PHY_DQS_WIDTH]={0}; //[#cmpr_ptr][#byte]
	unsigned int  loop_idx=0;
	unsigned int  cmpr_start_ptr;
	unsigned int  cmpr_stop_ptr;
	unsigned int  rdqs_delay;
	unsigned int  rfirst;
	unsigned int  nui;
	unsigned int  cmpr_ptr;
	static uint8_t lpbk_training_result[LPBK_VRET_LEN][LPBK_HORI_LEN][PHY_DQS_WIDTH] = {0};
	unsigned int rdqs_delay_idx, rdq_vref_idx;
	unsigned int curr_ptrcnt_even[PHY_DQS_WIDTH];
	unsigned int curr_ptrcnt_odd[PHY_DQS_WIDTH];
	unsigned int vref_opt,delay_opt;
	unsigned int rdqs_sdl;
  unsigned int cross_sel_pass;

	// First stop CK since asserting ld_cnt_reset will mess with CK
	stop_ck(0b00,0b11,ch);

	// Invert DQS since loopback inverts the clock
	#if LPBK_TRAIN_LPBK_INT
	  set_sdlcross_patbuf(fsp,freq_ratio,freq_idx,1,ch);
	#else
	  set_sdlcross_patbuf(fsp,freq_ratio,freq_idx,0,ch);
	#endif

	// DQS is always internal lpbk
	set_dqs_invert(0b1,ch);

	// Setup the pipelines for loopback
	for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
		// Set rfirst and nui
		rfirst     = 0b0 ;
		nui        = 0b1 ;
		apb_write_field_ch(M_RDPIPE_CONTROL[byte_idx][fsp],((nui<<1)|rfirst),ch);        // rfist as in lpbk dqs get invert

		// Transmit pipeline setup
		// Turn on the Transmit SDL
		apb_write_field_ch(M_OVR_WREN_EARLY[byte_idx],0b11,ch);
		// Oe can be kept zero since loopback is internal
		#if LPBK_TRAIN_LPBK_INT
			apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b01,ch);
		#else
			apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b11,ch);
		#endif

		apb_write_field_ch(M_OVR_TXDQSOE[byte_idx],0b01,ch);

		// Disable ODT since PBD has dependence on it
		apb_write_field_ch(M_OVR_DQODT[byte_idx],0b01,ch);
		apb_write_field_ch(M_OVR_DQSODT[byte_idx],0b01,ch);

		// Enable recevier
		apb_write_field_ch(M_OVR_RXDQSEN[byte_idx],0b11,ch);
		apb_write_field_ch(M_OVR_RXDQEN[byte_idx],0b11,ch);       // Enable DQ Rx

		// Enable receive SDL
		apb_write_field_ch(M_OVR_RDEN_EARLY[byte_idx],0b11,ch);

		// Override the DQS gating and keep DQS enabled
		acsr_write_field_ch(M_ANA_DQS_RD_EN_SEL[byte_idx],0b0,ch);
		apb_write_field_ch(M_OVR_RDQSEN[byte_idx],0b11,ch);

		/// Enable loopback for DQS
		acsr_write_field_ch(M_ANA_LPBK_SEL_DQS[byte_idx],0b1,ch);

		// Set the stretch value for DQS to zero
		apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp],0,ch);
	}

	//enable loopback for dq and DMI
	#if LPBK_TRAIN_LPBK_INT
		for (unsigned int i=0; i<((DQ_BITS_PER_SLICE-1) * (PHY_DQS_WIDTH-1)); i++) acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DQ[i], 0b1,ch);
		for (unsigned int i=0; i<PHY_DQS_WIDTH; i++)                           acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DMI[i], 0b1,ch);
	#else
		for (unsigned int i=0; i<((DQ_BITS_PER_SLICE-1) * (PHY_DQS_WIDTH-1)); i++) acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DQ[i], 0b0,ch);
		for (unsigned int i=0; i<PHY_DQS_WIDTH; i++)                           acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DMI[i], 0b0,ch);
	#endif

	// Set DAC kick to maximize margin
	set_kick(LPBK_KICK,ch);

	// Set the dq vref and wdqs sdl. these are constant for the training
  unsigned int wdqs_sdl;
	for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH;byte_idx++) {
		print_dbg("Byte%d Using lpbk_vref_opt %d delay_opt %d  E:\n",byte_idx,LPBK_VREF_OPT[ch][byte_idx][TRN_IDX_GBL],LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]);
		set_rdq_vref_trn_perbyte(LPBK_VREF_OPT[ch][byte_idx][TRN_IDX_GBL],byte_idx,byte_idx,ch) ;
    // Set wdqs delay. Use the cross value from LPBK
    if (LPBK_WDQ_SDL[ch][byte_idx][TRN_IDX_GBL] > LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]) {
      wdqs_sdl=LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL];
    } else {
      wdqs_sdl=LPBK_WDQ_SDL[ch][byte_idx][TRN_IDX_GBL];
    }
    set_wdqs_delay_lpbk(LPBK_TRAIN_WDQS_NUI,wdqs_sdl,LPBK_CROSS_OPT[ch][byte_idx][TRN_IDX_GBL],byte_idx,byte_idx,fsp,ch);
	  print_dbg("IPM:CROSSEL: Using WDQS SDL Delay %d  E:\n",wdqs_sdl);
	}

	// Begin cross-sel training sweeps
	for (unsigned int cross_sel=CROSS_MIN;cross_sel<=CROSS_MAX;cross_sel++) {
		// Do a dummy pattern buffer enable to flush the pipelines.
		apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_DQRD_DATA, ch);
		wait_ptrn_done(ch);

		//Sweep wdq delay. As wdq delay is changed rdqs delay is also changed
		//so that loopback timing is maintained.
    for (unsigned int wdq_sdl=SDL_MIN;wdq_sdl<=SDL_MAX;wdq_sdl++) {
			set_wdq_delay_lpbk(LPBK_TRAIN_WDQ_NUI,wdq_sdl,cross_sel,0,PHY_DQS_WIDTH-1,fsp,ch);

			// We have 4 sets of data for comparison
			// Regular data in row 0,1,2,
			// Left shifed data in row 4,5,6
			// Right shifted data in row 7,8,9
			// Right shifted by 2 data in row 10,11,12
      // To save sim time, we will setup the PHY one byte at a time
      // Fire all 4 byte pattern buffers 
      // Read results one byte at a time
      // So the byte_idx for loop will need to be broken up 
			for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {

				// update the rdqs_delay so that lpbk timing is maintained
				if (wdq_sdl > (LPBK_PASS_SIZE_OPT[ch][byte_idx][TRN_IDX_GBL]/4)) {
					rdqs_sdl=wdq_sdl+LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]-wdqs_sdl-LPBK_PASS_SIZE_OPT[ch][byte_idx][TRN_IDX_GBL]/4;
				} else {
					rdqs_sdl=wdq_sdl+LPBK_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]-wdqs_sdl;
				}

				if (rdqs_sdl > SDL_MAX) rdqs_sdl=SDL_MAX;
				set_rdqs_delay(rdqs_sdl,fsp,byte_idx,byte_idx,ch);
      }


      // clear the pass array for every iteration
      for (unsigned int cmpr_ptr_idx=0;cmpr_ptr_idx<=3;cmpr_ptr_idx++) {
	      for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
          cross_pass[cmpr_ptr_idx][byte_idx]=0;
        }
      }

      // Send lpbk data 4 times and look to see which (if any) of the
      // patterns below passed (data,lshift, rshift, rshift2)
      for (unsigned int cmpr_ptr_idx=0;cmpr_ptr_idx<=3;cmpr_ptr_idx++) {

        if (cmpr_ptr_idx==0) cmpr_ptr=0; // Data
        if (cmpr_ptr_idx==1) cmpr_ptr=4; // Lshift
        if (cmpr_ptr_idx==2) cmpr_ptr=7; // Rshift
        if (cmpr_ptr_idx==3) cmpr_ptr=10; // Rshift2

        // Updated expected data pointer based on ld_cnt. There is one for each value
			  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
          apb_write_field_ch(M_RDQ_PTRNBUF_START_PTR[byte_idx], cmpr_ptr,ch);
          apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_START_PTR[byte_idx],cmpr_ptr,ch);
          apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_STOP_PTR[byte_idx],cmpr_ptr+2,ch);
        }

        // Reset and release the fifo pointers
        reset_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
        reset_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch) ;

        reset_release_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
        reset_release_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

        // Do loopback by enabling the pattern buffer
        apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_DQRD_DATA, ch);
        wait_ptrn_done(ch);
        delay(t_PATBUF_LPBK_DLY);

        // Store results
			  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
					// Read the results
					read_rdq_patbuf_cmpr(&data_fail, ch);
					curr_ptrcnt_even[byte_idx] =      apb_read_field_ch(M_RDFIFO_WRITE_POINTER_EVEN[byte_idx], ch);
					curr_ptrcnt_odd[byte_idx] =       apb_read_field_ch(M_RDFIFO_WRITE_POINTER_ODD[byte_idx], ch);

					if ((cmpr_ptr_idx==0) && (BIT_GET(data_fail,byte_idx)==0b0) && (curr_ptrcnt_even[byte_idx]==(SDL_TRAIN_BL/2)) && (curr_ptrcnt_odd[byte_idx]==(SDL_TRAIN_BL/2))) {
						cross_pass[cmpr_ptr_idx][byte_idx]=2;
					}
					if ((cmpr_ptr_idx==1) && (BIT_GET(data_fail,byte_idx)==0b0) && (curr_ptrcnt_even[byte_idx]==(SDL_TRAIN_BL/2)) && (curr_ptrcnt_odd[byte_idx]==(SDL_TRAIN_BL/2))) {
						cross_pass[cmpr_ptr_idx][byte_idx]=1;
					}
					if ((cmpr_ptr_idx==2) && (BIT_GET(data_fail,byte_idx)==0b0) && (curr_ptrcnt_even[byte_idx]==(SDL_TRAIN_BL/2)) && (curr_ptrcnt_odd[byte_idx]==(SDL_TRAIN_BL/2))) {
						cross_pass[cmpr_ptr_idx][byte_idx]=3;
					}
					if ((cmpr_ptr_idx==3) && (BIT_GET(data_fail,byte_idx)==0b0) && (curr_ptrcnt_even[byte_idx]==(SDL_TRAIN_BL/2)) && (curr_ptrcnt_odd[byte_idx]==(SDL_TRAIN_BL/2))) {
						cross_pass[cmpr_ptr_idx][byte_idx]=4;
					}
          #if IPM_DBG_CROSS_EXTRA
            for (unsigned int dq_idx=0;dq_idx<1;dq_idx++) {
              unsigned int read_data = apb_read_field_ch(M_RDQ_PTRNBUF_DQ[byte_idx][cmpr_ptr][dq_idx],ch);
              unsigned int exp_data  = apb_read_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][cmpr_ptr][dq_idx],ch);
              print_dbg("IPM:CROSSEL:Byte%d DQbit%d Cross %d  CmprPtr %d Wdqsdl %d Rdqsdelay %d Readdata 0x%x Expdata 0x%x DataFail %d E:\n",
                          byte_idx,dq_idx, cross_sel,cmpr_ptr,wdq_sdl,rdqs_sdl,read_data,exp_data,BIT_GET(data_fail,byte_idx));
              print_dbg("IPM:CROSSEL: Cmpr_ptr %d CrossPass0 %d Crosspass1 %d Crosspass2 %d Crosspass3 %d E: \n",
                       cmpr_ptr_idx,cross_pass[cmpr_ptr_idx][0], cross_pass[cmpr_ptr_idx][1],cross_pass[cmpr_ptr_idx][2],cross_pass[cmpr_ptr_idx][3]);
            }
          #endif
				} //byte_sweep
			} // cmpr_ptr_sweep

      // Do some error checking of the results. Only one of the 4 patterns shud match
      // else error
      for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
        unsigned int pass_count=0;
        for (unsigned int cmpr_ptr_idx=0;cmpr_ptr_idx<=3;cmpr_ptr_idx++) {
          if (cross_pass[cmpr_ptr_idx][byte_idx]>0) {
            pass_count++;
            XOVR_TRANS_DQ[ch][byte_idx][cross_sel][wdq_sdl]=cross_pass[cmpr_ptr_idx][byte_idx];
          }
        }
        if (pass_count > 1) {
						print_err("IPM:CROSSEL: ERROR! Multiple patterns passed. Check pattern buffer results  E:\n");
            print_err("IPM:CROSSEL: Byte%d Crosspass0 %d Crosspass1 %d Crosspass2 %d Crosspass3 %d Passcount %d \n",
                        byte_idx,cross_pass[0][byte_idx],cross_pass[1][byte_idx],cross_pass[2][byte_idx],cross_pass[3][byte_idx],pass_count);
        }
      }

			#if IPM_DBG_SDLCROSS
				print_dbg("IPM:CROSSEL: Cross_sel %d  Wdqdelay %02d Rdqsdelay %02d Pass0 %d Pass1 %d Pass2 %d Pass3 %d E:\n",
					cross_sel,wdq_sdl,rdqs_sdl,
					XOVR_TRANS_DQ[ch][0][cross_sel][wdq_sdl],XOVR_TRANS_DQ[ch][1][cross_sel][wdq_sdl],
					XOVR_TRANS_DQ[ch][2][cross_sel][wdq_sdl],XOVR_TRANS_DQ[ch][3][cross_sel][wdq_sdl]);
			#endif
		} // Sdl sweep
		#if IPM_DBG_SDLCROSS
		print_dbg("\n\n");
		#endif

	} // cross sweep

	// Restore pipeline defaults after loopback
	reset_dqbyte_controls(0,PHY_DQS_WIDTH-1,ch);

	// set dqs_invert as per input args
  if(RDQS_DLL == UI_0P5) {
    print_dbg("IPM:INIT: Set DLL to UI_0P5 Ch%d E:\n",ch);
		set_dqs_invert(0b0,ch);
  } else if(RDQS_DLL == UI_1P5) {
    print_dbg("IPM:INIT: Set DLL to UI_1P5 Ch%d E:\n",ch);
		set_dqs_invert(0b1,ch);
  } else {
    print_err("IPM:DQ_LPBK: ERROR! Invalid RDQS DLL setting %d\n",RDQS_DLL);
  }
	// Set the kick back to its default value
	set_kick(CSR_DQDM_RX_DQ_FE_DAC_KICK_HB,ch);

	// Restart CK
	start_ck(0b11,0b11,ch);

  // Do post-processing of transition data
  cross_sel_pass=cross_sel_postprocess(ch);

	return cross_sel_pass;
}


void do_cross_sel_bypass (unsigned int fsp,unsigned int  freq_ratio,unsigned int  freq_idx,unsigned int ch) {

  // Trans-data based on verilog sims for 2133Mbps only
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    // Cross=0
    XOVR_TRANS_DQ[ch][byte_idx][0][0]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][1]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][2]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][3]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][4]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][5]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][6]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][7]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][8]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][9]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][10]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][11]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][12]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][13]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][14]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][15]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][16]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][17]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][18]=2;
    XOVR_TRANS_DQ[ch][byte_idx][0][19]=3;
    XOVR_TRANS_DQ[ch][byte_idx][0][20]=3;
    // Cross=1
    XOVR_TRANS_DQ[ch][byte_idx][1][0]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][1]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][2]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][3]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][4]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][5]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][6]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][7]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][8]=2;
    XOVR_TRANS_DQ[ch][byte_idx][1][9]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][10]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][11]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][12]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][13]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][14]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][15]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][16]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][17]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][18]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][19]=3;
    XOVR_TRANS_DQ[ch][byte_idx][1][20]=3;    

  }

  cross_sel_postprocess(ch);

}

void dram_set_and_release_reset() {

	// Assert reset for both channels
	stuff_ckhv_patbuf(PTRNBUF_INIT, 0, 0);
	stuff_ckhv_patbuf(PTRNBUF_INIT, 0, 1);

	//Step 15 : t_INIT1 (200us) delay
	delay(t_INIT1);

	//RESET_n drive to 1
	stuff_ckhv_patbuf(PTRNBUF_CK_START, 0, 0);
	stuff_ckhv_patbuf(PTRNBUF_CK_START, 0, 1);

	//Step 17 : t_INIT3 (2ms) delay
	delay(t_INIT3);
}

void wake_up_chnl(unsigned int ch) {
  // pipe_resetn clears the pattern buffer default row state as well.
  // First reload the pattern buffer so that correct
  // initial state is there in the pipe
  stuff_ckhv_patbuf_new(0b00,0b11,0b11,SEND,ch); // cke,resetn,ckdis,ch
  delay(t_PIPE_SETTLE);

  // Assert the clken
  acsr_write_field_ch(M_ANA_CA_CLK_EN, 0b1,ch);
  acsr_write_field_ch(M_ANA_CK_CLK_EN, 0b1,ch);
  acsr_write_field_ch(M_ANA_HV_CLK_EN, 0b1,ch);
  delay(t_PIPE_SETTLE);

  // Start the clk
  stuff_ckhv_patbuf_new(0b00,0b11,0b00,SEND,ch); // cke,resetn,ckdis,ch
  delay(t_CKCKEH);

  // Assert CKE
  stuff_ckhv_patbuf_new(0b11,0b11,0b00,SEND,ch); // cke,resetn,ckdis,ch
  delay(1);
}

void disable_ch(unsigned int cke_val,unsigned int reset_n_val, unsigned int ch) {
  stop_ck(0b00,0b11,ch);
  delay(5);
  acsr_write_field_ch(M_ANA_HV_CLK_EN,0b0,ch);
  //print_info(buf,"IPM:INIT: Disable Ch%d E:\n",ch);
} // disable_ch

void enable_ch(unsigned int cke_val,unsigned int reset_n_val, unsigned int ch) {
  //Because during CA training if we give the piperstn then for another channel 
  //ptrnbuf can be have differnt value of default specially for resetn
  //We can't put start_ck before clk_en because that is asyncronous event
  stop_ck(0b00,0b11,ch);
  delay(5);
  acsr_write_field_ch(M_ANA_HV_CLK_EN,0b1,ch);
  delay(5);
  start_ck(0b11,0b11,ch);
 // print_info(buf,"IPM:INIT: Enable Ch%d E:\n",ch);
} // enable_ch

void go_to_boot(unsigned int fsp, unsigned int ch) {

	apb_write_field_ch(M_CUR_FSP,0,ch);

	//Stop the clock
	apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],  0b11,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],  0b11,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],	 0b11,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 0x00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR,  0x00,ch);
	apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
	wait_ptrn_done(ch);

	//Stop the DLL
	apb_write_field(M_DFI_CLK_EN,0b0 );
	apb_write_field(M_DLL_ACCUM_RST_N,0b0);
	apb_write_field(M_DLL_PRECOND_RST_N,0b0);
	apb_write_field(M_DLL_DFI_DIV_RST_N,0b0);
	apb_write_field(M_DLL_DAC_OUT_EN,0b0);

	//Switch to boot clk
	//Reset the PLL
	apb_write_field(M_PLL_RSTN, 		0b0);  //pll_rstn
	// Redo PLL config
	pll_config();

	//Switch to boot clk
	print_dbg("IPM:CA: Going back to boot clk E:\n");
	configure_ca_boot(BOOT_CC_SDL_DELAY,BOOT_CK_SDL_DELAY,BOOT_CC_NUI,BOOT_CK_NUI,BOOT_CAP_EN,BOOT_CROSS_SEL,0,ch);

	//Restart CK
	apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],  0b00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],  0b11,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],	 0b11,ch);		
	apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 0x00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR,  0x00,ch);
	apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
	wait_ptrn_done(ch);
}


int dll_min_bound(unsigned int divide_ratio) {
	// figure the minimum value allowed for DLL as a function of the incoming clock frequency
	// in order to stay away from the situation where the DLL clock just dies
	// and results in a lock condition
	unsigned int ret_val,i;

	// 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62
	// 0    1   2   3   4   5   6   7   8   9  10  11  12  13
	// unsigned int ret[13]={0,0,0,120,52,78,100,100,100,100,100,100,120};
	unsigned int ret[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
	i=(divide_ratio - 10)/4;
	ret_val=ret[i];
	return (ret_val);
}

void set_dll(unsigned int  fsp, unsigned int  freq_ratio, unsigned int  freq_idx, unsigned int  delay_inc, unsigned int dll_accum_ovrd) {

	unsigned int  dll_accum_delay_step_int;
	unsigned int  dll_locking_period_int;
	unsigned int  dll_lock_swing_int;

	dll_accum_delay_step_int=DLL_ACCUM_DELAY_STEP;
	dll_locking_period_int =DLL_LOCKING_PERIOD;
	dll_lock_swing_int =DLL_LOCK_SWING;

	// increment
	apb_write_field          ( M_PLL_FREEZE,    0b1 );

	// Set dll accum min bound depending on mult ratio
	apb_write_field(M_DLL_ACCUM_MIN_BOUND_HI, 		dll_min_bound(TRN_SCN[TRN_IDX_GBL].pll_mult));

	//Set the delay inc
	apb_write_field          (M_DLL_DELAY_INC,  		    delay_inc);
	apb_write_field          (M_DLL_DELAY_STEP,  		    dll_accum_delay_step_int);

	// Set locking period
	apb_write_field          (M_DLL_CLK_LOCKING_PERIOD ,dll_locking_period_int);
	apb_write_field          (M_DLL_CLK_SWING_HI ,BITS_GET(dll_lock_swing_int,22,16));
	apb_write_field          (M_DLL_CLK_SWING_LO ,BITS_GET(dll_lock_swing_int,15,0));

	// override the accumulator counter
	apb_write_field          (M_DLL_ACCUM_OVRD_VAL_HI,       BITS_GET(dll_accum_ovrd,23,16));
	apb_write_field          (M_DLL_ACCUM_OVRD_VAL_LO,       BITS_GET(dll_accum_ovrd,15,0));
	apb_write_field          (M_DLL_ACCUM_OVRD,              0b1);
	
	// enable dac_out, clk_out, and de-assert dll_rst_n (synchronization happens locally)
	apb_write_field          (M_DLL_DAC_OUT_EN,                   0b1 );
	apb_write_field          (M_DLL_CUSTOM_DIV_DFI_CLN,           0b00 );
	apb_write_field          (M_DLL_CUSTOM_DIV_MC,                0b0 );

	apb_write_field          (M_PLL_FREEZE,                  0b0 );
	delay(10);

	// de-assert reset of dfi_div
	apb_write_field          (M_DLL_DFI_DIV_RST_N,                   0b1 );
	apb_write_field          (M_DLL_DAC_OUT_EN,                      0b1 );

	delay(10);
	// de-assert reset of precond
	apb_write_field          (M_DLL_PRECOND_RST_N,                   0b1 );

	delay(10);
	// de-assert accum reset
	apb_write_field(M_DLL_ACCUM_RST_N, 		0b1);

}

void reset_dll() {

	// Assert the resets
	apb_write_field( M_PLL_FREEZE,    0b1 );
	apb_write_field(M_DLL_PRECOND_RST_N, 	0b0);
	apb_write_field(M_DLL_DFI_DIV_RST_N, 	0b0);

	// Set enables to zero
	apb_write_field(M_DLL_DAC_OUT_EN, 		0b0);

	//Reset divider settings.
	apb_write_field(M_DLL_CUSTOM_CLK_INV, 	0b0);
	apb_write_field(M_DLL_CUSTOM_DIV_MC, 	0b0);
	apb_write_field(M_DLL_CUSTOM_DIV_DFI_CLN, 	0b00);

	// Assert the overrides
	apb_write_field(M_DLL_LOCK_OVERRIDE ,     	    0b1 );

	apb_write_field( M_PLL_FREEZE,    0b0 );

}

void stuff_wdq_patbuf(unsigned int dq_neg_data, unsigned int dq_pos_data, unsigned int byte_idx, unsigned int row_idx, unsigned int ch) {
  unsigned int dq0_7=0, dq8_15=0, dq_16=0;
  for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
    if (bit_idx<8) {
      BIT_SET(dq0_7, bit_idx*2, BIT_GET(dq_pos_data, bit_idx));
      BIT_SET(dq0_7, bit_idx*2+1, BIT_GET(dq_neg_data, bit_idx));
    } else if (bit_idx<16) {
      BIT_SET(dq8_15, (bit_idx-8)*2, BIT_GET(dq_pos_data, bit_idx));
      BIT_SET(dq8_15, (bit_idx-8)*2+1, BIT_GET(dq_neg_data, bit_idx));
    } else {
      BIT_SET(dq_16, (bit_idx-16)*2, BIT_GET(dq_pos_data, bit_idx));
      BIT_SET(dq_16, (bit_idx-16)*2+1, BIT_GET(dq_neg_data, bit_idx));
    }
  }
  apb_write_ch(WDQ_PTRNBUF_DQ0_PB0_0_ADDR+row_idx*6+byte_idx*96, dq0_7, ch);
  apb_write_ch(WDQ_PTRNBUF_DQ8_PB0_0_ADDR+row_idx*6+byte_idx*96, dq8_15, ch);
  apb_write_ch(WDQ_PTRNBUF_DQ16_PB0_0_ADDR+row_idx*6+byte_idx*96, dq_16, ch);
}

void set_pbd_bank_en_ctrl(unsigned int delay, unsigned int *bank_en, unsigned int *ctrl) {
  if     (delay == 0)  { *bank_en = 0b0; *ctrl = 0x0; }
  else if(delay == 1)  { *bank_en = 0b0; *ctrl = 0x1; }
  else if(delay == 2)  { *bank_en = 0b0; *ctrl = 0x2; }
  else if(delay == 3)  { *bank_en = 0b0; *ctrl = 0x3; }
  else if(delay == 4)  { *bank_en = 0b0; *ctrl = 0x4; }
  else if(delay == 5)  { *bank_en = 0b0; *ctrl = 0x5; }
  else if(delay == 6)  { *bank_en = 0b0; *ctrl = 0x6; }
  else if(delay == 7)  { *bank_en = 0b0; *ctrl = 0x7; }
  else if(delay == 8)  { *bank_en = 0b0; *ctrl = 0x8; }
  else if(delay == 9)  { *bank_en = 0b0; *ctrl = 0x9; }
  else if(delay == 10) { *bank_en = 0b0; *ctrl = 0xA; }
  else if(delay == 11) { *bank_en = 0b0; *ctrl = 0xB; }
  else if(delay == 12) { *bank_en = 0b0; *ctrl = 0xC; }
  else if(delay == 13) { *bank_en = 0b0; *ctrl = 0xD; }
  else if(delay == 14) { *bank_en = 0b0; *ctrl = 0xE; }
  else if(delay == 15) { *bank_en = 0b0; *ctrl = 0xF; }
  else if(delay == 16) { *bank_en = 0b1; *ctrl = 0xF; }
  else if(delay == 17) { *bank_en = 0b1; *ctrl = 0xE; }
  else if(delay == 18) { *bank_en = 0b1; *ctrl = 0xD; }
  else if(delay == 19) { *bank_en = 0b1; *ctrl = 0xC; }
  else if(delay == 20) { *bank_en = 0b1; *ctrl = 0xB; }
  else if(delay == 21) { *bank_en = 0b1; *ctrl = 0xA; }
  else if(delay == 22) { *bank_en = 0b1; *ctrl = 0x9; }
  else if(delay == 23) { *bank_en = 0b1; *ctrl = 0x8; }
  else if(delay == 24) { *bank_en = 0b1; *ctrl = 0x7; }
  else if(delay == 25) { *bank_en = 0b1; *ctrl = 0x6; }
  else if(delay == 26) { *bank_en = 0b1; *ctrl = 0x5; }
  else if(delay == 27) { *bank_en = 0b1; *ctrl = 0x4; }
  else if(delay == 28) { *bank_en = 0b1; *ctrl = 0x3; }
  else if(delay == 29) { *bank_en = 0b1; *ctrl = 0x2; }
  else if(delay == 30) { *bank_en = 0b1; *ctrl = 0x1; }
  else if(delay == 31) { *bank_en = 0b1; *ctrl = 0x0; }
  else print_err("IPM:SDL: ERROR! Invalid SDL code %d E:\n",delay);

}

//-------------------------------------------------------------------------------------------------
// clock_sync_procedure:This method is used to do the clock sync procedure
//-------------------------------------------------------------------------------------------------
void clock_sync_procedure(unsigned int  fsp, unsigned int  freq_ratio, unsigned int  freq_idx) {

	unsigned int  dll_accum_ovrd_val_int;
	unsigned int  dll_locking_period_int;

	unsigned int  dll_stat_first;
	unsigned int  dll_accum_first;
	unsigned short dll_accum_first_lo;
	unsigned short dll_accum_first_hi;
	unsigned int  dll_delay_step_first;
	unsigned int  dll_lock_first;
	unsigned int  dll_overflow_first;
	unsigned int  dll_underflow_first;
	unsigned int  dll_delay_inc_first;
	unsigned int  dll_ignore_first;

	unsigned int  dll_stat_second;
	unsigned int  dll_accum_second;
	unsigned short dll_accum_second_lo;
	unsigned short dll_accum_second_hi;
	unsigned int  dll_delay_step_second;
	unsigned int  dll_lock_second;
	unsigned int  dll_overflow_second;
	unsigned int  dll_underflow_second;
	unsigned int  dll_delay_inc_second;
	unsigned int  dll_ignore_second;

	unsigned int  dll_delay_inc_lock=0;
	unsigned int  dll_accum_lock=0;
	unsigned int  dll_lock_error;

	unsigned int  cross_sel_val;
  #if SIM_ENV
	  unsigned int  cross_sel_flip=1; //=($test$plusargs("CROSS_SEL_FLIP"));
  #else 
	  unsigned int  cross_sel_flip=0; //=($test$plusargs("CROSS_SEL_FLIP"));
  #endif

	// DLL's accumulator
	dll_accum_ovrd_val_int=DLL_ACCUM_OVRD_VAL;
	dll_locking_period_int=DLL_LOCKING_PERIOD;

	dll_delay_inc_first = 0b0;
	dll_lock_first = 0b0;
	dll_ignore_first = 0b0;
	dll_underflow_first=0b0;
	dll_overflow_first=0b0;

	dll_delay_inc_second = 0b0;
	dll_lock_second = 0b0;
	dll_ignore_second = 0b0;
	dll_underflow_second=0b0;
	dll_overflow_second=0b0;

	// Setup DLL with delay_inc=1
	set_dll(fsp, freq_ratio, freq_idx,0b1,dll_accum_ovrd_val_int);
	delay(10);

	// De-assert overrides to begin DLL lock
	apb_write_field          (M_PLL_FREEZE,                         0b1 );
	apb_write_field          (M_DLL_LOCK_OVERRIDE ,     	    0b0 );
	apb_write_field          (M_DLL_CLK_LOCKING_PERIOD , dll_locking_period_int );
	apb_write_field          (M_DLL_ACCUM_OVRD,                     0b0 );
	apb_write_field          (M_PLL_FREEZE,                         0b0 );

	// lock to the first setup
	// Poll for dll Lock
	print_dbg("IPM:DLL: First lock initiated  E:\n");
	apb_poll_field(M_DLL_LOCKED, 1);
	print_dbg("IPM:DLL: First lock done  E:\n");

	// Gather lock data. Accum value, value of dll_delay_inc and lock value
	apb_write_field  ( M_PLL_FREEZE,                        0b1 );
	dll_stat_first =   apb_read	( DLL_STAT_ADDR);
	dll_accum_first_lo =   apb_read	( DLL_ACCUM_OBS_LO_ADDR);
	dll_accum_first_hi =   apb_read	( DLL_ACCUM_OBS_HI_ADDR);
	dll_delay_step_first =   apb_read	( DLL_DELAY_STEP_ADDR);
	apb_write_field          ( M_PLL_FREEZE,                        0b0 );

	dll_lock_first = BIT_GET(dll_stat_first,0);
	dll_overflow_first = BIT_GET(dll_stat_first,1);
	dll_underflow_first = BIT_GET(dll_stat_first,2);
	dll_accum_first = (dll_accum_first_hi<<16) | dll_accum_first_lo;
	dll_delay_inc_first = BIT_GET(dll_delay_step_first,15);

	//Get DLL back to reset and setup stuff for 2nd lock
	apb_write_field          ( M_PLL_FREEZE,    0b1 );
	// Reset the DLL
	reset_dll();
	delay(10);

	// Setup DLL with delay_inc=0
	set_dll(fsp, freq_ratio, freq_idx,0b0,dll_accum_ovrd_val_int);
	delay(10);

	// DLL second lock .Begin DLL lock by de-asserting override
	apb_write_field          (M_PLL_FREEZE,             0b1 );
	apb_write_field          (M_DLL_LOCK_OVERRIDE ,     0b0 );
	apb_write_field          (M_DLL_CLK_LOCKING_PERIOD ,dll_locking_period_int );
	apb_write_field          (M_DLL_ACCUM_OVRD,         0b0 );
	apb_write_field          (M_PLL_FREEZE,             0b0 );

	// lock to the first setup
	// Poll for dll Lock
	print_dbg("IPM:DLL: 2nd lock initiated  E:\n");
	apb_poll_field(M_DLL_LOCKED, 1);
	print_dbg("IPM:DLL: 2nd lock Done  E:\n");

	// Gather lock data. Accum value, value of dll_delay_inc and lock value
	apb_write_field  (M_PLL_FREEZE,             0b1 );
	dll_stat_second =   apb_read	(DLL_STAT_ADDR);
	dll_accum_second_lo =   apb_read	(DLL_ACCUM_OBS_LO_ADDR);
	dll_accum_second_hi =   apb_read	(DLL_ACCUM_OBS_HI_ADDR);
	dll_delay_step_second =   apb_read	(DLL_DELAY_STEP_ADDR);
	apb_write_field ( M_PLL_FREEZE,             0b0 );

	dll_lock_second = BIT_GET(dll_stat_second,0);
	dll_overflow_second = BIT_GET(dll_stat_second,1);
	dll_underflow_second = BIT_GET(dll_stat_second,2);
	dll_accum_second = (dll_accum_second_hi<<16) | dll_accum_second_lo;
	dll_delay_inc_second = BIT_GET(dll_delay_step_second,15);

	// Selecting which of the two dll locks you want to use for final lock
	if ((dll_lock_first == 0b0) || (dll_overflow_first == 0b1) || (dll_underflow_first==0b1)) {
		dll_ignore_first=0b1;
	}
	if ((dll_lock_second == 0b0) || (dll_overflow_second == 0b1) || (dll_underflow_second==0b1)) {
		dll_ignore_second=0b1;
	}

	if ((dll_ignore_first == 0b1) && (dll_ignore_second  == 0b1)) {
		dll_lock_error=0b1;
	} else if (dll_ignore_first == 0b1) {
		dll_delay_inc_lock = dll_delay_inc_second;
		dll_accum_lock = dll_accum_second;
		dll_lock_error=0b0;
	} else if (dll_ignore_second == 0b1) {
		dll_delay_inc_lock = dll_delay_inc_first;
		dll_accum_lock = dll_accum_first;
		dll_lock_error=0b0;
	} else if (dll_accum_second <= dll_accum_first) {
		dll_delay_inc_lock = dll_delay_inc_first;
		dll_accum_lock = dll_accum_first;
		dll_lock_error=0b0;
	} else if (dll_accum_second > dll_accum_first) {
		dll_delay_inc_lock = dll_delay_inc_second;
		dll_accum_lock = dll_accum_second;
		dll_lock_error=0b0;
	} else {
		dll_lock_error=0b1;
	}
	delay(10);

	// Now do the final DLL lock
	// Reset the DLL
	reset_dll();
	delay(10);

	//Setup the DLL with the the final delay_inc value and accum value close to final lock
	set_dll(fsp, freq_ratio, freq_idx,dll_delay_inc_lock,dll_accum_lock);
	delay(10);

	// DLL second lock .Begin DLL lock by de-asserting override
	apb_write_field          (M_PLL_FREEZE,                        0b1 );
	apb_write_field          (M_DLL_CLK_LOCKING_PERIOD ,  dll_locking_period_int );
	apb_write_field          (M_DLL_LOCK_OVERRIDE ,     	   0b0 );
	apb_write_field          (M_DLL_ACCUM_OVRD,                   0b0 );
	apb_write_field          (M_PLL_FREEZE,                        0b0 );

	// lock to the first setup
	// Poll for dll Lock
	print_dbg("IPM:DLL: Final lock initiated  E:\n");
	apb_poll_field(M_DLL_LOCKED, 1);
	print_dbg("IPM:DLL: Final lock done  E:\n");

	// Check if the lock is R2R or R2F and update cross_sel accordingly
	// Comparator output is flipped. So flipping this logic
	if (cross_sel_flip==1) {
		cross_sel_val = dll_delay_inc_lock ? 0 : 1;
	} else {
		cross_sel_val = dll_delay_inc_lock;
	}
	for (unsigned int ch=0; ch<=1;ch++) {
		for (unsigned int fsp_idx=0; fsp_idx<2; fsp_idx++) {
			apb_write_field_ch(M_CCHVCK_CROSS_SEL[fsp_idx],cross_sel_val,ch);
			for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
				apb_write_field_ch(M_CROSS_SEL[byte_idx][fsp_idx],cross_sel_val,ch );
			}
		}
	}
}

//---------------------------------------------------------------------------------------------------
// pll_freq_change_proc :This method is used to change the pll frequency. Steps are
//                       1. stop CK
//                       2. change freq, wait for pll lock
//                       3. if boot_clk_config is 1, wcross is configured for R->F boot clock
//                          and clock sync block reset is asserted
//                          else clock sync procedure is executed
//                       4. enable CK
//---------------------------------------------------------------------------------------------------
void pll_freq_change_procedure_alt (
	unsigned int  fsp,
	unsigned int  freq_ratio,
	unsigned int  freq_idx,
	unsigned int  reset_n_val,
	unsigned int  cke0_val,
	unsigned int  ck_dly_method
	) {

	unsigned short accum_obsv_hi, accum_obsv_lo;
	unsigned int ck_delay;

	for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
		//First drive CKE low
		apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],0b00,ch); //BFS: CKE shud go low
		apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],BITS_GET(reset_n_val,1,0),ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],0b00,ch);

		//Added delay for PLL set up time
		apb_write_field_ch(M_CKHV_PTRNBUF_DELAY[0],0x10,ch);

		// Flush pattern buffer
		apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 0x00,ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);
		apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
		wait_ptrn_done (ch);

		//Wait before disabling clk
		delay(t_CKELCK);

		//Then STOP CK by driving CK_t low and CK_c high
		apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0],0b11,ch);
		apb_write_field_ch(M_CK_HV_PTRN_EN,0b1,ch);
		wait_ptrn_done(ch);

		//CHK :
		apb_write_field_ch(M_CUR_FSP, fsp,ch);
	}

	//==================================================================
	//CLOCK SWITCHING - boot to HF
	//==================================================================
	// Reset PLL
	reset_pll(fsp, freq_ratio, freq_idx);
	delay(10);

	apb_write_field(M_PLL_RSTN, 		0b0);  //pll_rstn
	delay(10);

	// Reset DLL
	// Commenting this out seems to help with PLL lock
	// reset_dll();
	// delay(10);

	// set up frequency set points
	setup_fsps(fsp, freq_ratio, freq_idx);

	//Deassert PLL RESET 
	apb_write_field(M_PLL_RSTN, 		0b1);  //pll_rstn

	// Release accumulator from manual override
	apb_write( PLL_FREEZE_REGS_ADDR,          0x0001 );
	apb_write( PLL_ACCUM_OVRD_CTRL_ADDR  ,    0x0000 );
	apb_write( PLL_FREEZE_REGS_ADDR,          0x0000 );

	apb_poll_field(M_PLL_LOCK_DET_LOCKED,1);
	print_info("IPM:PLL/DLL: PLL lock done E:\n");

	// just and example reading the registers back from accum_obsv
	apb_write_field(M_PLL_FREEZE, 		0b1);
	accum_obsv_hi =   apb_read(PLL_ACCUM_OBSV_HI_ADDR); 
	accum_obsv_lo =   apb_read(PLL_ACCUM_OBSV_LO_ADDR);
	apb_write_field(M_PLL_FREEZE, 		0b0);

	delay(10);
	// write the accum fsps back into the csrs and make it accept fsps for override
	apb_write_field(M_PLL_FREEZE, 		0b1);

	apb_write_field          ( M_PLL_ACCUM_OVRD_VAL_HI[fsp], accum_obsv_hi);
	apb_write_field          ( M_PLL_ACCUM_OVRD_VAL_LO[fsp], accum_obsv_lo);

	//apb_write          ( PLL_ACCUM_OVRD_CTRL_ADDR ,     16'h0002); //commented out as siva said not req
	apb_write_field(M_PLL_FREEZE, 		0b0);

	//Lock the dfi_clk_dirty to dfi_clk_clean
	clock_sync_procedure(fsp, freq_ratio, freq_idx);
	print_info("IPM:PLL/DLL: DLL lock done E:\n");

	// gate the xover clocks before adjusting settings
	// Forthe HV outputs, stop the XOVER clk so that previous state is retained
	for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
		print_dbg("IPM:PLL/DLL: Lock: Set HV CLKEN=0 Ch%d  E:\n",ch);
		acsr_write_field_ch(M_ANA_HV_CLK_EN,0b0,ch);
		delay(t_PIPEDELAY);
	}

	// Reset and release the pipe resets
	print_dbg("IPM:PLL/DLL: Lock: Release pipe reset  E:\n");
	reset_release_pipe_rstn();
	// Make sure reset has propagated thru the pipeline
	delay(t_PIPE_RSTN);

	//Set reset back to high but dont start clk yet
	for (unsigned int ch=GLB_CH_MIN;ch<=GLB_CH_MAX;ch++) {
		print_dbg("IPM:PLL/DLL: Lock: Restore resetn pipe to logic high Ch%d  E:\n",ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_CKE[1],		0b00,ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_RESET[1], BITS_GET(reset_n_val,1,0),ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[1], 0b11,ch); //BFS: Changed to 00
		apb_write_field_ch(M_CK_HV_PTRN_EN, 	0b1,ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x01,ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x01,ch);
		wait_ptrn_done(ch);
		delay(t_PIPE_SETTLE);

		//Configure CK pipe for high freq operation
		//Need NUI=1 for CK
		ck_delay=CK_DELAY_UI*(SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]+1);
		set_ck_delay(ck_delay,fsp,ck_dly_method,ch);
		delay(t_PIPE_SETTLE);
		print_dbg("IPM:PLL/DLL: Lock: Setting CK delay %d for high speed operation Ch%d  E:\n",ck_delay,ch);

		// Turn HV CLK back on after pattern buffer has driven the right value into
		// the pipeliness
		print_dbg("IPM:PLL/DLL: Lock: Set HV CLKEN=1 Ch%d  E:\n",ch);
		acsr_write_field_ch(M_ANA_HV_CLK_EN,0b1,ch);

		// Turn CK ON
		print_dbg("IPM:PLL/DLL: Lock: Start CK Ch%d  E:\n",ch);
		apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[1], 0b00,ch); //BFS: Changed to 00
		apb_write_field_ch(M_CK_HV_PTRN_EN, 	0b1,ch);
		wait_ptrn_done(ch);

		//Now assert CKE after clk start
		print_dbg("IPM:PLL/DLL: Lock: Restart CKE Ch%d  E:\n",ch);
		delay(t_CKCKEH);
		apb_write_field_ch(M_CKHV_PTRNBUF_CKE[1],		BITS_GET(cke0_val,1,0),ch);
		apb_write_field_ch(M_CK_HV_PTRN_EN, 	0b1,ch);
		wait_ptrn_done(ch);
	}
} // pll_freq_change_procedure_alt

//------------------------------------------------------------------------------
// set_vref_on_dq: Drive vref[6:0] on DQ_PC1[6:0] during CA training
//------------------------------------------------------------------------------
void set_vref_on_dq(unsigned int vref_data, unsigned int ch) {
  unsigned int byte_idx=0;
  unsigned int row_start=0;
  unsigned int row_end=6;

  // row-start: wr_en=0; vref=vref_data; delay=0
  apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_start],0x0,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_start],0x0,ch); //Vref on DQ setup time
  stuff_wdq_patbuf(vref_data, vref_data, byte_idx, row_start, ch);

  // row-start+1: wr_en=0; vref=vref_data; delay=0
  apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_start+1],0x0,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_start+1],0x0,ch); //Vref on DQ setup time
  stuff_wdq_patbuf(vref_data, vref_data, byte_idx, row_start+1, ch);

  // row-start+2: wr_en=1; vref=vref_data; delay=0
  apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_start+2],0b1,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_start+2],0x0,ch); //Vref on DQ
  stuff_wdq_patbuf(vref_data, vref_data, byte_idx, row_start+2, ch);

  //row_start+3: wr_en=1; vref=vref_data; delay=0
  apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_start+3],0b1,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_start+3],0x0,ch); //Vref on DQ
  stuff_wdq_patbuf(vref_data, vref_data, byte_idx, row_start+3, ch);

  //row_start+4: wr_en=0; vref=0; delay=0
  apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_start+4],0b0,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_start+4],0x0,ch); //Vref on DQ hold time
  stuff_wdq_patbuf(vref_data, vref_data, byte_idx, row_start+4, ch);

  //row_start+5: wr_en=0; vref=0; delay=0
  apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_start+5],0b0,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_start+5],0x0,ch); //Vref on DQ hold time
  stuff_wdq_patbuf(vref_data, vref_data, byte_idx, row_start+5, ch);

  //row_start+5: wr_en=0; vref=0; delay=0
  apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_start+6],0b0,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_start+6],0x0,ch); //Vref on DQ hold time
  stuff_wdq_patbuf(vref_data, vref_data, byte_idx, row_start+6, ch);

  apb_write_field_ch(M_WDQ_PTRNBUF_START_PTR[byte_idx],row_start,ch);
  apb_write_field_ch(M_WDQ_PTRNBUF_STOP_PTR[byte_idx],row_end,ch);
}

//------------------------------------------------------------------------------
// set_cc_delay: set the digital and analog delay for CA and CS. Set over as well
//------------------------------------------------------------------------------
void set_cc_delay(unsigned int cc_delay, unsigned int fsp, unsigned int ch) {

	unsigned int nui;
	unsigned int sdl_delay;
	unsigned int bank_en;
	unsigned int ctrl;
	unsigned int cross_sel;

	// gate the xover clocks before adjusting settings
	acsr_write_field_ch(M_ANA_CA_CLK_EN,0b0,ch);

	// Do the computations required to set digital and analog delays
	if (CC_XOVR_OLD==1) { 
		find_ana_cross_sel_nui(cc_delay,SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL],XOVR_SRCDLY_CC[ch][TRN_IDX_GBL],XOVR_DSTDLY_CC[ch][TRN_IDX_GBL],&sdl_delay,&cross_sel,&nui);
	} else {
		find_ana_cross_sel_nui_new(
			cc_delay,
			SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL],
			XOVR_THLD_CA[ch][0][0][TRN_IDX_GBL],
			XOVR_THLD_CA[ch][1][0][TRN_IDX_GBL],
			XOVR_THLD_CA[ch][2][0][TRN_IDX_GBL],
			0,
			0,
			ch,
			&sdl_delay,
			&cross_sel,
			&nui);
	}
	set_sdl_bank_en_ctrl(sdl_delay,&bank_en,&ctrl);

	// Set the SDL delay
	acsr_write_field_ch(M_ANA_SDL_CA_CTRL[fsp], 	ctrl,ch);
	acsr_write_field_ch(M_ANA_SDL_CA_BANK_EN[fsp], 	bank_en,ch);
	// FYI this is not required to be written everytime. But it is convinient to take care here
	acsr_write_field_ch(M_ANA_SDL_CA_CAP_EN[fsp], 	SDL_CAP_EN_OPT[TRN_IDX_GBL],ch);

	// Set the digital pipe delay
	apb_write_field_ch(M_CC_PIPE_DLY_CA[fsp], nui,ch);
	apb_write_field_ch(M_CC_PIPE_DLY_CS[fsp], nui,ch);

	// Set the xover
	for (unsigned int idx=0; idx<10; idx++) {
		acsr_write_field_ch(M_ANA_CROSS_SEL_CA[idx][fsp], cross_sel,ch);
	}
	acsr_write_field_ch(M_ANA_CROSS_SEL_CS[fsp],cross_sel,ch);

	// Enable the ccr xover clks after settings update
	delay(t_PIPE_SETTLE);
	acsr_write_field_ch(M_ANA_CA_CLK_EN,0b1,ch);

} // set_cc_delay

void read_fifo_ptr_data(unsigned int *csr_ca_pos, unsigned int *csr_ca_neg, unsigned int printval, unsigned int ch) {
	unsigned int curr_ptrcnt_even[4] ;
	unsigned int curr_ptrcnt_odd[4]  ;
	unsigned int read_data2_d3 ;
	unsigned int read_data1_d3 ;
	unsigned int read_data0_d3 ;
	unsigned int read_data2_d2 ;
	unsigned int read_data1_d2 ;
	unsigned int read_data0_d2 ;

	unsigned int read_data2_d1 ;
	unsigned int read_data1_d1 ;
	unsigned int read_data0_d1 ;
	unsigned int read_data2_d0 ;
	unsigned int read_data1_d0 ;
	unsigned int read_data0_d0 ;

  unsigned int csr_ca_pos_even=0;
  unsigned int csr_ca_neg_even=0;
  unsigned int csr_ca_pos_odd=0;
  unsigned int csr_ca_neg_odd=0;

  unsigned int read_data_even_slice0;
  unsigned int read_data_odd_slice0;
  unsigned int read_data_even_slice1;
  unsigned int read_data_odd_slice1;
  unsigned int read_data_even_slice2;
  unsigned int read_data_odd_slice2;
  unsigned int read_data_even_slice3;
  unsigned int read_data_odd_slice3;

  // Check fifo pointers and print them out
  for (unsigned int byte_idx=0;byte_idx<=3;byte_idx++) {
    curr_ptrcnt_even[byte_idx] =      apb_read_field_ch(M_RDFIFO_WRITE_POINTER_EVEN[byte_idx], ch);
    curr_ptrcnt_odd[byte_idx] =       apb_read_field_ch(M_RDFIFO_WRITE_POINTER_ODD[byte_idx], ch);
    if (printval==1) {
      print_dbg( "IPM: curr_ptrcnt_even[%d] = %d E:\n", byte_idx, curr_ptrcnt_even[byte_idx]);
      print_dbg( "IPM: curr_ptrcnt_odd[%d] = %d E:\n", byte_idx, curr_ptrcnt_odd[byte_idx]);
    }
  }

  // Read the csr data
  read_data2_d3 =         apb_read_ch(RX_LAST_DATA_2_P0_D3_ADDR,ch);
  read_data1_d3 =         apb_read_ch(RX_LAST_DATA_1_P0_D3_ADDR,ch);
  read_data0_d3 =         apb_read_ch(RX_LAST_DATA_0_P0_D3_ADDR,ch);
  read_data2_d2 =         apb_read_ch(RX_LAST_DATA_2_P0_D2_ADDR,ch);
  read_data1_d2 =         apb_read_ch(RX_LAST_DATA_1_P0_D2_ADDR,ch);
  read_data0_d2 =         apb_read_ch(RX_LAST_DATA_0_P0_D2_ADDR,ch);

  read_data2_d1 =         apb_read_ch(RX_LAST_DATA_2_P0_D1_ADDR,ch);
  read_data1_d1 =         apb_read_ch(RX_LAST_DATA_1_P0_D1_ADDR,ch);
  read_data0_d1 =         apb_read_ch(RX_LAST_DATA_0_P0_D1_ADDR,ch);
  read_data2_d0 =         apb_read_ch(RX_LAST_DATA_2_P0_D0_ADDR,ch);
  read_data1_d0 =         apb_read_ch(RX_LAST_DATA_1_P0_D0_ADDR,ch);
  read_data0_d0 =         apb_read_ch(RX_LAST_DATA_0_P0_D0_ADDR,ch);

  // Remap the data bytewise into even and odd data. Its hard to make sense of it otherwise
  read_data_even_slice0 = (BIT_GET(read_data1_d0,0)    <<16 | BITS_GET(read_data0_d0,15,0));
  read_data_odd_slice0  = (BITS_GET(read_data2_d0,1,0) <<15 | BITS_GET(read_data1_d0,15,1));

  read_data_even_slice1 = (BIT_GET(read_data1_d1,0)    <<16 | BITS_GET(read_data0_d1,15,0));
  read_data_odd_slice1  = (BITS_GET(read_data2_d1,1,0) <<15 | BITS_GET(read_data1_d1,15,1));

  read_data_even_slice2 = (BIT_GET(read_data1_d2,0)    <<16 | BITS_GET(read_data0_d2,15,0));
  read_data_odd_slice2  = (BITS_GET(read_data2_d2,1,0) <<15 | BITS_GET(read_data1_d2,15,1));

  read_data_even_slice3 = (BIT_GET(read_data1_d3,0)    <<16 | BITS_GET(read_data0_d3,15,0));
  read_data_odd_slice3  = (BITS_GET(read_data2_d3,1,0) <<15 | BITS_GET(read_data1_d3,15,1));



  csr_ca_pos_even=BITS_GET(read_data_even_slice3,16,7);
  csr_ca_neg_even=BITS_GET(read_data_even_slice3,6,0) <<3 | BITS_GET(read_data_even_slice2,16,14);

  csr_ca_pos_odd=BITS_GET(read_data_odd_slice3,16,7);
  csr_ca_neg_odd=BITS_GET(read_data_odd_slice3,6,0) <<3 | BITS_GET(read_data_odd_slice2,16,14);

  if (printval==1) {
    print_dbg("curr read_data2_d3 = 0x%0x E:\n", read_data2_d3) ;
    print_dbg("curr read_data1_d3 = 0x%0x E:\n", read_data1_d3) ;
    print_dbg("curr read_data0_d3 = 0x%0x E:\n", read_data0_d3) ;

    print_dbg("curr read_data2_d2 = 0x%0x E:\n", read_data2_d2) ;
    print_dbg("curr read_data1_d2 = 0x%0x E:\n", read_data1_d2) ;
    print_dbg("curr read_data0_d2 = 0x%0x E:\n", read_data0_d2) ;

    print_dbg("curr read_data2_d1 = 0x%0x E:\n", read_data2_d1) ;
    print_dbg("curr read_data1_d1 = 0x%0x E:\n", read_data1_d1) ;
    print_dbg("curr read_data0_d1 = 0x%0x E:\n", read_data0_d1) ;

    print_dbg("curr read_data2_d0 = 0x%0x E:\n", read_data2_d0) ;
    print_dbg("curr read_data1_d0 = 0x%0x E:\n", read_data1_d0) ;
    print_dbg("curr read_data0_d0 = 0x%0x E:\n", read_data0_d0) ;

    print_dbg("Slice3 : Even data 0x%x  E:\n",read_data_even_slice3);
    print_dbg("Slice3 : Odd  data 0x%x  E:\n",read_data_odd_slice3);
    print_dbg("Slice2 : Even data 0x%x  E:\n",read_data_even_slice2);
    print_dbg("Slice2 : Odd  data 0x%x  E:\n",read_data_odd_slice2);
    print_dbg("Slice1 : Even data 0x%x  E:\n",read_data_even_slice1);
    print_dbg("Slice1 : Odd  data 0x%x  E:\n",read_data_odd_slice1);
    print_dbg("Slice0 : Even data 0x%x  E:\n",read_data_even_slice0);
    print_dbg("Slice0 : Odd  data 0x%x  E:\n",read_data_odd_slice0);
    print_dbg("Rx data pos even : 0x%x Rx data negE: 0x%x  E:\n",csr_ca_pos_even,csr_ca_neg_even);
    print_dbg("Rx data pos odd: 0x%x Rx data negO: 0x%x  E:\n",csr_ca_pos_odd,csr_ca_neg_odd);
    print_dbg(" E:\n") ;
  }

  if ((csr_ca_pos_even!=csr_ca_pos_odd) || (csr_ca_neg_even!=csr_ca_neg_odd)) {
    print_info("IPM:CA: Even and odd data not matching CA_POS_EVEN 0x%x CA_POS_ODD 0x%x CA_NEG_EVEN 0x%x CA_NEG_ODD 0x%x  E:\n", csr_ca_pos_even,csr_ca_pos_odd,csr_ca_neg_even,csr_ca_neg_odd);
  } else {
    *csr_ca_pos=csr_ca_pos_even;
    *csr_ca_neg=csr_ca_neg_even;
  }

}

//------------------------------------------------------------------------------
// CA training task: Part-2
//------------------------------------------------------------------------------
void do_ca_training_part2(unsigned int  fsp, unsigned int *vref_opt, unsigned int *cc_delay_opt,unsigned int ch) {

	unsigned int  cc_delay;
	unsigned int  csr_ca_pos=0;
	unsigned int  csr_ca_neg=0;
	static uint8_t  ca_training_result[CA_MAX_LEN]={0}; //[CA_TRAIN_VREF_MAX:CA_TRAIN_VREF_MIN][CA_TRAIN_DELAY_MAX:CA_TRAIN_DELAY_MIN];
	unsigned int ca_train_delay_min;
	unsigned int ca_train_delay_max;

	unsigned int start_found=0;
	unsigned int result;

	unsigned int catrain_delay_step;
	unsigned int catrain_vref_step;

	unsigned int loop_idx=0;
	unsigned int result_size=0;
	unsigned int vref_opt_int,delay_opt_int;


	//----------------------------------------------------
	//Setup the CA training pattern.
	//----------------------------------------------------
	stuff_cc_patbuf(CA_TRAIN_PAT_MID,CA_TRAIN_PAT_EARLY,0b0,0b1,15,ch); //ca_neg, ca_pos, cs_neg,cs_pos,row
	stuff_cc_patbuf(0x000,CA_TRAIN_PAT_LATE,0b0,0b0,16,ch);
	apb_write_field_ch(M_CC_PTRNBUF_START_PTR,15,ch);
	apb_write_field_ch(M_CC_PTRNBUF_STOP_PTR,16,ch);

	delay(t_CAENT);

	ca_train_delay_min=CA_TRAIN_DELAY_MIN_UI*(SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]+1)+(SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]+1)/CA_TRAIN_DELAY_MIN_UI_FRACTION;
	ca_train_delay_max=CA_TRAIN_DELAY_MAX_UI*(SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]+1)+(SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]+1)/CA_TRAIN_DELAY_MAX_UI_FRACTION;

	//----------------------------------------------------
	//CA training loop
	//----------------------------------------------------

  // Set the step size 
  catrain_delay_step=CA_TRAIN_DELAY_STEP;
  catrain_vref_step=CA_TRAIN_VREF_STEP;

  // Begine 2-D sweep of Dram vref and Phy CA delay
  for (unsigned int vref=CA_TRAIN_VREF_MIN;vref<CA_TRAIN_VREF_MAX+1;vref=vref+catrain_vref_step) {

    // Program dq pattern to send out vref along with wdqs pulses
    set_vref_on_dq(vref,ch);

    //Enable Byte0 DQ/DQS Transmiot pattern buffer
    apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_BYTE0,ch);
    wait_ptrn_done(ch);

    //As per DRAM spec wait needed before DRAM can accept data
    delay(t_VREFLONG);

    //LP4x needed a dummy loop to flush things out. Do the same for IPM
    #if SI_ENV
      for (cc_delay=ca_train_delay_min;cc_delay<ca_train_delay_min+1;cc_delay=cc_delay+catrain_delay_step) {
        set_cc_delay(cc_delay,fsp,ch);

        apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CC,ch);
        wait_ptrn_done(ch);
        delay(t_CATRAIN_STEP);
        apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_BYTE2|PTRN_EN_DQWR_BYTE3,ch);
        wait_ptrn_done(ch);
        delay(1);
      }
    #endif

    for (cc_delay=ca_train_delay_min;cc_delay<ca_train_delay_max+1;cc_delay=cc_delay+catrain_delay_step) {
      //Set CA NUI, SDL delay as well as adjust xover
      set_cc_delay(cc_delay,fsp,ch);

      for (unsigned int itr=0; itr<CA_TRAIN_OVRSAMPLE_CNT; itr++) {

        // Enable the CC pattern buffer. Data is already loaded outside the loop
        //enable_patbuf(0b1,0b0,0b0,0b0,0b0);
        apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CC,ch);
        wait_ptrn_done(ch);

        // Wait some time for dram to spit out the posedge and negedge data
        delay(t_CATRAIN_STEP);

        // Send WDQS loopback pulse on byte_tx to receive data
        //enable_patbuf(0b0,0b0,dqwr_ptrn_en_byte_rx,0b0,0b0);
        apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_BYTE2|PTRN_EN_DQWR_BYTE3,ch);
        wait_ptrn_done(ch);

        // Read the received data
        read_fifo_ptr_data(&csr_ca_pos,&csr_ca_neg,0b0,ch);

        if ((csr_ca_pos!=CA_TRAIN_PAT_EARLY) || (csr_ca_neg!=CA_TRAIN_PAT_MID)) {
          ca_training_result[result_size]++; // No of fails
        }

      } // itr
      #if IPM_DBG_CA
        print_dbg("IPM:CA: Vref: %d ,SDL DELAY: %d ,Rx Data Pos: 0x%x, Rx Data Neg: 0x%x, FailCnt: %d  E:\n",vref,cc_delay,csr_ca_pos,csr_ca_neg,ca_training_result[result_size]);
      #endif
      result_size++;
    } // cc delay
  } // vref ca
		result_size=0;


	//Find optimal value
  unsigned int pass_size_opt=0;
	int ret ;
	ret = find_optimal_com((uint8_t *)ca_training_result, 1, 
					0,0,  
					CA_TRAIN_VREF_MIN,CA_TRAIN_VREF_MAX,CA_TRAIN_VREF_STEP, 
					ca_train_delay_min,ca_train_delay_max,catrain_delay_step, 
					CA_TRAIN_PASS_REGION_THLD,CA_TRAIN_PASS_REGION_DIFF,
					(IPM_DBG_CA && IPM_DBG_FIND_OPT), 
					&vref_opt_int,&delay_opt_int,&pass_size_opt); 
	if (ret == -1) {
		print_err("IPM:CA: FIND_OPT_COM fail\n") ;
	} 

	*vref_opt=vref_opt_int;
	*cc_delay_opt=delay_opt_int+CA_TRAIN_OFFSET*(SDL_WRP_CODE_OPT_CA[ch][TRN_IDX_GBL]+1);

	if (cc_delay<0) {
		//`uvm_fatal("CATRAIN Error:", $sformatf("Zero or -ve eye center %d CA training incorrect",cc_delay))
	}
  #if (CA_DBG==1)
    print_dbg("IPM:CA: CC_VREF_OPT  %d, CC_DELAY_OPT %d  CC_DELAY_OPT_RAW %d E:\n", *vref_opt,*cc_delay_opt,delay_opt_int);
  #endif 

} // do_ca_training_part2

//---------------------------------------------------
// CA Training
//---------------------------------------------------
void do_ca_training_top(unsigned int  fsp, unsigned int  freq_ratio, unsigned int  freq_idx, unsigned int ch) {

	unsigned int pbd_bank_en;
	unsigned int pbd_ctrl;
	unsigned int dqdrv=0;
	unsigned int DQPAT=0x1FFFF;
	unsigned int old_fsp;
	unsigned int vref_ca;

	// Start CA training in boot clk mode
	if (INIT_TRN_DONE[ch]==0) { // Initial training case
		go_to_boot(0,ch);
	}

	//----------------------------------
	// DQ PC0/byte0 : Transmit mode
	//----------------------------------
	// Turn on the drven and SDL so that  we dont need to deal with
	// their timing; set before CBT entry to avoid micron model error
	apb_write_field_ch(M_OVR_WREN_EARLY[0],0b11,ch);
	apb_write_field_ch(M_OVR_TXDQOE[0],0b11,ch);
	apb_write_field_ch(M_OVR_TXDQSOE[0],0b11,ch);
	apb_write_field_ch(M_WDQS_PIPE_STRETCH[0][fsp],0,ch);// DQS stretch=0

	//----------------------------------
	// DQ_PC1 : Receive receive mode. A.k.a byte 2,3
	//----------------------------------
	for (unsigned int byte_idx=2;byte_idx<=3;byte_idx++) {
		// DQ Path
		apb_write_field_ch(M_OVR_RXDQEN[byte_idx],0b11,ch);

		if (dqdrv==1) {
			apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b00,ch);
		} else {
			apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b01,ch);
		}

		for (unsigned int dqbit=byte_idx*16;dqbit<(byte_idx+1)*16;dqbit++) {
			acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DQ[byte_idx], 0b0,ch);
		}
		acsr_write_field_ch(M_ANA_RX_LPBK_SEL_DMI[byte_idx], 0b0,ch);

		// RDQS Path
		apb_write_field_ch(M_OVR_RXDQSEN[byte_idx],0b11,ch);        // Enable DQS Rx
		apb_write_field_ch(M_OVR_RDQSEN[byte_idx],0b11,ch);         // Enable RDQSEN (DQS gating)
		apb_write_field_ch(M_OVR_RDEN_EARLY[byte_idx],0b11,ch);     // Enable the SDQS DL
		acsr_write_field_ch(M_ANA_DQS_RD_EN_SEL[byte_idx],0b0,ch);  // Bypass RDQSEN -ve edge flop
		acsr_write_field_ch(M_ANA_LPBK_SEL_DQS[byte_idx],0b1,ch);   // Enable DQS lpbk to receive DQ
		apb_write_field_ch(M_OVR_TXDQSOE[byte_idx],0b10,ch);        // Disable DQS Tx DRVEN
		apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp],0,ch);// DQS stretch=0

		// Setup WDQS pattern buffer to transmit pulses to receive DQ input
		// Put some setup and hold time for the DQS pulses

		//Row0. No DQS
		apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][0],0b0,ch);
		apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][0],0x0,ch);
		stuff_wdq_patbuf(DQPAT,DQPAT,byte_idx,0,ch);

		//Row 1-14 Toggle DQS
		for (unsigned int row_idx=1;row_idx<15;row_idx++) {
			apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b1,ch);
			apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0x0,ch);
			stuff_wdq_patbuf(DQPAT,DQPAT,byte_idx,row_idx,ch);
		}

		// Row 15. No DQS
		apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][15],0b0,ch);
		apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][15],0x0,ch);
		stuff_wdq_patbuf(DQPAT,DQPAT,byte_idx,15,ch);

		// Start and stop ptr
		apb_write_field_ch(M_WDQ_PTRNBUF_START_PTR[byte_idx],0,ch);
		apb_write_field_ch(M_WDQ_PTRNBUF_STOP_PTR[byte_idx],15,ch);

	}

	//----------------------------------------------------
	//Configure the CA,CS offset. When CK appears in between CK and CS we will get
	//transition regions
	//----------------------------------------------------
	set_pbd_bank_en_ctrl(CA_TRAIN_CS_PBD_DELAY,&pbd_bank_en,&pbd_ctrl);
	acsr_write_field_ch(M_ANA_TX_PBD_BANK_EN_CS[fsp],pbd_bank_en,ch);
	acsr_write_field_ch(M_ANA_TX_PBD_CTRL_CS[fsp],pbd_ctrl,ch);

	//----------------------------------------------------
	// Switch to FSPWR[fsp]
	//----------------------------------------------------
	BIT_SET(MRW_DATA[ch][13],6,fsp);
	send_mrw_through_ptrn_buf(13,ch);

	//----------------------------------------------------
	// Issue MRW-13 for CA training entry for term_rank
	//----------------------------------------------------
	BIT_SET(MRW_DATA[ch][13],0,0b1);
	send_mrw_through_ptrn_buf(13,ch);

	//----------------------------------------------------
	//Setup the CA training pattern.
	//----------------------------------------------------
	stuff_cc_patbuf(CA_TRAIN_PAT_MID,CA_TRAIN_PAT_EARLY,0b1,0b0,15,ch); //ca_neg, ca_pos, cs_neg,cs_pos,row
	stuff_cc_patbuf(CA_TRAIN_PAT_LATE,CA_TRAIN_PAT_LATE,0b0,0b1,16,ch);
	apb_write_field_ch(M_CC_PTRNBUF_START_PTR,15,ch);
	apb_write_field_ch(M_CC_PTRNBUF_STOP_PTR,16,ch);

	//----------------------------------------------------
	// Drive CKE Low to switch to FSP1 in preparation for freq change
	//----------------------------------------------------
	apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],		0b00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],  0b11,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0], 	0b00,ch);
	// Delay
	apb_write_field_ch(M_CKHV_PTRNBUF_DELAY[0], 	0x00,ch);
	// Start and stop pointer
	apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);
	// Flush the ptrnbuf
	apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
	wait_ptrn_done(ch);
	delay(t_CKELCK);
	apb_write_field_ch(M_CUR_FSP,fsp,ch);

	// Set the current FSP.freq_ratio and index before setting new value
	old_fsp =   apb_read_field_ch(M_CUR_FSP,ch);

	apb_write_field_ch(M_CUR_FSP,fsp,ch);

	//Switch to high frequency. PLL lock and DLL lock. Note that since we are in CA training, CKE
	//has to low at the end of PLL lock
	print_dbg("IPM:CA:PLL & DLL Lock begin. FSP: %d, Freq Ratio: %0d, Freq Idx: %d  E:\n",fsp,freq_ratio,freq_idx);
	pll_freq_change_procedure_alt(fsp,freq_ratio,freq_idx,0b11,0b00,1);
	print_dbg("IPM:CA:PLL & DLL Lock end. FSP: %d, Freq Ratio: %d, Freq Idx: %d E:\n",fsp,freq_ratio,freq_idx);

	//----------------------------------------------------
	// Wait tCAENT
	//----------------------------------------------------
	delay(t_CAENT);

	// 2nd part of CA training. Go thru the vref and delay loops to
	// get the pass fail regions
	print_dbg("IPM:CA: Training begin. Loop thru Vref and CA delays  E:\n");

	do_ca_training_part2(fsp,&CC_VREF_OPT[ch][TRN_IDX_GBL],&CC_DELAY_OPT[ch][TRN_IDX_GBL],ch);

	print_dbg("IPM:CA: Training Done.  E:\n");

  // Boot is fsp0
  apb_write_field_ch(M_CUR_FSP,0,ch);

  //Stop the clock
  print_dbg("IPM:CA: Stopping CK after training.  E:\n");
  apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0], 	0b11,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x00,ch);
  apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);
  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
  wait_ptrn_done(ch);

  //Stop the DLL
  apb_write_field(M_DFI_CLK_EN,0b0 );
  apb_write_field(M_DLL_ACCUM_RST_N,0b0);
  apb_write_field(M_DLL_PRECOND_RST_N,0b0);
  apb_write_field(M_DLL_DFI_DIV_RST_N,0b0);
  apb_write_field(M_DLL_DAC_OUT_EN,0b0);

  //Reset the PLL
  print_dbg("IPM:CA: Reset PLL after CA training. E:\n");
  apb_write_field(M_PLL_RSTN, 		0b0);  //pll_rstn
  // Redo PLL config
  pll_config();

  //Switch to boot clk
  print_dbg("IPM:CA: Configure boot clk after CA training. E:\n");
  
  configure_ca_boot(BOOT_CC_SDL_DELAY,BOOT_CK_SDL_DELAY,BOOT_CC_NUI,BOOT_CK_NUI,BOOT_CAP_EN,BOOT_CROSS_SEL,0,ch);

	//Remove offset between CA and CS
	acsr_write_field_ch(M_ANA_TX_PBD_BANK_EN_CS[fsp],0b0,ch);
	acsr_write_field_ch(M_ANA_TX_PBD_CTRL_CS[fsp],0x0,ch);

	//Restart CK
  print_dbg("IPM:CA: Restart CK in boot freq after CA training. E:\n");
	apb_write_field_ch(M_CKHV_PTRNBUF_CKDIS[0], 	0b00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);
	apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
	wait_ptrn_done(ch);

	delay(t_CKCKEH);

	//Assert CKE to switch back to FSP0 for term rank
	apb_write_field_ch(M_CKHV_PTRNBUF_CKE[0],		0b11,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_RESET[0],  0b11,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_START_PTR, 	0x00,ch);
	apb_write_field_ch(M_CKHV_PTRNBUF_STOP_PTR, 	0x00,ch);
	//enable_patbuf(0b0,0b1,0b0,0b0,0b0);
	apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CK, ch);
	wait_ptrn_done(ch);

	delay(t_XCBT);

	//Write trained values Dont write CC delay until all MRW's are finished
	print_info("IPM:CA: CC_VREF_OPT : %d CC_DELAY_OPT %d   E:\n",CC_VREF_OPT[ch][TRN_IDX_GBL],CC_DELAY_OPT[ch][TRN_IDX_GBL]);
	vref_ca=CC_VREF_OPT[ch][TRN_IDX_GBL];
	BITS_SET(MRW_DATA[ch][12],5,0,vref_ca);
	send_mrw_through_ptrn_buf(12,ch);

	//Exit of CA training op[0] to 0
	BIT_SET(MRW_DATA[ch][13],0,0b0);
	send_mrw_through_ptrn_buf(13,ch);
	delay(10);

	//Set FSPOP =to requested FSP
	//Set VRCG mode based on FSP
	print_dbg("IPM:CA: Switching to FSP1  E:\n");

	if (fsp==0b01) {
		BIT_SET(MRW_DATA[ch][13],3,0b0);
		BIT_SET(MRW_DATA[ch][13],7,0b1);
	} else {
		BIT_SET(MRW_DATA[ch][13],3,0b0);
		BIT_SET(MRW_DATA[ch][13],7,0b0);
	}
	send_mrw_through_ptrn_buf(13,ch);

	//As per spec wait needed before DRAM can accept data
	delay(t_VREFLONG);

	// Write CC delays & CK delays
	set_cc_delay(CC_DELAY_OPT[ch][TRN_IDX_GBL],fsp,ch);

	apb_write_field_ch(M_CUR_FSP,fsp,ch);
	// apb_write_field_ch(M_CUR_FREQ_RATIO,freq_ratio,ch);
	// apb_write_field_ch(M_CUR_FREQ_INDEX,freq_idx,ch);

}

//------------------------------------------------------------------------------
// CA training bypass
//------------------------------------------------------------------------------
void do_ca_training_bypass(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

  //Program FSPOP and FSPWR to requested FSP
  // For initial training only FSP1 is permitted.
  if (fsp==0b01) {
    BITS_SET(MRW_DATA[ch][13],7,6,0b11);
  } else {
    BITS_SET(MRW_DATA[ch][13],7,6,0b00);
  }
  send_mrw_through_ptrn_buf(13,ch);

  //Program the optimal vref
  BITS_SET(MRW_DATA[ch][12],5,0,CC_VREF_OPT[ch][TRN_IDX_GBL]);
  send_mrw_through_ptrn_buf(12,ch);

  //No more MRW from here
  //Program the optimal CC Delay
  set_cc_delay(CC_DELAY_OPT[ch][TRN_IDX_GBL],fsp,ch);

  // Set current FSP. note current FSP should be set after all the boot freq mrw's are done
  // this is to preserve boot timing between ca and ck
  apb_write_field_ch(M_CUR_FSP,fsp,ch);

  print_info("IPM:CA: CC_VREF_OPT  %d, CC_DELAY_OPT %d E:\n", CC_VREF_OPT[ch][TRN_IDX_GBL],CC_DELAY_OPT[ch][TRN_IDX_GBL]);
}

//------------------------------------------------------------------------------
// set_wdqs_delay: set the digital and analog delay for CA and CS. Set over as well
//------------------------------------------------------------------------------
void set_wdqs_delay(unsigned int wdqs_delay, unsigned int fsp, unsigned int byte_start, unsigned int byte_end, unsigned int ch) {

	unsigned int nui_wdqs;
	unsigned int sdl_delay_wdqs;
	unsigned int bank_en_wdqs;
	unsigned int ctrl_wdqs;
	unsigned int cross_sel_wdqs;
	unsigned int sdl_cap_en;

	signed int nui_wdqs_oe;
	signed int nui_wdqs_early;
	unsigned int byte_idx;

	for(byte_idx=byte_start;byte_idx<byte_end+1;byte_idx++) {
		// Do the computations required to set digital and analog delays for WDQS
		
		if (CC_XOVR_OLD==1) {
			find_ana_cross_sel_nui(wdqs_delay,SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],XOVR_SRCDLY_WDQS[ch][byte_idx][TRN_IDX_GBL],XOVR_DSTDLY_WDQS[ch][byte_idx][TRN_IDX_GBL],&sdl_delay_wdqs,&cross_sel_wdqs,&nui_wdqs);
		} else {
			find_ana_cross_sel_nui_new(
				wdqs_delay,
				SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_WDQ[ch][0][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_WDQ[ch][1][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_WDQ[ch][2][byte_idx][TRN_IDX_GBL],
				byte_idx,
				1,
				ch,
				&sdl_delay_wdqs,
				&cross_sel_wdqs,
				&nui_wdqs);
		}
			
		set_sdl_bank_en_ctrl(sdl_delay_wdqs,&bank_en_wdqs,&ctrl_wdqs);

		// Anytime wdqs delay is set, there are dependent delays that go with that 
		// also need to be set. Figure out the dependent delays
		// oe is 2 UI ahead of WDQS
		// early is 4 ui ahead of WDQS
		nui_wdqs_oe=nui_wdqs-2;
		nui_wdqs_early=nui_wdqs-4;

		if (nui_wdqs_early <0) {
			print_err("IPM:WRLVL: ERROR! -ve NUI delay encountered. Please check wdqs range. WDQSOE Delay: %d WDQS_EARLY Delay: %d",nui_wdqs_oe,nui_wdqs_early);
		}
		sdl_cap_en = SDL_CAP_EN_OPT[TRN_IDX_GBL];

		// Set the SDL delay
		acsr_write_field_ch(M_ANA_SDL_DQS_CTRL[byte_idx][fsp],ctrl_wdqs,ch);
		acsr_write_field_ch(M_ANA_SDL_DQS_BANK_EN[byte_idx][fsp],bank_en_wdqs,ch);
		acsr_write_field_ch(M_ANA_SDL_DQS_CAP_EN[byte_idx][fsp],sdl_cap_en,ch);

		// Set the digital pipe delay
		apb_write_field_ch(M_WDQS_PIPE_DLY[byte_idx][fsp],nui_wdqs,ch);
		apb_write_field_ch(M_WDQS_PIPE_OE_DLY[byte_idx][fsp],nui_wdqs_oe,ch);
		apb_write_field_ch(M_WRITE_EN_EARLY_PIPE_DLY[byte_idx][fsp],nui_wdqs_early,ch);
		apb_write_field_ch(M_W_DQS_CS_PIPE_DLY[byte_idx][fsp],nui_wdqs_oe,ch);

		// Set the xover
		acsr_write_field_ch(M_ANA_CROSS_SEL_DQSC[byte_idx][fsp],cross_sel_wdqs,ch);
		acsr_write_field_ch(M_ANA_CROSS_SEL_DQST[byte_idx][fsp],cross_sel_wdqs,ch);

	}
} 

//------------------------------------------------------------------------
// Find transition point in the presence of noise/dither etc..
//------------------------------------------------------------------------
void find_transition_com(
		uint8_t *result_ar,
		unsigned int col_width,
		unsigned int byte_idx,
		unsigned int wrp_code,
		unsigned int start,
		unsigned int stop,
		unsigned int step,
		unsigned int pat1,
		unsigned int pat2,
    unsigned int last_pat,
		unsigned int dbg,
		unsigned int ch,
		unsigned int *opt ) {

	unsigned int result_size=0;
	unsigned int curr_result;

	unsigned int pat1_start_found=0;
	unsigned int pat1_end_found=0;
	unsigned int pat2_start_found=0;
	unsigned int pat2_end_found=0;

	unsigned int pat1_start_idx=0;
	unsigned int pat1_end_idx=0;
	unsigned int pat2_start_idx=0;
	unsigned int pat2_end_idx=0; 
	unsigned int look_for_pat1=1;
	unsigned int look_for_pat2=0;

  // 2 pass approach wen last_pat is set to 1. First pass: find the last occurence of solid pat1
  unsigned int fp_pat1_start_idx=start;
  unsigned int fp_pat1_end_idx=start;
  if (last_pat==1) {
    for (unsigned int dly_idx=start;dly_idx<=stop;dly_idx=dly_idx+step) {
      curr_result=result_ar[result_size*col_width+byte_idx];
      result_size++;

      // Process first pattern
      if (look_for_pat1==1) {
        if ((pat1_start_found==0) && (pat1_end_found==0) && (curr_result==pat1))  {
          pat1_start_found=1;
          pat1_start_idx=dly_idx;
          if(dbg==1) {
          print_dbg("FIND_TRANS_COM: Find transition Byte%d Delay %d curr_result %d Pat1_start %d E:\n", dly_idx,curr_result,pat1_start_idx);
          }
        }
        if ((pat1_start_found==1) && (pat1_end_found==0) && (curr_result!=pat1)) {
          pat1_end_found=1;
          pat1_end_idx=dly_idx-step;
          if (dbg==1) {
          print_dbg("FIND_TRANS_COM: Find transition Byte%d Delay %d curr_result %d Pat1_end %d E:\n", dly_idx,curr_result,pat1_end_idx);
          }
        }
        if ((pat1_start_found==1) && (pat1_end_found==1)) {
          if ((pat1_end_idx-pat1_start_idx) >= (wrp_code/2-wrp_code/8)) {
            fp_pat1_start_idx=pat1_start_idx;
            fp_pat1_end_idx=pat1_end_idx;
          } 
          pat1_start_found=0;
          pat1_end_found=0;
        }
      }
    }
    look_for_pat1=1;
    pat1_start_found=0;
    pat1_end_found=0;
    result_size=0;

    if ((fp_pat1_start_idx==0)||(fp_pat1_end_idx==0)){
      print_err("FIND_TRANS_COM: Could not find first pattern  E:\n");
    }
  }

	for (unsigned int dly_idx=start;dly_idx<=stop;dly_idx=dly_idx+step) {
		curr_result=result_ar[result_size*col_width+byte_idx];
		result_size++;
    	if (dbg==1) {
		print_dbg("FIND_TRANS_COM: Find transition Byte%d Delay %d curr_result %d  E:\n", byte_idx,dly_idx,curr_result);
    	}

		// Process first pattern
		if ( (look_for_pat1==1) && (dly_idx >= fp_pat1_start_idx)) {
			if ((pat1_start_found==0) && (curr_result==pat1))  {
				pat1_start_found=1;
				pat1_start_idx=dly_idx;
				if (dbg==1) {
				print_dbg("FIND_TRANS_COM: Find transition Byte%d Delay %d curr_result %d Pat1_start %d E:\n", byte_idx,dly_idx,curr_result,pat1_start_idx);
				}
			}
			if ((pat1_start_found==1) && (pat1_end_found==0) && (curr_result!=pat1)) {
				pat1_end_found=1;
				pat1_end_idx=dly_idx-step;
				if (dbg==1) {
				print_dbg("FIND_TRANS_COM: Find transition Byte%d Delay %d curr_result %d Pat1_end %d E:\n", byte_idx,dly_idx,curr_result,pat1_end_idx);
				}
			}
			if ((pat1_start_found==1) && (pat1_end_found==1)) {
				if ((pat1_end_idx-pat1_start_idx) >= (wrp_code/2-wrp_code/8)) {
					look_for_pat2=1;
					look_for_pat1=0;
				} else {
					pat1_start_found=0;
					pat1_end_found=0;
				}
			}
		}

		// Process 2nd pattern
		if (look_for_pat2==1) {
			if ((pat2_start_found==0) && (curr_result==pat2))  {
				pat2_start_found=1;
				pat2_start_idx=dly_idx;
				if (dbg==1) {
				print_dbg("FIND_TRANS_COM: Find transition Byte%d Delay %d curr_result %d Pat2_start %d E:\n", byte_idx,dly_idx,curr_result,pat2_start_idx);
				}
			}
			if ((pat2_start_found==1) && (pat2_end_found==0) && (curr_result!=pat2)) {
				pat2_end_found=1;
				pat2_end_idx=dly_idx-step;
				if (dbg==1) {
				print_dbg("FIND_TRANS_COM: Find transition Byte%d Delay %d curr_result %d Pat2_end %d E:\n", byte_idx,dly_idx,curr_result,pat2_end_idx);
				}
			}
			if ((pat2_start_found==1) && (pat2_end_found==1)) {
				if ((pat2_end_idx-pat2_start_idx) >= (wrp_code/2-wrp_code/8)) {
					*opt=(pat1_end_idx+pat2_start_idx)/2;
					if (dbg==1) {
					print_dbg("FIND_TRANS_COM: Found Optima %d  E:\n", *opt);
					}
				} else {
					pat2_start_found=0;
					pat2_end_found=0;
				}
			}
		}
	} // for
	if ((pat1_start_found!=1) || (pat1_end_found!=1) || (pat2_start_found!=1) || (pat2_end_found!=1) ) {
		print_err("FIND_TRANS_COM: ERROR! curr byte %d pat1_start_found %d, pat1_end_found %d, pat2_start_found %d, pat2_end_found %d E:\n", byte_idx, pat1_start_found, pat1_end_found, pat2_start_found, pat2_end_found) ;
		print_err("FIND_TRANS_COM: ERROR! curr byte %d pat1_start_idx %d, pat1_end_idx %d, pat2_start_idx %d, pat2_end_idx %d E:\n", byte_idx, pat1_start_idx, pat1_end_idx, pat2_start_idx, pat2_end_idx) ;
		*opt=0;
		result_size = 0 ;
	}

}

//------------------------------------------------------------------------------
// Wrlvl Training Task:
//------------------------------------------------------------------------------
void do_wrlvl_training_top(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

	unsigned int prev_result=0xF;
	unsigned int curr_result=0x0;
	unsigned short read_data[PHY_DQS_WIDTH];
	unsigned int wrlvl_train_delay_min;
	unsigned int wrlvl_train_delay_max;
	static uint8_t wrlvl_training_result[TRNARR_MAXLEN][PHY_DQS_WIDTH]; 
	unsigned int result_size=0;

	// Configure all DQ's is receive mode. 
	// Also enable loopback so that the same DQS pulses can be used for receivers
	for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
		// DQ Path 
		apb_write_field_ch(M_OVR_RXDQEN[byte_idx],0b11,ch);       // Enable DQ Rx

		// RDQS Path 
		apb_write_field_ch(M_OVR_RXDQSEN[byte_idx],0b11,ch);      // Enable DQS Rx
		apb_write_field_ch(M_OVR_RDEN_EARLY[byte_idx],0b11,ch);   // Enable the SDQS DL
		acsr_write_field_ch(M_ANA_DQS_RD_EN_SEL[byte_idx],0b0,ch); // Bypass RDQSEN -ve edge flop
		apb_write_field_ch(M_OVR_RDQSEN[byte_idx],0b11,ch);       // Enable RDQSEN (DQS gating)

    // Set RDQS delay to zero and vref to mid-code
    // Prior lpbk training may have done a sweep
    set_rdqs_delay(0, fsp, 0, PHY_DQS_WIDTH-1,ch);
    #if SI_ENV
      set_rdq_vref(127,ch);
    #endif

		//Enable lpbk. Need it for Rx clocking
		acsr_write_field_ch(M_ANA_LPBK_SEL_DQS[byte_idx],0b1,ch);

		//De-assert fifo point unsigneder reset
		apb_write_field_ch(M_RDFIFO_RESET_N[byte_idx],0b1,ch);

		//----------------------------------------------------
		// Set DQS stretch to 0. We will set exact number of WDQS
		// pulse thru pattern buffer.
		//----------------------------------------------------
		//M_WDQS_PIPE_STRETCH(#Byte,#fsp)
		apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp],0,ch);

		//Disable DQ driver so that WDQS can operate while DQ is tristated
		apb_write_field_ch(M_OVR_TXDQOE[byte_idx],0b01,ch);

		// Setup WDQS pattern buffer to transmit pulses to receive DQ input
		// FYI: Loopback clk is inverted clock
		for (unsigned int row_idx=0;row_idx<16;row_idx++) {
			apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b1,ch);
		}
		apb_write_field_ch(M_WDQ_PTRNBUF_START_PTR[byte_idx],0,ch);
		apb_write_field_ch(M_WDQ_PTRNBUF_STOP_PTR[byte_idx],15,ch);

	}

	// Initialize array before starting training
	for (unsigned int i=0;i<TRNARR_MAXLEN;i++) {
		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH; byte_idx++) {
			wrlvl_training_result[i][byte_idx]=1;
		}
	}

	//MRW to enter write levelling: MR2[7]
	BIT_SET(MRW_DATA[ch][2],7,0b1);
	send_mrw_through_ptrn_buf(2,ch);

	wrlvl_train_delay_min=WRLVL_TRAIN_DELAY_MIN_UI*(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1)+(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1)/WRLVL_TRAIN_DELAY_MIN_UI_FRACTION;
	wrlvl_train_delay_max=WRLVL_TRAIN_DELAY_MAX_UI*(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1)+(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1)/WRLVL_TRAIN_DELAY_MAX_UI_FRACTION;

	//Loop thru WRLVL delays and get the sampled data
	for (unsigned int wrlvl_delay=wrlvl_train_delay_min;wrlvl_delay<wrlvl_train_delay_max+1;wrlvl_delay=wrlvl_delay+WRLVL_TRAIN_DELAY_STEP) {
		// Set wdqs delay: pipe delay(nui), sdl delay and wcross
		set_wdqs_delay(wrlvl_delay,fsp,0,PHY_DQS_WIDTH-1,ch); 

		//Enable the wren pattern buffer
		apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_DQWR_DATA,ch);
		wait_ptrn_done(ch);

		//Give time for DRAM to transfer data to DQ
		delay(t_WRLVL_TRAIN_STEP);

		//Check the received logic level
		read_data[0] =     apb_read_ch(RX_LAST_DATA_1_P0_D3_ADDR,ch);
		read_data[1] =     apb_read_ch(RX_LAST_DATA_1_P0_D2_ADDR,ch);
		read_data[2] =     apb_read_ch(RX_LAST_DATA_1_P0_D1_ADDR,ch);
		read_data[3] =     apb_read_ch(RX_LAST_DATA_1_P0_D0_ADDR,ch);

		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
			if (BITS_GET(read_data[byte_idx],15,1)==0x7FFF) {
				wrlvl_training_result[result_size][byte_idx]=0b1;
			} else if(BITS_GET(read_data[byte_idx],15,1)==0x0000) {
				wrlvl_training_result[result_size][byte_idx]=0b0;
			} else{
				// This could be due to metastability. Just continue with the loop
				wrlvl_training_result[result_size][byte_idx]=0b10;
			}
		}
		#if IPM_DBG_WRLVL
			print_dbg( "IPM:WRLVL: wrlvl_delay %d Rdata0 0x%0x, Rdata1 = 0x%0x, Rdata2 0x%0x, Rdata3 0x%0x  E:\n", 
				wrlvl_delay,
				wrlvl_training_result[result_size][0],wrlvl_training_result[result_size][1],
				wrlvl_training_result[result_size][2],wrlvl_training_result[result_size][3]);
		#endif

		result_size++;
	} // wrlvl delay loop

	// Find the optimal delay values
	for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
		unsigned int opt=0;
		find_transition_com((uint8_t *)wrlvl_training_result,PHY_DQS_WIDTH,
							byte_idx,SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL], 
							wrlvl_train_delay_min,wrlvl_train_delay_max,WRLVL_TRAIN_DELAY_STEP, 
							0,1,0, 			
							(IPM_DBG_WRLVL && IPM_DBG_TRANS), 
							ch,&opt); 
		WRLVL_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=opt+WRLVL_TRAIN_OFFSET*(SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]+1);
		//print_dbg("IPM:WRLVL: WRLVL_DELAY_OPT (CH%0d): Byte%d Raw opt: %0d Opt(offset incl): %0d  E:\n",ch,byte_idx,opt,WRLVL_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]);
	}

	//MRW to exit write levelling: MR2[7]
	BIT_SET(MRW_DATA[ch][2],7,0b0);
	send_mrw_through_ptrn_buf(2,ch);

	//Reset the pipeline controls
	reset_dqbyte_controls(0,PHY_DQS_WIDTH-1,ch);

}

//------------------------------------------------------------------------------
// Wrlvl Training Bypass
//------------------------------------------------------------------------------
void do_wrlvl_training_writetrnval(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {
  // Write the optimal delay values
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    print_info("IPM:WRLVL: Writing the optimal values TRAINING_OPT (Ch%d): delay_byte%d %d E:\n",ch,byte_idx,WRLVL_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]);
    set_wdqs_delay(WRLVL_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL],fsp,byte_idx,byte_idx,ch);
  }
}

//------------------------------------------------------------------------------
// Set DRAM Latencies
//------------------------------------------------------------------------------
void set_dram_timings(unsigned int freq_idx, unsigned int ch) {

	//Program MRW0 for nRTP=op[5:3]
	BITS_SET(MRW_DATA[ch][0],5,3,T_DRAM_NRTP[TRN_IDX_GBL]);
	send_mrw_through_ptrn_buf(0,ch);

	//Program MRW1 for nWR=op[6:4]
	//toggle read preamble
	BITS_SET(MRW_DATA[ch][1],6,4,T_DRAM_NWR[TRN_IDX_GBL]);
	//2*tCK write preamble
	BIT_SET(MRW_DATA[ch][1],2,0b1);
	//Toggle read preamble
	BIT_SET(MRW_DATA[ch][1],3,0b1);
	send_mrw_through_ptrn_buf(1,ch);

	//Program MRW2 for RL=op[2:0] WL=op[5:3]
	BITS_SET(MRW_DATA[ch][2],2,0,T_DRAM_RL[TRN_IDX_GBL]);
	BITS_SET(MRW_DATA[ch][2],5,3,T_DRAM_WL[TRN_IDX_GBL]);
	send_mrw_through_ptrn_buf(2,ch);
}

//------------------------------------------------------------------------------
// Set up the CC Pattern buffer to drive MPC command
// Setup the rden pattern buffer to drive rden to receive fifo data
//------------------------------------------------------------------------------
void set_rdpre_patbuf(unsigned int freq_idx, unsigned int ch) {

  //Program the CC pattern buffer to send MPC command. But dont send it yet
  send_mpc_through_ptrn_buf(MPC_RD_DQCAL,NOSEND,ch);

  //Program the rden pattern buffer to send rden after RL-3 latency. But dont send it yet
  // RL-3 is due to following:
  // 1. 1cycle offset due to rden being set  in row-1 while cmd is in row-0
  // 2. 1cycle offset becos we want to start training atleast 1*tck before expected pulse
  // 3.  Differences in delay between trained value of cc pipe delay and rd_end pipedelay
  for (unsigned int byte_idx=0;byte_idx<=3;byte_idx++) {
    apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][0],0b0,ch);  //Wait for RL
    apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][0],T_RDDATA_EN[TRN_IDX_GBL]-1,ch);

    for (unsigned int row_idx=1;row_idx<=RDPRE_TRAIN_BL/2;row_idx++) {
      apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][row_idx],0b1,ch);  //Assert rdqsen for BL/2*tck
      apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }

    apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][RDPRE_TRAIN_BL/2+1],0b0,ch);  //De-assert rden
    apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][RDPRE_TRAIN_BL/2+1],0,ch);

    apb_write_field_ch(M_RDEN_PTRNBUF_START_PTR[byte_idx],0,ch);  // Startptr=row0
    apb_write_field_ch(M_RDEN_PTRNBUF_STOP_PTR[byte_idx],RDPRE_TRAIN_BL/2+1,ch);
  }
}

//------------------------------------------------------------------------------
// Set rden and other dependent delays
//------------------------------------------------------------------------------
void set_rden_delay(unsigned int rden_delay, unsigned int fsp, unsigned int byte_start, unsigned int byte_end, unsigned int  chknui_flag, unsigned int ch) {

	unsigned int sdl_delay_rden;
	unsigned int bank_en_rden;
	unsigned int ctrl_rden;
	unsigned int cross_sel_rden;
	unsigned int nui_rden;
	signed int nui_rden_dqrxen;
	signed int nui_rden_dqsrxen;
	signed int nui_rden_dqodten;
	signed int nui_rden_dqsodten;
	signed int nui_rden_early;


	//`uvm_info(get_name(),$sformatf("RDPRE_TRAIN_FMINFO: RDPREDelay Setting: %d, ",rden_delay),UVM_LOW);
	for(unsigned int byte_idx=byte_start;byte_idx<byte_end+1;byte_idx++) {

		// Do the computations required to set digital and analog delays for rden
		if (CC_XOVR_OLD==1) { 
			find_ana_cross_sel_nui(rden_delay,SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],XOVR_SRCDLY_RDEN[ch][byte_idx][TRN_IDX_GBL],XOVR_DSTDLY_RDEN[ch][byte_idx][TRN_IDX_GBL],&sdl_delay_rden,&cross_sel_rden,&nui_rden);
		} else {
			find_ana_cross_sel_nui_new(
				rden_delay,
				SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_RDEN[ch][0][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_RDEN[ch][1][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_RDEN[ch][2][byte_idx][TRN_IDX_GBL],
				byte_idx,
				1,
				ch,
				&sdl_delay_rden,
				&cross_sel_rden,
				&nui_rden);
		}
		set_sdl_bank_en_ctrl(sdl_delay_rden,&bank_en_rden,&ctrl_rden);

		// Give more time. Copied from LPX.
		nui_rden_dqrxen=nui_rden-4;
		nui_rden_dqsrxen=nui_rden-2;
		nui_rden_dqodten=nui_rden-4;
		nui_rden_dqsodten=nui_rden-4;
		nui_rden_early=nui_rden-4;

		//During training we need not be strict about dependent relationships
		if (chknui_flag==0b0) {
			if (nui_rden_dqrxen<0)  nui_rden_dqrxen=0;
			if (nui_rden_dqsrxen<0) nui_rden_dqsrxen=0;
			if (nui_rden_dqodten<0) nui_rden_dqodten=0;
			if (nui_rden_dqsodten<0) nui_rden_dqsodten=0;
			if (nui_rden_early<0) nui_rden_early=0;
		} else if ((nui_rden_dqrxen<0) || (nui_rden_dqsrxen<0) || (nui_rden_dqodten<0) || (nui_rden_dqsodten<0) || (nui_rden_early<0)) {
			//`uvm_fatal("IPM:RDPRE:", $sformatf("-ve NUI delay encountered. Please check rden range. Rden_dqrxen : %d, Rden_dqsrxen: %d, Rden_dqodten : %d, Rden_dqsodten : %d, Rden_early : %d ",nui_rden_dqrxen,nui_rden_dqsrxen,nui_rden_dqodten,nui_rden_dqsodten,nui_rden_early));
		}

		//Set the SDL delay
		acsr_write_field_ch(M_ANA_TXSDL_CTRL_DQS[byte_idx][fsp],ctrl_rden,ch);
		acsr_write_field_ch(M_ANA_TXSDL_BANK_EN_DQS[byte_idx][fsp],bank_en_rden,ch);
		acsr_write_field_ch(M_ANA_TXSDL_CAP_EN_DQS[byte_idx][fsp],SDL_CAP_EN_OPT[TRN_IDX_GBL],ch);

		//Set the digital pipe delay
		apb_write_field_ch(M_RDQSEN_PIPE_DLY[byte_idx][fsp],nui_rden,ch);
		apb_write_field_ch(M_RXDQEN_PIPE_DLY[byte_idx][fsp],nui_rden_dqrxen,ch);
		apb_write_field_ch(M_RXDQSEN_PIPE_DLY[byte_idx][fsp],nui_rden_dqsrxen,ch);
		apb_write_field_ch(M_RDQODTEN_PIPE_DLY[byte_idx][fsp],nui_rden_dqodten,ch);
		apb_write_field_ch(M_RDQSODTEN_PIPE_DLY[byte_idx][fsp],nui_rden_dqsodten,ch);
		apb_write_field_ch(M_READ_EN_EARLY_PIPE_DLY[byte_idx][fsp],nui_rden_dqrxen,ch);

		//Set the xover
		acsr_write_field_ch(M_ANA_CROSS_SEL_DQS[byte_idx][fsp],cross_sel_rden,ch);
	}
}

void reset_wdq_patbuf(unsigned int ch) {
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    apb_write_field_ch(M_WDQ_PTRNBUF_START_PTR[byte_idx],0x0,ch);
    apb_write_field_ch(M_WDQ_PTRNBUF_STOP_PTR[byte_idx],0x0,ch);
    apb_write_field_ch(M_WDQ_PTRNBUF_RPT_CNT[byte_idx],0x0,ch);
    for (unsigned int row_idx=0;row_idx<=15;row_idx++) {
      apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0x0,ch);
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0x0,ch);
      for (unsigned int bit_idx=0;bit_idx<PHY_DQ_PER_DQS;bit_idx++) {
        apb_write_field_ch(M_WDQ_PTRNBUF_DQ[byte_idx][row_idx][bit_idx],0x0,ch);
      }
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_CS[byte_idx][row_idx],0x0,ch);
    }
  }
}

void reset_rden_patbuf(unsigned int ch) {
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    apb_write_field_ch(M_RDEN_PTRNBUF_START_PTR[byte_idx],0x0,ch);
    apb_write_field_ch(M_RDEN_PTRNBUF_STOP_PTR[byte_idx],0x0,ch);
    apb_write_field_ch(M_RDEN_PTRNBUF_RPT_CNT[byte_idx],0x0,ch);
    for (unsigned int row_idx=0;row_idx<=15;row_idx++) {
      apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][row_idx],0x0,ch);
      apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][row_idx],0x0,ch);
      apb_write_field_ch(M_RDEN_PTRNBUF_RD_CS[byte_idx][row_idx],0x0,ch);
    }
  }
}

void reset_rdq_patbuf(unsigned int ch) {
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    apb_write_field_ch(M_RDQ_PTRNBUF_START_PTR[byte_idx],0x0,ch);
    apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_START_PTR[byte_idx],0x0,ch);
    apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_STOP_PTR[byte_idx],0x0,ch);
  }
}

void reset_cc_patbuf(unsigned int ch) {
  apb_write_field_ch(M_CC_PTRNBUF_START_PTR,0x0,ch);
  apb_write_field_ch(M_CC_PTRNBUF_STOP_PTR,0x0,ch);
  apb_write_field_ch(M_CC_PTRNBUF_RPT_CNT,0x0,ch);
  for (unsigned int row_idx=0;row_idx<=31;row_idx++) {
    apb_write_field_ch(M_CC_PTRNBUF_DELAY[row_idx],0x0,ch);
    for (unsigned int bit_idx=0;bit_idx<10;bit_idx++) {
      apb_write_field_ch(M_CC_PTRNBUF_CA[row_idx][bit_idx],0x0,ch);
    }
  }
}

int do_rdpre_training_top(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int rpt, unsigned int ch) {

	unsigned short curr_ptrcnt_even[PHY_DQS_WIDTH]={0};
	unsigned short curr_ptrcnt_odd[PHY_DQS_WIDTH]={0};
	signed int rdpre_train_delay_min;
	signed int rdpre_train_delay_max;
	static uint8_t rdpre_training_result[TRNARR_MAXLEN][PHY_DQS_WIDTH]={0}; 
	unsigned int result_size=0;

	// Initialize the ptrcnt to zero
	// for(unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
	// 	curr_ptrcnt_even[byte_idx]=0x0;
	// 	curr_ptrcnt_odd[byte_idx]=0x0;
	// }

	//Initialize results array
	// for (unsigned int i=0;i<TRNARR_MAXLEN;i++) {
	// 	for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH; byte_idx++) {
	// 		rdpre_training_result[i][byte_idx]=0;
	// 	}
	// }

	if (rpt==0) {
		print_dbg("Ch%d : Using Non-rpt mode E:\n",ch) ;
	} else {
		print_dbg("Ch%d : Using Rpt mode E:\n",ch) ;
		BIT_SET(MRW_DATA[ch][13],1,0b1);
		send_mrw_through_ptrn_buf(13,ch);		
	}

	// Program the pattern buffer to send rden pulses. Loop must start immediately
	// afterwards (to avoid mistakenly overwriting patbuf)
	set_rdpre_patbuf(freq_idx,ch);

	// 1.5 ui to start sweep before the 1st latching edge
	rdpre_train_delay_min=((RDPRE_TRAIN_DELAY_MIN_UI + (t_DQSCK_MIN/TRN_SCN[TRN_IDX_GBL].ui) - 2 )*(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1))+(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1)/RDPRE_TRAIN_DELAY_MIN_UI_FRACTION;
	rdpre_train_delay_max=((RDPRE_TRAIN_DELAY_MAX_UI + (t_DQSCK_MAX/TRN_SCN[TRN_IDX_GBL].ui))*(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1))+(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1)/RDPRE_TRAIN_DELAY_MAX_UI_FRACTION;
	if (rdpre_train_delay_min<0) rdpre_train_delay_min = 0;

  #if IPM_DBG_RDPRE
	  print_dbg("IPM:RDPRE: MIN DELAY:%0d Max Delay %0d  E:\n",rdpre_train_delay_min,rdpre_train_delay_max);
  #endif

	// Loop through rdqsen delay and find the optimal position based
	// on fifio point unsigneder reading
	for (unsigned int rden_idx=rdpre_train_delay_min;rden_idx<=rdpre_train_delay_max;rden_idx=rden_idx+RDPRE_TRAIN_DELAY_STEP) {

		// Set the rden and other dependent delays
		set_rden_delay(rden_idx,fsp,0,PHY_DQS_WIDTH-1,0b0,ch);

		//Reset rdqsen flop and fifo point unsigneders every iteration
		reset_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
		reset_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
		reset_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

		reset_release_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
		reset_release_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
		reset_release_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

		//Send MPC rdfifo cmd. Its is already setup. Just need to enable buffer
		apb_write_ch(CC_PTRN_EN_ADDR, PTRN_EN_CC|PTRN_EN_DQRD_EN,ch);
		wait_ptrn_done(ch);

		delay(t_RDPRE_TRAIN_STEP);

		//Read the fifo-ptr. This will tell us how many pulses were received
		// for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
		for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
			curr_ptrcnt_even[byte_idx] =       apb_read_field_ch(M_RDFIFO_WRITE_POINTER_EVEN[byte_idx],ch);
			curr_ptrcnt_odd[byte_idx] =       apb_read_field_ch(M_RDFIFO_WRITE_POINTER_ODD[byte_idx],ch);

			rdpre_training_result[result_size][byte_idx]=curr_ptrcnt_even[byte_idx];

		}
		#if IPM_DBG_RDPRE 
			print_dbg("IPM:RDPRE: RDPREDelay: %03d EvenPtr0 %02d, Evenptr1 %02d, Evenptr2 %02d, Evenptr3 %02d E:\n",
				rden_idx,curr_ptrcnt_even[0], curr_ptrcnt_even[1],curr_ptrcnt_even[2],curr_ptrcnt_even[3]);
		#endif
		result_size++;
	}

	//Find pointer transition and compute optima
	//FIXME revisit offset for 1.5ui dll case
	unsigned int rdpre_pass=1;
	for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
		unsigned int opt=0;
		// Siva try : Looking for 3->2 transition now . So, the offset is appropriately adjusted by -4*NUI
		find_transition_com((uint8_t *)rdpre_training_result,PHY_DQS_WIDTH, 									
							byte_idx,SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],				
							rdpre_train_delay_min,rdpre_train_delay_max,RDPRE_TRAIN_DELAY_STEP,		
							3,2,1,																	
							(IPM_DBG_RDPRE && IPM_DBG_TRANS),																					
							ch,&opt) ;
		if (opt==0) {
			RDEN_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=0;
			rdpre_pass=0;
		} else {
			RDEN_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=opt+RDPRE_TRAIN_OFFSET*(SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]+1)-4*(SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL]+1);
		}
		//print_dbg("IPM:RDPRE: RDPRE_DELAY_OPT (CH%0d): Byte%d Raw opt: %0d Opt(offset incl): %0d  E:\n",ch,byte_idx,opt,RDEN_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]);
	}

	if (rpt==0) {
		print_dbg("Ch%d : Using Non-rpt mode E:\n",ch) ;
	} else {
		print_dbg("Ch%d : Using Rpt mode E:\n",ch) ;
		BIT_SET(MRW_DATA[ch][13],1,0b0);
		send_mrw_through_ptrn_buf(13,ch);
	}

	//Reset the pipeline controls
	reset_dqbyte_controls(0,PHY_DQS_WIDTH-1,ch);

	//Reset the pattern buffer
	reset_wdq_patbuf(ch);
	reset_rden_patbuf(ch);
	reset_rdq_patbuf(ch);
	reset_cc_patbuf(ch);

	return(rdpre_pass);
}


//------------------------------------------------------------------------------
// Read Preamble Training Bypass
//------------------------------------------------------------------------------
void do_rdpre_training_writetrnval(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {
  // Program the optimal location of rdqsen and its dependent paramters
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    print_info("IPM:RDPRE: RDPRE_DELAY_OPT TRAINING_OPT(CH%0d): delay_byte%0d: %0d  E:\n",ch,byte_idx,RDEN_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]);
    set_rden_delay(RDEN_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL],fsp,byte_idx,byte_idx,0b1,ch);
  }
}

//------------------------------------------------------------------------------
// Set up the CC Pattern buffer to drive MPC command
// Setup the rden pattern buffer to drive rden to receive fifo data
//------------------------------------------------------------------------------
void set_rddq_patbuf(unsigned int freq_idx, unsigned int mrw32_pat, unsigned int ch) {

  //======================================================================
  // Pattern buffer programming for BL=8
  //======================================================================
  //  Row#    CA              RDEN      WDQ (wren can be zero)
  //  0       MPC-RD_DQ_CAL   0 (RL-2)  Exp_Data_BL[1:0]
  //  1       DES             1         Exp_Data_BL[3:2]
  //  2       DES             1         Exp_Data_BL[5:4]
  //  3       DES             1         Exp_Data_BL[7:6]
  //  4       DES             1         -
  //  5       DES             0         -
  //======================================================================

  //Program the CC pattern buffer to send MPC command. This is done on row-0
  // But dont send it yet
  send_mpc_through_ptrn_buf(MPC_RD_DQCAL,NOSEND,ch);

  for (unsigned int byte_idx=0;byte_idx<=3;byte_idx++) {
    //Program the rden pattern buffer to send rden after RL-3 latency. But dont send it yet
    // 1. 1cycle offset due to rden being set  in row-1 while cmd is in row-0
    // 2. 1cycle offset becos it seems like we are setting cmd->rden as RL-1 in our read operation

    apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][0],0b0,ch);  //Wait for RL
    apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][0],T_RDDATA_EN[TRN_IDX_GBL]-1,ch);

    for (unsigned int row_idx=1;row_idx<=RDDQ_TRAIN_BL/2;row_idx++) {
      apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][row_idx],0b1,ch);  //Assert rdqsen for BL/2*tck
      apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }

    apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][RDDQ_TRAIN_BL/2+1],0b0,ch);  //De-assert rden
    apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][RDDQ_TRAIN_BL/2+1],0,ch);

    apb_write_field_ch(M_RDEN_PTRNBUF_START_PTR[byte_idx],0,ch);  // Startptr=row0
    apb_write_field_ch(M_RDEN_PTRNBUF_STOP_PTR[byte_idx],RDDQ_TRAIN_BL/2+1,ch);


    // Program the WR DQ  pattern buffer with expected data.
    // As per FLC spec the default value of MR32='h5A='b0101_1010
    // Also program wren to zero so that we dont get any dqs pulses
    for (unsigned int row_idx=0;row_idx<=3;row_idx++) {
      unsigned int dq_neg_data=0;
      unsigned int dq_pos_data=0;
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b0,ch);
      for (unsigned int dq_idx=0;dq_idx<DQ_BITS_PER_SLICE;dq_idx++) {
        BIT_SET(dq_pos_data, dq_idx, BIT_GET(mrw32_pat,row_idx*2));
        BIT_SET(dq_neg_data, dq_idx, BIT_GET(mrw32_pat,row_idx*2+1));
      }
      stuff_wdq_patbuf(dq_neg_data, dq_pos_data, byte_idx, row_idx, ch);
    }

    // Program the read DQ pattern buffer and the compare pattern point unsigneder
    apb_write_field_ch(M_RDQ_PTRNBUF_START_PTR[byte_idx],0,ch);
    apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_START_PTR[byte_idx],0,ch);
    apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_STOP_PTR[byte_idx],3,ch);
  }
}

//------------------------------------------------------------------------------
// Read DQ Training
// FIXME 1.5UI DLL support
//------------------------------------------------------------------------------
int do_rddq_training_top(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

	unsigned int vref_opt=0,delay_opt=0;
	unsigned int rdq_cmpr=0;
	unsigned short ptrcnt_even[PHY_DQS_WIDTH]={0};
	unsigned short ptrcnt_odd[PHY_DQS_WIDTH]={0};
	static uint8_t rddq_training_result[RDDQ_MAX_LEN][PHY_DQS_WIDTH]={0};
	unsigned int result_size=0;
	int pass_flag=1;

	// For simplicity set the invert masks to zero so that same data is driven on all pins
	// FIXME: Support for alternate pin invertion by programming expected data appropriately
	BITS_SET(MRW_DATA[ch][15],7,0,0x0);
	BITS_SET(MRW_DATA[ch][20],7,0,0x0);
	send_mrw_through_ptrn_buf(15,ch);
	send_mrw_through_ptrn_buf(20,ch);

	//Due to lack of preamble in RDDQCAL MPC command, we will not be able to extract the 
	//first 2 bits of the burst
	//So, zero it out so that bit 2 is the first toggle on the channel.
	//Default MRW32 = 0101_1010
	//BCA MRW32     = 1010_0100
	BITS_SET(MRW_DATA[ch][32],7,0,RDDQ_TRAIN_PAT);
	send_mrw_through_ptrn_buf(32,ch);

	// Program the pattern buffer to send rddq pulses. Loop must start immediately
	// afterwards (to avoid mistakenly overwriting patbuf)
	set_rddq_patbuf(freq_idx,RDDQ_TRAIN_PAT,ch);

	// Dont insert any pattern buffer, MRW, MPC commands here since it will mess
	// with above pattern buffer generation

	// Loop through rdqsen delay and find the optimal position based
	// on fifio point unsigneder reading
	// Loop thru vref and rddq ranges and oversampling
	for (unsigned int rdq_vref=RDDQ_TRAIN_VREF_MIN; rdq_vref<=RDDQ_TRAIN_VREF_MAX; rdq_vref=rdq_vref+RDDQ_TRAIN_VREF_STEP) {
		set_rdq_vref_trn(rdq_vref, ch);
		for (unsigned int rdqs_delay=RDDQ_TRAIN_DELAY_MIN;rdqs_delay<=RDDQ_TRAIN_DELAY_MAX;rdqs_delay=rdqs_delay+RDDQ_TRAIN_DELAY_STEP) {

			// Set the rddq and other dependent delays
			set_rdqs_delay(rdqs_delay,fsp,0,PHY_DQS_WIDTH-1,ch);

			for (unsigned int itr=0; itr<=RDDQ_TRAIN_OVRSAMPLE_CNT; itr++) {
				//Reset rdqsen flop and fifo point unsigneders every iteration
				reset_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
				reset_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
				reset_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

				reset_release_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
				reset_release_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
				reset_release_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

				// unsigned int rd_en_sel2=acsr_read_field_ch(M_ANA_DQS_RD_EN_SEL[2],ch);
				//Send MPC RDDQCAL CMD
				apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CC|PTRN_EN_DQWR_DATA|PTRN_EN_DQRD_EN|PTRN_EN_DQRD_DATA,ch);
				wait_ptrn_done(ch);

				delay(t_RDDQ_TRAIN_STEP);

				//Read the comparison results
				read_rdq_patbuf_cmpr(&rdq_cmpr, ch);
				for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH;byte_idx++) { 
					ptrcnt_even[byte_idx] =           apb_read_field_ch(M_RDFIFO_WRITE_POINTER_EVEN[byte_idx],ch);
					ptrcnt_odd[byte_idx] =           apb_read_field_ch(M_RDFIFO_WRITE_POINTER_ODD[byte_idx],ch);

					//store the result of pass fail 
					if ( ((BIT_GET(rdq_cmpr,byte_idx))!=0b0) || (ptrcnt_even[byte_idx]!=4) || (ptrcnt_odd[byte_idx]!=4)) {
						rddq_training_result[result_size][byte_idx]++;
						if ((ptrcnt_even[byte_idx]!=4) || (ptrcnt_odd[byte_idx]!=4)) {
							print_err("IPM:RDDQ: Incorrect pointer count!! Ch%d Byte%d DQ Vref %03d Rdqs delay %02d ptrcnt_even %d ptrcnt_odd %d  E:\n",ch,byte_idx,rdq_vref,rdqs_delay,ptrcnt_even[byte_idx],ptrcnt_odd[byte_idx]);
						}
					}
				}//byte
			}//ovrsampling
      #if IPM_DBG_RDDQ
        print_dbg("IPM:RDDQ: DQ Vref %03d Rdqs delay %02d FailCnt0 %d FailCnt1 %d FailCnt2 %d FailCnt3 %d E:\n",
                  rdq_vref,rdqs_delay,rddq_training_result[result_size][0],rddq_training_result[result_size][1],
                  rddq_training_result[result_size][2],rddq_training_result[result_size][3]);
      #endif

			result_size++;

		} //rdqs_delay
	} // rdq_vref

	//Find and set optimal rdqs_delay per byte
  unsigned int pass_size_opt=0;
	int ret ;
	for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
		ret = find_optimal_com((uint8_t *)rddq_training_result,PHY_DQS_WIDTH, 							
						byte_idx,byte_idx, 												
						RDDQ_TRAIN_VREF_MIN,RDDQ_TRAIN_VREF_MAX,RDDQ_TRAIN_VREF_STEP,	
						RDDQ_TRAIN_DELAY_MIN,RDDQ_TRAIN_DELAY_MAX,RDDQ_TRAIN_DELAY_STEP,
						RDDQ_TRAIN_PASS_REGION_THLD,RDDQ_TRAIN_PASS_REGION_DIFF,
						(IPM_DBG_RDDQ && IPM_DBG_FIND_OPT ),					
						&vref_opt,&delay_opt,&pass_size_opt);				
		if (ret == -1) {
			print_err("IPM:RDDQ: FIND_OPT_COM fail E:\n") ;
		}
		RDQ_VREF_OPT[ch][byte_idx][TRN_IDX_GBL]=vref_opt;
		RDQS_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=delay_opt;
		if ((vref_opt==0) || (delay_opt==0) || (pass_size_opt==0)) {
			pass_flag=0;
		}
	}

	#if SI_ENV
  #if IPM_PRINT_EYE_PERBYTE_RDDQ
    for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
      print_eye_diagram((uint8_t *)rddq_training_result, byte_idx, 0, 0, // bit_idx not used, perbit=0
          PHY_DQS_WIDTH, PHY_DQ_PER_DQS,
          RDDQ_TRAIN_VREF_MIN , RDDQ_TRAIN_VREF_MAX , RDDQ_TRAIN_VREF_STEP,
          RDDQ_TRAIN_DELAY_MIN, RDDQ_TRAIN_DELAY_MAX, RDDQ_TRAIN_DELAY_STEP, RDDQ_HORI_LEN,
          RDQ_VREF_OPT[ch][byte_idx][TRN_IDX_GBL], RDQS_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]) ;

    }
	#endif
  #endif

	//Reset the pipeline controls
	reset_dqbyte_controls(0,PHY_DQS_WIDTH-1,ch);

	//Reset the pattern buffer
	reset_wdq_patbuf(ch);
	reset_rden_patbuf(ch);
	reset_rdq_patbuf(ch);
	reset_cc_patbuf(ch);

	return pass_flag;
}

//------------------------------------------------------------------------------
// Read DQ Training Bypass
//------------------------------------------------------------------------------
void do_rddq_training_writetrnval(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

  // Program the optimal location of rdqsen and its dependent paramters
  for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
    print_info("IPM:RDDQ: Writing the trained values TRAINING_OPT(CH%0d): Byte%d Vref_opt: %d Delay_opt: %0d  E:\n",ch,byte_idx,RDQ_VREF_OPT[ch][byte_idx][TRN_IDX_GBL],RDQS_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]);
    set_rdqs_delay(RDQS_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL],fsp,byte_idx,byte_idx,ch);
    set_rdq_vref_trn(RDQ_VREF_OPT[ch][byte_idx][TRN_IDX_GBL],ch);
  }
}

//------------------------------------------------------------------------------
// Write DQ Pattern buffer programming
//------------------------------------------------------------------------------
void set_wrdq_patbuf_new(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int twrlat, unsigned int ch) {

  unsigned int write_dq_packed[PHY_DQS_WIDTH][PHY_DQ_PER_DQS];

  for (unsigned int burst_idx=0;burst_idx<WRDQ_TRAIN_BL;burst_idx++) {
    for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
      for (unsigned int bit_idx=0; bit_idx<PHY_DQ_PER_DQS; bit_idx++) {
        BIT_SET(write_dq_packed[byte_idx][bit_idx],burst_idx,BIT_GET(WRDQ_TRAIN_PAT[burst_idx][byte_idx],bit_idx));
      }
    }
  }

  // DQ pattern buffer programming
  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
    // Strech value of WDQS was set to zero for earlier trainings.
    // Bring it back to its default to generate write preamble
    // FIXME: need to handle both 0p5 and 1p5 postamble
    apb_write_field_ch(M_WDQS_PIPE_STRETCH[byte_idx][fsp],STRCH_WDQS,ch);

    // Program the write dq pattern buffer
    apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][0],0b0,ch);
    apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][0],twrlat,ch);

    for (unsigned int row_idx=1;row_idx<=WRDQ_TRAIN_BL/2;row_idx++) {
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b1,ch);  //Assert wdqs for BL/2*tck
      apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }

    for (unsigned int row_idx=(WRDQ_TRAIN_BL/2)+1;row_idx<=7;row_idx++) {
      apb_write_field_ch(M_WDQ_PTRNBUF_WR_EN[byte_idx][row_idx],0b0,ch);  //De-assert wdqs
      apb_write_field_ch(M_WDQ_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }

    stuff_wdq_patbuf(0x0, 0x0, byte_idx, 0, ch);
    stuff_wdq_patbuf(0x0, 0x0, byte_idx, 1, ch);
    stuff_wdq_patbuf(0x0, 0x0, byte_idx, 2, ch);
    stuff_wdq_patbuf(0x0, 0x0, byte_idx, 3, ch);
    stuff_wdq_patbuf(WRDQ_TRAIN_PAT[1][byte_idx], WRDQ_TRAIN_PAT[0][byte_idx], byte_idx, 4, ch);
    stuff_wdq_patbuf(WRDQ_TRAIN_PAT[3][byte_idx], WRDQ_TRAIN_PAT[2][byte_idx], byte_idx, 5, ch);
    stuff_wdq_patbuf(WRDQ_TRAIN_PAT[5][byte_idx], WRDQ_TRAIN_PAT[4][byte_idx], byte_idx, 6, ch);
    stuff_wdq_patbuf(WRDQ_TRAIN_PAT[7][byte_idx], WRDQ_TRAIN_PAT[6][byte_idx], byte_idx, 7, ch);

    // Program the start and stop ptr
    apb_write_field_ch(M_WDQ_PTRNBUF_START_PTR[byte_idx],0,ch);
    apb_write_field_ch(M_WDQ_PTRNBUF_STOP_PTR[byte_idx],7,ch);

    // Program the rdq start ptr and comparrator start and stop ptr
    apb_write_field_ch(M_RDQ_PTRNBUF_START_PTR[byte_idx], 4,ch);
    apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_START_PTR[byte_idx],4,ch);
    apb_write_field_ch(M_RDQ_PTRNBUF_CMPR_STOP_PTR[byte_idx],7,ch);

    //Program the rden pattern buffer
    apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][0],0b0,ch);  //Wait for RL
    apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][0],T_RDDATA_EN[TRN_IDX_GBL]-1,ch);

    for (unsigned int row_idx=1;row_idx<=WRDQ_TRAIN_BL/2;row_idx++) {
      apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][row_idx],0b1,ch);  //Assert rdqsen for BL/2*tck
      apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][row_idx],0,ch);
    }

    apb_write_field_ch(M_RDEN_PTRNBUF_RD_EN[byte_idx][WRDQ_TRAIN_BL/2+1],0b0,ch);  //De-assert rden
    apb_write_field_ch(M_RDEN_PTRNBUF_DELAY[byte_idx][WRDQ_TRAIN_BL/2+1],0,ch);

    apb_write_field_ch(M_RDEN_PTRNBUF_START_PTR[byte_idx],0,ch);  // Startptr=row0
    apb_write_field_ch(M_RDEN_PTRNBUF_STOP_PTR[byte_idx],WRDQ_TRAIN_BL/2+1,ch);
  }
}

void set_wdq_vref(unsigned int vref, unsigned int ch) {
  BITS_SET(MRW_DATA[ch][14],5,0,vref);
  // Bit 6 seting not needed for IPM. There is only one range.
  send_mrw_through_ptrn_buf(14,ch);
}

void set_wdq_delay(unsigned int delay, unsigned int fsp, unsigned int byte_start, unsigned int byte_end, unsigned int ch) {
	unsigned int nui_dly, nui_oe_dly, cross_sel, sdl_dly, sdl_bank_en, sdl_ctrl, sdl_cap_en;

	for (unsigned int byte_idx=byte_start;byte_idx<=byte_end;byte_idx++) {
		// Do the computations required to set digital and analog delays
		if (CC_XOVR_OLD==1) {
		  find_ana_cross_sel_nui(delay,SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],XOVR_SRCDLY_WDQS[ch][byte_idx][TRN_IDX_GBL],XOVR_DSTDLY_WDQS[ch][byte_idx][TRN_IDX_GBL],&sdl_dly,&cross_sel,&nui_dly);
		} else {
			find_ana_cross_sel_nui_new(
				delay,
				SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_WDQ[ch][0][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_WDQ[ch][1][byte_idx][TRN_IDX_GBL],
				XOVR_THLD_WDQ[ch][2][byte_idx][TRN_IDX_GBL],
				byte_idx,
				1,
				ch,
				&sdl_dly,
				&cross_sel,
				&nui_dly);
		}

		set_sdl_bank_en_ctrl(sdl_dly,&sdl_bank_en,&sdl_ctrl);
		sdl_cap_en = SDL_CAP_EN_OPT[TRN_IDX_GBL];

		nui_oe_dly=nui_dly;
		if (nui_oe_dly<0) {
			return;
		}

		acsr_write_field_ch(M_ANA_SDL_DQ_CTRL[byte_idx][fsp], sdl_ctrl,ch);
		acsr_write_field_ch(M_ANA_SDL_DQ_BANK_EN[byte_idx][fsp], sdl_bank_en,ch);
		acsr_write_field_ch(M_ANA_SDL_DQ_CAP_EN[byte_idx][fsp], sdl_cap_en,ch);

		acsr_write_field_ch(M_ANA_DQ_CROSS_SEL[byte_idx][fsp], cross_sel,ch);
		acsr_write_field_ch(M_ANA_CROSS_SEL_DMI[byte_idx][fsp],cross_sel,ch);
		for (unsigned int dq_idx=byte_idx*16; dq_idx<byte_idx*16+16; dq_idx++)
			acsr_write_field_ch(M_ANA_CROSS_SEL_DQ[dq_idx][fsp],cross_sel,ch);

		apb_write_field_ch(M_WDQ_PIPE_DLY[byte_idx][fsp],nui_dly,ch);
		apb_write_field_ch(M_WDQ_PIPE_OE_DLY[byte_idx][fsp],nui_oe_dly,ch);
		apb_write_field_ch(M_W_DQ_CS_PIPE_DLY[byte_idx][fsp],nui_oe_dly,ch);
	}
}

//------------------------------------------------------------------------------
// Write DQ Training
// FIXME: Consider 1.5tck postamble as well
//------------------------------------------------------------------------------
int do_wrdq_training_top( unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

	//unsigned int cur_training_result;
	unsigned int compare_rdata;
	unsigned short ptrcnt_even[PHY_DQS_WIDTH]={0};
	unsigned short ptrcnt_odd[PHY_DQS_WIDTH]={0};
	unsigned int wrdq_train_delay_min;
	unsigned int wrdq_train_delay_max;
	static uint8_t wrdq_training_result[WRDQ_MAX_LEN][PHY_DQS_WIDTH]={0};
	static uint8_t wrdq_training_optvref[TRNOPT_MAXLEN][PHY_DQS_WIDTH]={0};
	unsigned int result_size=0,result_size_optvref=0;
	unsigned int vref_opt=0,delay_opt=0;
	int pass_flag=1;
	unsigned int twrlat=T_PHY_WRLAT[TRN_IDX_GBL]-1;

	set_wrdq_patbuf_new(fsp,freq_ratio,freq_idx,twrlat,ch);

	wrdq_train_delay_min=WRDQ_TRAIN_DELAY_MIN_UI*(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1);
	wrdq_train_delay_max=WRDQ_TRAIN_DELAY_MAX_UI*(SDL_WRP_CODE_OPT_DQ[ch][0][TRN_IDX_GBL]+1);

	int wrdq_delay_index_len = (wrdq_train_delay_max-wrdq_train_delay_min) / WRDQ_TRAIN_DELAY_STEP + 1 ;

	// Loop thru vref and wrdq ranges
	for (unsigned int vref=WRDQ_TRAIN_VREF_MIN; vref<=WRDQ_TRAIN_VREF_MAX; vref+=WRDQ_TRAIN_VREF_STEP) {
		set_wdq_vref(vref,ch);
		delay(1);

		for (unsigned int wdq_delay=wrdq_train_delay_min; wdq_delay<=wrdq_train_delay_max; wdq_delay+=WRDQ_TRAIN_DELAY_STEP) {
			// Set the wdq delay for each byte
			set_wdq_delay(wdq_delay, fsp, 0, 3,ch);

			for (unsigned int itr=0; itr<WRDQ_TRAIN_OVRSAMPLE_CNT; itr+=1) {

				// Reset and release fifo point unsigneders etc to start clean every iteration
				reset_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
				reset_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
				reset_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

				reset_release_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
				reset_release_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
				reset_release_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

				// Issue MPC WRFIFO 
				send_mpc_through_ptrn_buf(MPC_WR_FIFO,NOSEND,ch);
				apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CC|PTRN_EN_DQWR_DATA,ch);
				wait_ptrn_done(ch);
				delay(t_WTR);

				// Issue MPC RDFIFO 
				send_mpc_through_ptrn_buf(MPC_RD_FIFO,NOSEND,ch);
				apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CC|PTRN_EN_DQRD_EN|PTRN_EN_DQRD_DATA,ch);
				wait_ptrn_done(ch);

				delay(t_WRDQ_TRAIN_STEP);

				//Read and save the data received
				read_rdq_patbuf_cmpr(&compare_rdata, ch);
				//read_rdq_patbuf_cmpr_new(&compare_rdata, ch);
				for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
					ptrcnt_even[byte_idx] =           apb_read_field_ch(M_RDFIFO_WRITE_POINTER_EVEN[byte_idx],ch);
					ptrcnt_odd[byte_idx] =           apb_read_field_ch(M_RDFIFO_WRITE_POINTER_ODD[byte_idx],ch);

					//store the result of pass fail 
					if ( ((BIT_GET(compare_rdata,byte_idx))!=0b0) || (ptrcnt_even[byte_idx]!=4) || (ptrcnt_odd[byte_idx]!=4)) {
						wrdq_training_result[result_size][byte_idx]++;
					}

				}//byte
			}//ovrsmple

			// Print out the read data and expected data

			#if IPM_DBG_WRDQ
			  print_dbg("IPM:WRDQ: DQ Vref %02d Wdq delay %03d  FailCnt0 %d FailCnt1 %d FailCnt2 %d FailCnt3 %d  E:\n",
                  vref,wdq_delay,wrdq_training_result[result_size][0],wrdq_training_result[result_size][1],
                                 wrdq_training_result[result_size][2],wrdq_training_result[result_size][3]);
      #endif
			result_size++;
		}
	}

	// Since Vref is common to all bytes, finding optima is a bit different
	// for wrdq training.
	// First first the optimal vref which is the center of the common eye for
	// all bytes
	result_size=0;
	result_size_optvref=0;
	unsigned int max_pass_size_sum=0;
	unsigned int pass_size_sum=0;
	unsigned int vref_opt_allbyte=0;
	unsigned int pass_size_opt=0;
	unsigned int vref_eye[50]={0};

  // Extract the horizontal opening for each vref as the sum of the opening of the individual bytes
	for (unsigned int vref=WRDQ_TRAIN_VREF_MIN; vref<=WRDQ_TRAIN_VREF_MAX; vref+=WRDQ_TRAIN_VREF_STEP) {
		pass_size_sum=0;
			for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
				find_optimal_com((uint8_t *)wrdq_training_result,PHY_DQS_WIDTH,						
								byte_idx,byte_idx, 											
								vref,vref,WRDQ_TRAIN_VREF_STEP,										
								wrdq_train_delay_min,wrdq_train_delay_max,WRDQ_TRAIN_DELAY_STEP,	
								WRDQ_TRAIN_PASS_REGION_THLD,WRDQ_TRAIN_PASS_REGION_DIFF,
								(IPM_DBG_WRDQ && IPM_DBG_FIND_OPT) | (wrdq_delay_index_len<<16) | (WRDQ_TRAIN_VREF_MIN<<24) | (1<<31),						
								&vref_opt,&delay_opt,&pass_size_opt);					

				pass_size_sum+=pass_size_opt;
			}
    #if IPM_DBG_WRDQ
		  print_dbg("IPM:WRDQ:VREFOPT Ch%d Vref %d Pass_size_sum %d  E:\n", ch,vref,pass_size_sum);
    #endif
		if (pass_size_sum > max_pass_size_sum) {
		max_pass_size_sum=pass_size_sum;
		}
		vref_eye[vref]=pass_size_sum;
	}

  // Find the optimal vref as the center of all the vref eyes meeting width criteria
	unsigned int vref_opt_min=0;
	unsigned int vref_opt_max=0;
		for (unsigned int vref=WRDQ_TRAIN_VREF_MIN; vref<=WRDQ_TRAIN_VREF_MAX; vref+=WRDQ_TRAIN_VREF_STEP) {
		if (vref_eye[vref]>=(max_pass_size_sum-(PHY_DQS_WIDTH*WRDQ_TRAIN_PASS_REGION_DIFF))) {
		if (vref_opt_min==0) {
			vref_opt_min=vref;
			vref_opt_max=vref; //Vsi fix
		} else {
			vref_opt_max=vref;
		}
		}
	}
  vref_opt_allbyte=(vref_opt_min+vref_opt_max)/2;


	WRDQ_VREF_OPT[ch][TRN_IDX_GBL]=vref_opt_allbyte;

	result_size=0;
	result_size_optvref=0;

	// Now extract the delay data only corresponding to vref_opt_allbyte
	for (unsigned int vref=WRDQ_TRAIN_VREF_MIN; vref<=WRDQ_TRAIN_VREF_MAX; vref+=WRDQ_TRAIN_VREF_STEP) {
		for (unsigned int wdq_delay=wrdq_train_delay_min; wdq_delay<=wrdq_train_delay_max; wdq_delay+=WRDQ_TRAIN_DELAY_STEP) {
			if (vref==vref_opt_allbyte) {
				for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
					wrdq_training_optvref[result_size_optvref][byte_idx]=wrdq_training_result[result_size][byte_idx];
				}
				result_size_optvref++;
			}
			result_size++;
		}
	}

	int ret ;
	int avg_delay_opt=0;
	for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
		ret = find_optimal_com((uint8_t *)wrdq_training_result,PHY_DQS_WIDTH,								
						byte_idx,byte_idx, 												
                    	WRDQ_VREF_OPT[ch][TRN_IDX_GBL],WRDQ_VREF_OPT[ch][TRN_IDX_GBL],WRDQ_TRAIN_VREF_STEP,
                    	wrdq_train_delay_min,wrdq_train_delay_max,WRDQ_TRAIN_DELAY_STEP,
						WRDQ_TRAIN_PASS_REGION_THLD,WRDQ_TRAIN_PASS_REGION_DIFF,
                    	(IPM_DBG_WRDQ && IPM_DBG_FIND_OPT) | (wrdq_delay_index_len<<16) | (WRDQ_TRAIN_VREF_MIN<<24) | (1<<31),					
						&vref_opt,&delay_opt,&pass_size_opt);				
		if (ret == -1) {
			print_err("IPM:WRDQ: FIND_OPT_COM fail E:\n") ;
		}
		WRDQ_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=delay_opt;
		avg_delay_opt=avg_delay_opt+WRDQ_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL];
		if ((vref_opt==0) || (delay_opt==0) || (pass_size_opt==0) || (pass_size_opt>20) ) {
			pass_flag=0;
		}

	}
	avg_delay_opt=avg_delay_opt/PHY_DQS_WIDTH;

	// Check if all the delays are clustered around the mean
	// IPM seems to perform better on memtest when that happens
	for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
		int delay_diff = avg_delay_opt-WRDQ_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL];
		int diff_thold = (WRDQ_DIFF_TH*SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL])/100;

		if ((delay_diff > diff_thold) || (delay_diff < -1*diff_thold)) {
			pass_flag=0;
      print_err("IPM:WRDQ:  ERROR! WRDQ exceeding threshold for difference in trained value across bytes Ch%d Byte%0d: WRP_CODE %d Diff_thold %d WRDQ_DELAY_OPT : %0d AVG_DELAY_OPT %d Delay_diff %d Passflag %d  E:\n",
				ch,byte_idx, SDL_WRP_CODE_OPT_DQ[ch][byte_idx][TRN_IDX_GBL], diff_thold, WRDQ_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL],avg_delay_opt,delay_diff,pass_flag);
		}
		
	} 

	//Reset the pipeline controls
	reset_dqbyte_controls(0,PHY_DQS_WIDTH-1,ch);

	//Reset the pattern buffer
	reset_wdq_patbuf(ch);
	reset_rden_patbuf(ch);
	reset_rdq_patbuf(ch);
	reset_cc_patbuf(ch);
	
	return pass_flag;
}

void do_wrdq_training_writetrnval(unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

  //Set optimal vref
  print_info("IPM:WRDQ: Ch%d Writing the Optimal Vref %d E: \n",ch,WRDQ_VREF_OPT[ch][TRN_IDX_GBL]);
  set_wdq_vref(WRDQ_VREF_OPT[ch][TRN_IDX_GBL],ch);

  //Set optimal delays
  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
    print_info("IPM:WRDQ: Writing the values TRAINING_OPT(CH%0d): delay_byte%0d: %0d  E:\n",ch,byte_idx,WRDQ_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]);
    set_wdq_delay(WRDQ_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL], fsp, byte_idx, byte_idx,ch);
  }
}

void dq_patbuf_readout_cmpr(unsigned int *cmpr_fail, unsigned int row_start, unsigned int row_end, unsigned int ch) {
  unsigned int cmpr_fail_int[4];
  unsigned int wdq0_7,wdq8_15,wdq16;
  unsigned int rdq0_7,rdq8_15,rdq16;

  // Loop over each byte 
  for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH; byte_idx++) {
    cmpr_fail_int[byte_idx]=0;
    // Loop over each row
    for (unsigned int row_idx=row_start; row_idx<=row_end; row_idx++) {
      // Read contents of write dq pattern buffer
      wdq0_7 = apb_read_ch(WDQ_PTRNBUF_DQ0_PB0_0_ADDR+row_idx*6+byte_idx*96, ch);
      wdq8_15= apb_read_ch(WDQ_PTRNBUF_DQ8_PB0_0_ADDR+row_idx*6+byte_idx*96, ch);
      wdq16  = apb_read_ch(WDQ_PTRNBUF_DQ16_PB0_0_ADDR+row_idx*6+byte_idx*96, ch);

      // Read contents of read dq pattern buffer
      rdq0_7 = apb_read_ch(RDQ_PTRNBUF_DQ0_PB0_0_ADDR+row_idx*6+byte_idx*96, ch);
      rdq8_15= apb_read_ch(RDQ_PTRNBUF_DQ8_PB0_0_ADDR+row_idx*6+byte_idx*96, ch);
      rdq16  = apb_read_ch(RDQ_PTRNBUF_DQ16_PB0_0_ADDR+row_idx*6+byte_idx*96, ch);   

      // Compare the read and write pattern buffer contents
      if ((wdq0_7 != rdq0_7) || (wdq8_15 != rdq8_15) || (wdq16 != rdq16)) {
        cmpr_fail_int[byte_idx]=1;
      }

      // Display contents of buffer
      print_dbg("IPM:DRAM R/W: Byte%d Row%d Wdq0_7 0x%x Wdq8_15 0x%x Wdq16 0x%x Rdq0_7 0x%x Rdq8_15 0x%x Rdq16 0x%x CmprFail %d E: \n",byte_idx,row_idx,wdq0_7,wdq8_15,wdq16,rdq0_7,rdq8_15,rdq16,cmpr_fail_int[byte_idx]);
      
    }
    // Set bits of cmpr_fail
    BIT_SET(*cmpr_fail,byte_idx,cmpr_fail_int[byte_idx]);
  }
}

void do_dramfifo_rw_top( unsigned int fsp, unsigned int freq_ratio, unsigned int freq_idx, unsigned int ch) {

  unsigned int cmpr_fail=0;
  unsigned int twrlat=T_PHY_WRLAT[TRN_IDX_GBL]-1;

  // Reset the pattern buffers first
  reset_wdq_patbuf(ch);
  reset_rden_patbuf(ch);
  reset_rdq_patbuf(ch);
  reset_cc_patbuf(ch);

  // Setup pattern buffers for DRAM FIFO R/W
	set_wrdq_patbuf_new(fsp,freq_ratio,freq_idx,twrlat,ch);

  // Reset and release fifo point unsigneders etc to start clean every iteration
  reset_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
  reset_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
  reset_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

  reset_release_dqbyte_fifoptr(0,PHY_DQS_WIDTH-1,ch);
  reset_release_dqbyte_rdqsen(0,PHY_DQS_WIDTH-1,ch);
  reset_release_dqbyte_edgecomb(0,PHY_DQS_WIDTH-1,ch);

  // Issue MPC WRFIFO 
  send_mpc_through_ptrn_buf(MPC_WR_FIFO,NOSEND,ch);
  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CC|PTRN_EN_DQWR_DATA,ch);
  wait_ptrn_done(ch);
  delay(t_WTR);

  // Issue MPC RDFIFO 
  send_mpc_through_ptrn_buf(MPC_RD_FIFO,NOSEND,ch);
  apb_write_ch(CC_PTRN_EN_ADDR,PTRN_EN_CC|PTRN_EN_DQRD_EN|PTRN_EN_DQRD_DATA,ch);
  wait_ptrn_done(ch);

  delay(t_WRDQ_TRAIN_STEP);

  // Compare the contents of the read and write pattern buffer
  // We are not using the built in hardware comparator. Instead we are
  // reading out both pattern buffers and comparing them in firmware
  dq_patbuf_readout_cmpr(&cmpr_fail, 4,7,ch);

  print_info("IPM:RWCHK: Post training DRAM FIFO R/W Compare Fail Status Byte3:0 0x%x E: \n",BITS_GET(cmpr_fail,3,0));

}

void phy_training(unsigned int ch_min, unsigned int ch_max) {

  // Save dfi_init_start protocol parameters
  unsigned int req_fsp[2];
  unsigned int req_freq_ratio[2];
  unsigned int req_freq_idx[2];

  // Options to bypass training
  unsigned int bypass_ca_training;
  unsigned int bypass_wrlvl_training;
  unsigned int bypass_rdpre_training;
  unsigned int bypass_rddq_training;
  unsigned int bypass_wrdq_training;
  unsigned int bypass_lpbk_training;
  unsigned int bypass_cross_training;
  unsigned int bypass_dramfifo_rw;

  // Retraining
  unsigned int need_to_train;
  unsigned int need_to_train_phy;
  unsigned int read_data;

  //--------------------------------------------------------------------
  // Clear the scratchpad for retraining case and free up space
  //--------------------------------------------------------------------
  if ((TRN_IDX_GBL==1) || (TRN_IDX_GBL==3)) {
    clear_scratchpad();
  }

  //--------------------------------------------------------------------
  // Clear the dfi_complete. This is required for retrain and optional for
  // initial training
  //--------------------------------------------------------------------
  delay(10);
  for(unsigned int ch=GLB_CH_MIN;ch<GLB_CH_MAX+1;ch++) {
    apb_write_field_ch(M_DFI_INIT_COMPLETE,0b0,ch);
  }

  // Print channels being trained
  print_info("IPM:INIT: Ch-min %0d, Ch-max %0d E:\n",ch_min,ch_max);

  //--------------------------------------------------------------------
  // Read DLL accumulator contents to check RTL FIX during initial training
  //--------------------------------------------------------------------
  if ((TRN_IDX_GBL==0) || (TRN_IDX_GBL==2)) {
    do_read_dll_accum_rst();
  }

  //--------------------------------------------------------------------
  // Set global variables: Moved to phy_init() since it is used only 
  // during initial training
  //--------------------------------------------------------------------

  //----------------------------------------------------------------
  // Assert training_en. This must be done for both channels always
  //----------------------------------------------------------------
  for(unsigned int ch=GLB_CH_MIN;ch<GLB_CH_MAX+1;ch++) {
    print_info("IPM:INIT: Assert training_en Ch%d E:\n",ch);
    apb_write_field_ch(M_TRAINING_EN,0b1,ch);
  }

  //------------------------------------------------------------------------------------
  // DRAM initialization. This must be done for both channels always
  //------------------------------------------------------------------------------------
  if ((TRN_IDX_GBL==0) || (TRN_IDX_GBL==2)) {
    print_info("IPM:INIT: Initialize DRAM both channels E:\n");
    dram_init(ch_min,ch_max);
  }

  //------------------------------------------------------------------------------------
  // Issue self-refresh entry
  // TBD: resolve between self-refresh and powerdown state below
  // This step may be redundant for retraining if MC already puts the PHY in self-refresh
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    print_info("IPM:INIT: Issue self-refresh entry Ch%d E:\n",ch);
    send_sre_through_ptrn_buf(ch);
  }

  //------------------------------------------------------------------------------------
  // Put both channels in powerdown state. i.e. CK stopped, CKE=low, resetn=1 PHY clken=0
  // This will allow us to work on one channel without affecting the other
  // This must be done for both channels always
  //------------------------------------------------------------------------------------
  #if SI_ENV
    for(unsigned int ch=GLB_CH_MIN;ch<GLB_CH_MAX+1;ch++) {
      print_info("IPM:INIT: Putting Ch%d in powerdown state E:\n",ch);
      shut_down_chnl(ch);
    }
  #endif

  //------------------------------------------------------------------------------------
  // Process FSP etc..
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {

    read_data =     apb_read_ch(DFI_FREQ_RATIO_ADDR, ch);
    req_freq_ratio[ch] = BITS_GET(read_data,1,0);
    req_fsp[ch]        = BITS_GET(read_data,3,2);
    req_freq_idx[ch]   = BITS_GET(read_data,8,4);

    TRN_IDX_GBL=99; // Just a big number for error checking

    for(unsigned int i=0; i<TOTAL_TRN_IDX; i++) {
      if (req_freq_idx[ch] == TRN_SCN[i].freq_idx) {
        TRN_IDX_GBL = i;
      }
    }
    print_info("IPM:INIT: Ch%d freq_ratio=%d fsp=%d freq_index=%d TRN Idx=%d E:\n", 
                ch,req_freq_ratio[ch],req_fsp[ch],req_freq_idx[ch],TRN_IDX_GBL);
    if (TRN_IDX_GBL > (TOTAL_TRN_IDX-1)) {
      print_err("IPM:INIT: ERROR! Invalid TRN_IDX_GBL. Please check freq_idx E:\n");
    }
  }

  //------------------------------------------------------------------------------------
  // Configure DRAM timng
  //------------------------------------------------------------------------------------
  if ((TRN_IDX_GBL==0) || (TRN_IDX_GBL==2)) {
    for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
      print_info("IPM:INIT: Configuring DRAM timing parameters E:\n", req_freq_ratio[ch],req_fsp[ch],req_freq_idx[ch],TRN_IDX_GBL);
      config_dfi_dram_timing(req_fsp[ch], req_freq_ratio[ch], req_freq_idx[ch],ch);
    }
  }

  //------------------------------------------------------------------------------------
  // Set PBD cap_en to be same as sdl cap_en. This is to ensure enuff separation between CA and CS during CA training
  //------------------------------------------------------------------------------------
  if ((TRN_IDX_GBL==0) || (TRN_IDX_GBL==2)) {
    for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
      set_pbd_cap_en(req_fsp[ch],ch);
    }
  }

  //------------------------------------------------------------------------------------
  // Set flags for Training/bypass training
  // BYPASS_TRAINING_2: Completely skip training and bypass training. Used for debug
  // BYPASS_TRAINING_1: Bypass training and use predefined training defaults
  // If neither of the above is supplied it defaults to training
  //------------------------------------------------------------------------------------
  #ifdef BYPASS_TRAINING_2
    print_info("IPM:INIT: Bypass training mode2 E:\n");
    bypass_ca_training   =2;
    bypass_wrlvl_training=2;
    bypass_rdpre_training=2;
    bypass_rddq_training= 2;
    bypass_wrdq_training= 2;
    bypass_lpbk_training= 2;
    bypass_cross_training=2;
    bypass_dramfifo_rw=2;
 #elif BYPASS_TRAINING_1
    print_info("IPM:INIT: Bypass training mode1 E:\n");
    bypass_ca_training   =1;
    bypass_wrlvl_training=1;
    bypass_rdpre_training=1;
    bypass_rddq_training= 1;
    bypass_wrdq_training= 1;
    bypass_lpbk_training= 1;
    bypass_cross_training=1;
    bypass_dramfifo_rw=0;
  #else 
    print_info("IPM:INIT: Training mode E:\n");
    if ((TRN_IDX_GBL==0) || (TRN_IDX_GBL==2)) {
      bypass_ca_training   =0;
      bypass_wrlvl_training=0;
      bypass_rdpre_training=0;
      bypass_rddq_training= 0;
      bypass_wrdq_training= 0;
      bypass_lpbk_training= 1; // Retraining not needed
      bypass_cross_training=1; // Retraining not needed
      bypass_dramfifo_rw=0;
    } else {
      bypass_ca_training   =CA_RETRAIN;
      bypass_wrlvl_training=WRLVL_RETRAIN;
      bypass_rdpre_training=RDPRE_RETRAIN;
      bypass_rddq_training= RDDQ_RETRAIN;
      bypass_wrdq_training= WRDQ_RETRAIN;
      bypass_lpbk_training= LPBK_RETRAIN;
      bypass_cross_training=CROSS_RETRAIN;
      bypass_dramfifo_rw=0;
    }
  #endif

  print_info("IPM:INIT: Training Requested: Lpbk %d Cross %d CA %d Wrlvl %d Rdpre %d Rddq %d Wrdq %d  DRAM Fifo R/W %dE:\n",
              (1-bypass_lpbk_training),(1-bypass_cross_training),(1-bypass_ca_training),(1-bypass_wrlvl_training),
              (1-bypass_rdpre_training),(1-bypass_rddq_training),(1-bypass_wrdq_training),(1-bypass_dramfifo_rw));

 // print_info("IPM: Sizeoflog1 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Serializer stage_sel
  // Reset value is "0". Shud not need to change this.
  // Including here for testing or incase we need to play with it
  //------------------------------------------------------------------------------------
  if ((TRN_IDX_GBL==0) || (TRN_IDX_GBL==2)) {
    for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
      for (unsigned int byte_idx=0;byte_idx<PHY_DQS_WIDTH;byte_idx++) {
        apb_write_field_ch(M_SER_RESET_STAGESEL_WR_PIPE[byte_idx],0,ch);
        apb_write_field_ch(M_SER_RESET_STAGESEL_RD_PIPE[byte_idx],0,ch);
      }
      apb_write_field_ch(M_SER_RESET_STAGESEL_CMD,0,ch);
    }
  }

	//------------------------------------------------------------------------------------
	// Turn on PLL for lpbk, cross-sel training
	//------------------------------------------------------------------------------------
  if ((TRN_IDX_GBL==0) || (TRN_IDX_GBL==2)) {
    if ((bypass_lpbk_training==0b0) || (bypass_cross_training==0b0)) {
      print_info("IPM:PLL/DLL-1:------------PLL/DLL first lock    ---------------- E:\n") ;
      pll_freq_change_procedure(req_fsp[0],req_freq_ratio[0],req_freq_idx[0],0b11,0b11,0);
    }
  }

	//------------------------------------------------------------------------------------
  // DQ Loopback to get lpbk timing settings for use in cross-sel training
  //------------------------------------------------------------------------------------
	if (bypass_lpbk_training==0b0) {
		for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
			print_info("IPM:LPBK-Ser:------------LPBK Training  ch%d  ----------------- E:\n",ch) ;
			do_dq_patbuf_lpbk(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
		}
	} else if (bypass_lpbk_training==0b1) {
		for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
			print_info("IPM:LPBK-Ser:------------LPBK Bypass  ch%d  ------------------- E:\n",ch) ;
			do_dq_patbuf_lpbk_bypass(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }
  }
  //print_info("IPM: Sizeoflog2 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Cross-sel training for getting xover thresholds and  wrp_code
  //------------------------------------------------------------------------------------
	if (bypass_cross_training==0b0) {
		for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
			print_info("IPM:LPBK-Ser:------------Cross-sel Training  ch%d  ------------- E:\n",ch) ;
			do_cross_sel_training(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
		}
	} else if (bypass_cross_training==0b1) {
		for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
			print_info("IPM:LPBK-Ser:------------Cross-sel Bypass   ch%d  ------------- E:\n",ch) ;
			do_cross_sel_bypass(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }
  }
 // print_info("IPM: Sizeoflog3 %d E:\n",sizeoflog);

	//------------------------------------------------------------------------------------
  // Reinitialize completely after cross-sel. CA training seems to be sensitive to Prior PLL
  // lock
	//------------------------------------------------------------------------------------
  #if SI_ENV
    if ((bypass_lpbk_training==0b0) || (bypass_cross_training==0b0)) {
      phy_init(ch_min,ch_max);
      dram_set_and_release_reset();
      print_dbg("IPM:INIT: Re-Initialize DRAM after cross sel training Ch%d\n",ch);
      dram_init(ch_min,ch_max);
      for(unsigned int ch=GLB_CH_MIN;ch<GLB_CH_MAX+1;ch++) {
          shut_down_chnl(ch);
          delay(1);
      }
    }
  #endif
  //print_info("IPM: Sizeoflog4 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // CA  Training
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    #if SI_ENV
      // Wake up the channel
      wake_up_chnl(ch);
    #else
      enable_ch(0b11,0b11,ch);
    #endif

    if (bypass_ca_training==0b0) {
      print_info("IPM:CA:------------ IPM CA TRAINING ch%d ----------------E:\n", ch) ;
      do_ca_training_top(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    } else if (bypass_ca_training==0b1) {
      print_info("IPM:CA:------------ IPM CA BYPASS ch%d  -----------------E:\n", ch) ;
      // CA Training optima for 2133Mbps verilog sims
      CC_VREF_OPT[ch][TRN_IDX_GBL]=32;
      CC_DELAY_OPT[ch][TRN_IDX_GBL]=94;
      do_ca_training_bypass(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }

    #if SI_ENV
      // Shut down the channel once training is done.
      shut_down_chnl(ch);
    #else
      disable_ch(0b00,0b11,ch);
    #endif
  }
 // print_info("IPM: Sizeoflog5 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Once CA training/bypass is done relock the PLL
  //------------------------------------------------------------------------------------
  if (bypass_ca_training <2) {
    print_info("IPM:CA: Relocking PLL/DLL after CA training -------------E:\n");
    pll_freq_change_procedure_alt(req_fsp[ch_min],req_freq_ratio[ch_min],req_freq_idx[ch_min],0b11,0b11,1);
  }
 // print_info("IPM: Sizeoflog6 %d E:\n",sizeoflog);

  //--------------------------------------------------------------------------------------
  // Wake up the required channels. No need to turn them off anymore
  //--------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    print_info("IPM: Waking up Ch%d  E:\n",ch);
    #if SI_ENV
      wake_up_chnl(ch);
    #else
      enable_ch(0b11,0b11,ch);
    #endif
  }

  //------------------------------------------------------------------------------------
  // Wrlvl training
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    if (bypass_wrlvl_training==0b0) {
      print_info("IPM:WRLVL: ------------ WRLVL TRAINING Ch%d  ----------------E:\n",ch);
      do_wrlvl_training_top(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
      // Write the optimal value
      do_wrlvl_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    } else if (bypass_wrlvl_training==0b1) {
      print_info("IPM:WRLVL: ------------ WRLVL BYPASS Ch%d  ------------------E:\n",ch);
      for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH;byte_idx++) {
        WRLVL_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=147;
      }
      // Write the optimal value
      do_wrlvl_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }
  }

  //---------------------------------------
	// Set DRAM timings
	//---------------------------------------
	for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    if (bypass_rdpre_training< 2) {
		  set_dram_timings(req_freq_idx[ch],ch);
    }
	}
 // print_info("IPM: Sizeoflog7 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Rdpreamble training
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    if (bypass_rdpre_training==0b0) {
      print_info("IPM:RDPRE: ------------ RDPRE TRAINING Ch%d-------------------E:\n",ch);
      do_rdpre_training_top(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],1,ch);
      // Write the optimal value
      do_rdpre_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    } else if (bypass_rdpre_training==0b1) {
      print_info("IPM:RDPRE: ------------ RDPRE BYPASS Ch%d--------------------E:\n",ch);
      for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH;byte_idx++) {
        RDEN_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=173;
      }
      // Write the optimal value
      do_rdpre_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }
  }
  //print_info("IPM: Sizeoflog8 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Rd DQ Training
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    if (bypass_rddq_training==0b0) {
      print_info("IPM:RDDQ: ------------ RDDQ TRAINING Ch%d-------------------E:\n",ch);
      do_rddq_training_top(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
      // Write the optimal value
      do_rddq_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    } else if (bypass_rddq_training==0b1) {
      print_info("IPM:RDDQ: ------------ RDDQ BYPASS Ch%d---------------------E:\n",ch);
      for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH;byte_idx++) {
        RDQS_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=12;
        RDQ_VREF_OPT[ch][byte_idx][TRN_IDX_GBL]=100;
      }
      // Write the optimal value
      do_rddq_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }
  }
//  print_info("IPM: Sizeoflog9 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Wr DQ Training
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    if (bypass_wrdq_training==0b0) {
      print_info("IPM:WRDQ: ------------ WRDQ TRAINING Ch%d-------------------E:\n",ch);
      do_wrdq_training_top(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
      //Write the optimal value
      do_wrdq_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    } else if (bypass_wrdq_training==0b1) {
      print_info("IPM:WRDQ: ------------ WRDQ BYPASS Ch%d---------------------E:\n",ch);
      for (unsigned int byte_idx=0; byte_idx<PHY_DQS_WIDTH;byte_idx++) {
        WRDQ_DELAY_OPT[ch][byte_idx][TRN_IDX_GBL]=103;
      }
      WRDQ_VREF_OPT[ch][TRN_IDX_GBL]=32; // Common for all bytes
      //Write the optimal value
      do_wrdq_training_writetrnval(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }
  }
 // print_info("IPM: Sizeoflog10 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Verify training works by doing DRAM FIFO read/write operation
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    if (bypass_dramfifo_rw==0b0) {
      print_info("IPM:RWCHK: -------- DRAM FIFO R/W Check Ch%d-----------------E:\n",ch);
      do_dramfifo_rw_top(req_fsp[ch],req_freq_ratio[ch],req_freq_idx[ch],ch);
    }
  }
 // print_info("IPM: Sizeoflog11 %d E:\n",sizeoflog);

  //------------------------------------------------------------------------------------
  // Wrap up the training
  //------------------------------------------------------------------------------------
  for(unsigned int ch=ch_min;ch<ch_max+1;ch++) {
    //Set BL=16. MR1; op[1:0]=2'b01
    // BCA firmware tests use BL 16 after exiting training
    // Customer can override this on their MC side if required.
    BITS_SET(MRW_DATA[ch][1],1,0,0b01);
    send_mrw_through_ptrn_buf(1,ch);

    // De-assert training enable
    apb_write_field_ch(M_TRAINING_EN,0b0,ch);
    // Assert init_complete
    apb_write_field_ch(M_INTR_DFI_INIT_START,0b1,ch);
    // Clear interrupt
    apb_write_ch(DFI_INIT_COMPLETE_ADDR,0b1,ch);
  }

}
