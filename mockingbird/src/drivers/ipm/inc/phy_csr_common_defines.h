// Copyright (c) 2020 Blue Cheetah Analog Design, Inc. 
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.

// Set to zero for NMOS based pullup
#define CSR_CACS_TX_SEL_PUNB  0x0
#define CSR_CK_TX_SEL_PUNB  0x0
#define CSR_HV_TX_SEL_PUNB  0x0
#define CSR_DQDM_TX_SEL_PUNB  0x0
#define CSR_DQS_TX_SEL_PUNB  0x0

#define CSR_DQS_RD_EN_SEL  0x1

#define CSR_CACS_TX_DCODE_IDLEB  0x1
#define CSR_CK_TX_DCODE_IDLEB  0x1
#define CSR_HV_TX_DCODE_IDLEB  0x1
#define CSR_DQDM_TX_DCODE_IDLEB  0x1
#define CSR_DQSC_TX_DCODE_IDLEB  0x0
#define CSR_DQST_TX_DCODE_IDLEB  0x1

#define CSR_DQS_RXPBD_EDGE_RESETB  0x1

#define CSR_CA_MDL_LPBKENB  0x1

#define CSR_CACS_TX_ZCODE  0x1f
#define CSR_CK_TX_ZCODE  0x1f
#define CSR_HV_TX_ZCODE  0x1f
#define CSR_DQDM_TX_ZCODE  0x1f
#define CSR_DQS_TX_ZCODE  0x1f

#define CSR_CACS_TX_XOVER_FINE_CROSS_SEL  0x0
#define CSR_CK_TX_XOVER_FINE_CROSS_SEL  0x0
#define CSR_HV_TX_XOVER_FINE_CROSS_SEL  0x0
#define CSR_DQDM_TX_XOVER_FINE_CROSS_SEL  0x0
#define CSR_DQS_TX_XOVER_FINE_CROSS_SEL  0x0
#define CSR_DQS_RX_XOVER_FINE_CROSS_SEL  0x0
#define CSR_DQS_MDL_XOVER_FINE_CROSS_SEL  0x0

#define CSR_CACS_TX_DUTY_PN  0x1
#define CSR_CK_TX_DUTY_PN  0x1
#define CSR_HV_TX_DUTY_PN  0x1
#define CSR_DQDM_TX_DUTY_PN  0x1
#define CSR_DQS_TX_DUTY_PN  0x1

#define CSR_DQDM_RX_DQ_FE_DAC_MAIN  64
#define CSR_DQDM_RX_DQ_FE_DAC_KICK_HB  3
#define CSR_DQDM_RX_DQ_FE_DAC_KICK_LB  3
#define CSR_DQDM_RX_DQ_FE_DAC_ENB  0x0
#define CSR_DQDM_RX_DQ_FE_EN  0x1

#define CSR_CACS_TX_DRVEN_ON  0x1
#define CSR_CK_TX_DRVEN_ON  0x1
#define CSR_HV_TX_DRVEN_ON  0x1

#define CSR_RETRAIN_REF_PER_MULT 1000
#define CSR_RETRAIN_CYCLES 1

// SL1 : Both 0 or 2 will work . 
#define CSR_DQ_SER_RESET_STAGESEL 0
#define CSR_CA_SER_RESET_STAGESEL 0
	

