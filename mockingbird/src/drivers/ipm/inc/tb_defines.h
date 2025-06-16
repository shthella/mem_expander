// Copyright (c) 2020 Blue Cheetah Analog Design, Inc. 
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.




#define VIP_APB_ADDR_WIDTH  32
#define PHY_APB_ADDR_WIDTH  17
#define CSR_APB_ADDR_WIDTH  16
#define APB_DATA_WIDTH      16
#define MCU_ADDR_OFFSET_CSR   0x1000
#define MCU_ADDR_OFFSET_IMEM  0x2000

#define IPM_DRAM

#define PHY_NUM_CH 2
#define PHY_DQ_PER_DQS 17
#define PHY_DQS_PC_WIDTH 2
#define PHY_NUM_PC 2
#define PHY_DQ_PC_WIDTH (PHY_DQ_PER_DQS*PHY_DQS_PC_WIDTH)  //34
#define PHY_DQS_WIDTH (PHY_DQS_PC_WIDTH*PHY_NUM_PC)  //4
#define PHY_DQ_WIDTH (PHY_DQ_PC_WIDTH*PHY_NUM_PC)
#define PHY_MIN_BL 8
#define PHY_PREFETCH_SIZE (PHY_DQ_PC_WIDTH*PHY_MIN_BL)
#define PHY_NUM_MR 256
#define PHY_MR_WIDTH 8
#define PHY_CA_WIDTH 10
#define PHY_BADDR_WIDTH 4
#define PHY_RADDR_WIDTH 15
#define PHY_CADDR_WIDTH 5
#define PHY_TDQS2DQ_PS 200
#define PHY_TCK_PS 937.5
#define HALF_PERIOD_PHY_CLK 1  //234ps

//#define PHY_IF_PARAM (.CA_BITS(PHY_CA_WIDTH), .DQS_BITS(PHY_DQS_WIDTH*2), .DQ_BITS(PHY_DQ_WIDTH))
//#define PHY_MON_PARAM (.DQ_PER_DQS(PHY_DQ_PER_DQS), .DQS_PC_WIDTH(PHY_DQS_PC_WIDTH), .DQS_WIDTH(PHY_DQS_WIDTH*2), .DQ_WIDTH(PHY_DQ_WIDTH), .MIN_BL(PHY_MIN_BL), .PREFETCH_SIZE(PHY_PREFETCH_SIZE), .NUM_MR(PHY_NUM_MR),\
//                       .MR_WIDTH(PHY_MR_WIDTH), .CA_WIDTH(PHY_CA_WIDTH), .BADDR_WIDTH(PHY_BADDR_WIDTH), .RADDR_WIDTH(PHY_RADDR_WIDTH), .CADDR_WIDTH(PHY_CADDR_WIDTH), .TDQS2DQ_PS(PHY_TDQS2DQ_PS), .TCK_PS(PHY_TCK_PS))
//
//#define CH_A $root.top.IPM_PHY_DUT.ipm_ch_0
//#define CH_B $root.top.IPM_PHY_DUT.ipm_ch_1
