// Copyright (c) 2020 Blue Cheetah Analog Design, Inc. 
// All Rights Reserved.
// The information contained herein is confidential and proprietary information
// of Blue Cheetah Analog Design, Inc. and its licensors, if any, and is
// subject to applicable non-disclosure agreement with Blue Cheetah Analog
// Design, Inc. Dissemination of information, use of this material, or
// reproduction of this material is strictly forbidden unless prior written
// permission is obtained from Blue Cheetah Analog Design, Inc.

#ifndef REG_MNEMONICS_COMPRESSED_H
#define REG_MNEMONICS_COMPRESSED_H

#include <stdint.h>

extern const uint32_t M_WDQ_PTRNBUF_DQ_MIN[17];
extern const uint32_t M_RDQ_PTRNBUF_DQ_MIN[17];
extern const uint32_t M_CC_PTRNBUF_CA_MIN[10];

#endif


typedef struct {
  uint32_t start_code;
  uint8_t num_intervals_0;
  uint8_t num_intervals_1;
} __attribute__ ((aligned (4), packed)) interval_header_t;

typedef struct {
  int index : 7;
  signed int stride : 25;
} __attribute__ ((aligned (4), packed)) single_interval_t;

typedef struct {
  interval_header_t header;
  single_interval_t strides[];
} mn_intervals_t;

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_CKT_stride = {
  .header = { .start_code = 528904, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_DQ_PRBS_ERROR_COUNT_PIN_stride = {
  .header = { .start_code = 520095608, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 2, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 6 }
};

static const mn_intervals_t M_WRITE_EN_EARLY_PIPE_STRETCH_stride = {
  .header = { .start_code = 50331904, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_RESULT_PRBS_CA_stride = {
  .header = { .start_code = 285214994, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 7, .stride = 2097152 },
  .strides[1] = { .index = 8, .stride = -14680062 },
  .strides[2] = { .index = 9, .stride = 2097152 }
};

static const mn_intervals_t M_ANA_LPBK_SEL_DQS_stride = {
  .header = { .start_code = 19456, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_DMI_stride = {
  .header = { .start_code = 144963, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_CA_stride = {
  .header = { .start_code = 2761220, .num_intervals_0 = 1, .num_intervals_1 = 3 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 5, .stride = 6 },
  .strides[2] = { .index = 6, .stride = -8218 },
  .strides[3] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_CROSS_RESETN_DQST_stride = {
  .header = { .start_code = 280077, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_RX_TXPBD_BANK_EN_DQS_stride = {
  .header = { .start_code = 541188, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDEN_PTRNBUF_START_PTR_stride = {
  .header = { .start_code = 117441632, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_ZCODE_PI_CA_stride = {
  .header = { .start_code = 5254145, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_DMI_stride = {
  .header = { .start_code = 2765380, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_CKE_stride = {
  .header = { .start_code = 528898, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_DQ_PRBSCHECK_FAIL_PIN_ID_stride = {
  .header = { .start_code = 67110736, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 2, .stride = 5242880 },
  .strides[1] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_RXSDL_BANK_EN_F_DQS_stride = {
  .header = { .start_code = 3163143, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ZCODE_PUW_DQST_stride = {
  .header = { .start_code = 5262346, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CHC_PRBSCHECK_FAIL_PIN_ID_stride = {
  .header = { .start_code = 67111200, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 2, .stride = 5242880 }
};

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_CKC_stride = {
  .header = { .start_code = 528910, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_HIZ_CA_stride = {
  .header = { .start_code = 863232, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_CS_stride = {
  .header = { .start_code = 2753056, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 196608 }
};

static const mn_intervals_t M_MIN_OSC_CNT_stride = {
  .header = { .start_code = 251660692, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_DQ_stride = {
  .header = { .start_code = 22023, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_RX_RXPBD_CTRL_F_DQS_stride = {
  .header = { .start_code = 3687432, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_SDL_CK_BANK_EN_stride = {
  .header = { .start_code = 3412498, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_OVR_RDQSEN_stride = {
  .header = { .start_code = 29360544, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_INV_SEL_DQS_stride = {
  .header = { .start_code = 216064, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CC_PRBS_ERROR_COUNT_CHC_stride = {
  .header = { .start_code = 419432730, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 2, .stride = 2 }
};

static const mn_intervals_t M_ANA_RXSDL_CTRL_F_DQS_stride = {
  .header = { .start_code = 1328134, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_T_TX_PBD_CTRL_DQS_stride = {
  .header = { .start_code = 3162638, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_RSTN_stride = {
  .header = { .start_code = 3146242, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_CA_stride = {
  .header = { .start_code = 3154436, .num_intervals_0 = 1, .num_intervals_1 = 3 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 5, .stride = 6 },
  .strides[2] = { .index = 6, .stride = -8218 },
  .strides[3] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_HB_DMI_F_stride = {
  .header = { .start_code = 1587260, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TXSDL_BANK_EN_DQS_stride = {
  .header = { .start_code = 3424770, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_LD_CNT_RD_PIPE_stride = {
  .header = { .start_code = 36700584, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_DQ_stride = {
  .header = { .start_code = 3166728, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_TX_PBD_DUTYB_CTRLP_RSTN_stride = {
  .header = { .start_code = 1049091, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_PLL_ACCUM_OVRD_VAL_HI_stride = {
  .header = { .start_code = 117567506, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 2, .stride = 4 }
};

static const mn_intervals_t M_ANA_HIZ_DQSC_stride = {
  .header = { .start_code = 871440, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_RX_TXPBD_CAP_EN_DQS_stride = {
  .header = { .start_code = 2769412, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTYB_P_DQ_stride = {
  .header = { .start_code = 1069577, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_HB_DMI_R_stride = {
  .header = { .start_code = 1587262, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_PBD_DUTY_CTRLN_CKE_stride = {
  .header = { .start_code = 1315331, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_RDQSODTEN_PIPE_DLY_stride = {
  .header = { .start_code = 50331792, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_DUTY_N_CKC_stride = {
  .header = { .start_code = 1315343, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_DQRD_EN_PTRN_EN_stride = {
  .header = { .start_code = 6293430, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_READ_EN_EARLY_PIPE_DLY_stride = {
  .header = { .start_code = 50331808, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_RETRAIN_REF_PER_MULT_stride = {
  .header = { .start_code = 251660676, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_DQ_PRBSGEN_ID_DQ_stride = {
  .header = { .start_code = 16779056, .num_intervals_0 = 4, .num_intervals_1 = 1 },
  .strides[0] = { .index = 7, .stride = 2097152 },
  .strides[1] = { .index = 8, .stride = -14680062 },
  .strides[2] = { .index = 15, .stride = 2097152 },
  .strides[3] = { .index = 16, .stride = -14680062 },
  .strides[4] = { .index = 3, .stride = 6 }
};

static const mn_intervals_t M_ANA_HIZ_DQ_stride = {
  .header = { .start_code = 875524, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_DQWR_DATA_PTRN_EN_stride = {
  .header = { .start_code = 2099126, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_CCHVCK_CROSS_SEL_stride = {
  .header = { .start_code = 2002, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 2 }
};

static const mn_intervals_t M_DQ_PRBS_ERROR_COUNT_stride = {
  .header = { .start_code = 520095600, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_RDQ_PTRNBUF_START_PTR_stride = {
  .header = { .start_code = 117441904, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DUTY_N_CKT_stride = {
  .header = { .start_code = 1315337, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_DQ_stride = {
  .header = { .start_code = 153095, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_NEED_TO_RETRAIN_stride = {
  .header = { .start_code = 276826540, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_ZCODE_X_CA_stride = {
  .header = { .start_code = 5647360, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_DMI_stride = {
  .header = { .start_code = 3158596, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_DQST_stride = {
  .header = { .start_code = 17933, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQS_RD_EN_SEL_stride = {
  .header = { .start_code = 84992, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTY_N_DMI_stride = {
  .header = { .start_code = 1323589, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTYB_P_DQS_stride = {
  .header = { .start_code = 1065477, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CKHV_PTRNBUF_CKDIS_stride = {
  .header = { .start_code = 20973814, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_DQST_stride = {
  .header = { .start_code = 149005, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_ENB_DMI_R_stride = {
  .header = { .start_code = 800830, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ZCODE_PI_DMI_stride = {
  .header = { .start_code = 5258305, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_DMI_stride = {
  .header = { .start_code = 13891, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDEN_PTRNBUF_RD_CS_stride = {
  .header = { .start_code = 1049840, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 32 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_RSTN_stride = {
  .header = { .start_code = 2753026, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 196608 }
};

static const mn_intervals_t M_ANA_DQ_CROSS_SEL_stride = {
  .header = { .start_code = 17942, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTYB_P_CKC_stride = {
  .header = { .start_code = 1053199, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_ANA_ZCODE_PUW_CA_stride = {
  .header = { .start_code = 5254144, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_CKC_stride = {
  .header = { .start_code = 2757134, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 196608 }
};

static const mn_intervals_t M_DQ_PRBS_GEN_EN_stride = {
  .header = { .start_code = 1980, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_ANA_SDL_CA_BANK_EN_stride = {
  .header = { .start_code = 3412496, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_ANA_SHDL_CAP_EN_DQS_stride = {
  .header = { .start_code = 2892837, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = -786431 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_ANA_SDL_DQ_BANK_EN_stride = {
  .header = { .start_code = 3424796, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQS_RESET_stride = {
  .header = { .start_code = 150528, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_SEL_PUNB_DMI_stride = {
  .header = { .start_code = 801856, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RETRAIN_CYCLES_stride = {
  .header = { .start_code = 117442980, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_ENB_DMI_F_stride = {
  .header = { .start_code = 800828, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDEN_PTRNBUF_DELAY_stride = {
  .header = { .start_code = 67110000, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 32 }
};

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_DQ_stride = {
  .header = { .start_code = 545288, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_PBD_DQS_CAP_EN_stride = {
  .header = { .start_code = 2769434, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ODTEN_CA_stride = {
  .header = { .start_code = 928768, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_TX_C_TX_PBD_CTRL_DQS_stride = {
  .header = { .start_code = 3162644, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ZCODE_PDR_DQST_stride = {
  .header = { .start_code = 5262348, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_T_TX_PBD_BANK_EN_DQS_stride = {
  .header = { .start_code = 541198, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_LD_CNT_WR_PIPE_stride = {
  .header = { .start_code = 33554856, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DQ_RISE_RX_PBD_CTRL_DMI_R_stride = {
  .header = { .start_code = 3159103, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_RX_RXPBD_CTRL_R_DQS_stride = {
  .header = { .start_code = 3163144, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_WDQ_PTRNBUF_WR_CS_stride = {
  .header = { .start_code = 1049568, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 32 }
};

static const mn_intervals_t M_RETRAIN_CNT_stride = {
  .header = { .start_code = 385878444, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DUTYB_P_DQST_stride = {
  .header = { .start_code = 1065487, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ZCODE_PDW_DMI_stride = {
  .header = { .start_code = 5651521, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_SDL_HV_CTRL_stride = {
  .header = { .start_code = 1053204, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_ANA_TX_PBD_DUTYB_CTRLP_CKE_stride = {
  .header = { .start_code = 1053187, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_DQ_PRBS_TYPE_stride = {
  .header = { .start_code = 16779048, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 2, .stride = 2097152 },
  .strides[1] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_SDL_DQS_CAP_EN_stride = {
  .header = { .start_code = 2900510, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = -786431 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDEN_PTRNBUF_RPT_CNT_stride = {
  .header = { .start_code = 117441640, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_LB_DMI_F_stride = {
  .header = { .start_code = 1718332, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_INTR_NEED_TO_RETRAIN_ENABLE_stride = {
  .header = { .start_code = 12584880, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_ANA_DQ_FINE_CROSS_SEL_stride = {
  .header = { .start_code = 149014, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_OVR_DQODT_stride = {
  .header = { .start_code = 25166240, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_RX_TXPBD_CTRL_DQS_stride = {
  .header = { .start_code = 3162628, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_READ_EN_EARLY_PIPE_STRETCH_stride = {
  .header = { .start_code = 50332000, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_RDEN_PTRNBUF_STOP_PTR_stride = {
  .header = { .start_code = 125830240, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_PBD_DQ_CAP_EN_stride = {
  .header = { .start_code = 2769432, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTYB_P_CKT_stride = {
  .header = { .start_code = 1053193, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_ANA_PBD_DQS_BANK_EN_stride = {
  .header = { .start_code = 541210, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_SHDL_BANK_EN_DQS_stride = {
  .header = { .start_code = 3417125, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_DQ_PRBSGEN_INJECT_ERROR_stride = {
  .header = { .start_code = 1864, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_PLL_CP_BIAS_RES_CTRL_stride = {
  .header = { .start_code = 3207685, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_ANA_RX_RXPBD_BANK_EN_F_DQS_stride = {
  .header = { .start_code = 148489, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CKHV_PTRNBUF_RESET_stride = {
  .header = { .start_code = 18876662, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_DQ_stride = {
  .header = { .start_code = 2773512, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_SDL_DQ_CAP_EN_stride = {
  .header = { .start_code = 2900508, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = -786431 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_CROSS_RESETN_DQSC_stride = {
  .header = { .start_code = 280083, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_LB_DMI_R_stride = {
  .header = { .start_code = 1718334, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DIV_SEL_DQS_stride = {
  .header = { .start_code = 142372, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_LB_R_stride = {
  .header = { .start_code = 1726466, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_CLR_RETRAIN_stride = {
  .header = { .start_code = 8391076, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_ZCODE_PUW_DQSC_stride = {
  .header = { .start_code = 5262352, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RETRAIN_RST_N_stride = {
  .header = { .start_code = 1051004, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_RXSDL_CTRL_R_DQS_stride = {
  .header = { .start_code = 1065990, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTY_N_DQSC_stride = {
  .header = { .start_code = 1327637, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RESULT_PRBS_DQ_stride = {
  .header = { .start_code = 285214552, .num_intervals_0 = 4, .num_intervals_1 = 1 },
  .strides[0] = { .index = 7, .stride = 2097152 },
  .strides[1] = { .index = 8, .stride = -14680062 },
  .strides[2] = { .index = 15, .stride = 2097152 },
  .strides[3] = { .index = 16, .stride = -14680062 },
  .strides[4] = { .index = 3, .stride = 6 }
};

static const mn_intervals_t M_CKHV_PTRNBUF_DELAY_stride = {
  .header = { .start_code = 67111150, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DQ_RISE_RX_PBD_CAP_EN_DMI_R_stride = {
  .header = { .start_code = 2765887, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_PBD_DQ_CTRL_stride = {
  .header = { .start_code = 3162648, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_SDL_HV_CAP_EN_stride = {
  .header = { .start_code = 2888212, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = -786431 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_CKT_stride = {
  .header = { .start_code = 136711, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_HV_PIPE_DLY_stride = {
  .header = { .start_code = 50333634, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 2 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_CS_stride = {
  .header = { .start_code = 1567, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_LB_F_stride = {
  .header = { .start_code = 1726464, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_CA_stride = {
  .header = { .start_code = 140803, .num_intervals_0 = 1, .num_intervals_1 = 3 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 5, .stride = 6 },
  .strides[2] = { .index = 6, .stride = -8218 },
  .strides[3] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_MAIN_F_stride = {
  .header = { .start_code = 7362560, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_CKC_stride = {
  .header = { .start_code = 136717, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_DQ_FALL_RX_PBD_BANK_EN_F_stride = {
  .header = { .start_code = 545793, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_HIZ_DQST_stride = {
  .header = { .start_code = 871434, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_CKE_stride = {
  .header = { .start_code = 136705, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_RDQ_PTRNBUF_CMPR_START_PTR_stride = {
  .header = { .start_code = 117441912, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_WRITE_EN_EARLY_PIPE_DLY_stride = {
  .header = { .start_code = 50331712, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_RDFIFO_WRITE_POINTER_EVEN_stride = {
  .header = { .start_code = 318767560, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_CH_PRBS_SEED_stride = {
  .header = { .start_code = 234883326, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 2, .stride = 2 }
};

static const mn_intervals_t M_ANA_PBD_DQS_DUTYB_CTRLP_stride = {
  .header = { .start_code = 1065499, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQS_RESETN_stride = {
  .header = { .start_code = 280087, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_OVR_RXDQEN_stride = {
  .header = { .start_code = 20971936, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_RX_RXPBD_CAP_EN_F_DQS_stride = {
  .header = { .start_code = 2769929, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ZCODE_PDW_DQST_stride = {
  .header = { .start_code = 5655563, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_PLL_ACCUM_OVRD_VAL_LO_stride = {
  .header = { .start_code = 251785232, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 2, .stride = 4 }
};

static const mn_intervals_t M_ANA_CROSS_RESETN_DQ_stride = {
  .header = { .start_code = 284167, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_ZCODE_PI_DQ_stride = {
  .header = { .start_code = 5266437, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_PBD_DQ_BANK_EN_stride = {
  .header = { .start_code = 541208, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_SEL_PUNB_DQ_stride = {
  .header = { .start_code = 809988, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_ZCODE_PDW_DQSC_stride = {
  .header = { .start_code = 5655569, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_WDQS_PIPE_OE_DLY_stride = {
  .header = { .start_code = 50331696, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_RX_RXPBD_CAP_EN_R_DQS_stride = {
  .header = { .start_code = 2376713, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_CROSS_RESETN_DQS_stride = {
  .header = { .start_code = 280065, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDQ_PTRNBUF_CMPR_STOP_PTR_stride = {
  .header = { .start_code = 75498872, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_RXDQSEN_PIPE_STRETCH_stride = {
  .header = { .start_code = 50331952, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_WDQ_PTRNBUF_RPT_CNT_stride = {
  .header = { .start_code = 117440984, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_PLL_OUT_DIV_MODE_stride = {
  .header = { .start_code = 2945538, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 1 }
};

static const mn_intervals_t M_ANA_DQ_RESETN_stride = {
  .header = { .start_code = 280086, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_PBD_DQ_DUTY_CTRLN_stride = {
  .header = { .start_code = 1327641, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CKHV_PTRNBUF_CKE_stride = {
  .header = { .start_code = 16779510, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_CKE_stride = {
  .header = { .start_code = 3150338, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_CROSS_SEL_stride = {
  .header = { .start_code = 384, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_ZCODE_PI_DQST_stride = {
  .header = { .start_code = 5262347, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_PBD_CTRL_DQS_stride = {
  .header = { .start_code = 3154983, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_OVR_RDEN_EARLY_stride = {
  .header = { .start_code = 18874776, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_CKC_stride = {
  .header = { .start_code = 3150350, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_ANA_SEL_PUNB_CA_stride = {
  .header = { .start_code = 797696, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_WDQ_PIPE_OE_DLY_stride = {
  .header = { .start_code = 50331680, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_WDQ_PIPE_DLY_stride = {
  .header = { .start_code = 50331648, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_CKT_stride = {
  .header = { .start_code = 3150344, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_ANA_DQ_FALL_RX_PBD_CAP_EN_F_stride = {
  .header = { .start_code = 2774017, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_DQRD_DATA_PTRN_EN_stride = {
  .header = { .start_code = 10487734, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_ANA_ZCODE_X_DQ_stride = {
  .header = { .start_code = 5659652, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_CROSS_RESETN_CA_stride = {
  .header = { .start_code = 271875, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_WDQ_PTRNBUF_WR_EN_stride = {
  .header = { .start_code = 992, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 32 }
};

static const mn_intervals_t M_ANA_DUTY_N_CA_stride = {
  .header = { .start_code = 1319429, .num_intervals_0 = 1, .num_intervals_1 = 3 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 5, .stride = 6 },
  .strides[2] = { .index = 6, .stride = -8218 },
  .strides[3] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_DUTY_N_DQS_stride = {
  .header = { .start_code = 1327621, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_RX_LPBK_SEL_CA_stride = {
  .header = { .start_code = 797697, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_WDQ_PTRNBUF_STOP_PTR_stride = {
  .header = { .start_code = 125829584, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_CA_stride = {
  .header = { .start_code = 9731, .num_intervals_0 = 1, .num_intervals_1 = 3 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 5, .stride = 6 },
  .strides[2] = { .index = 6, .stride = -8218 },
  .strides[3] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_CK_PIPE_DLY_stride = {
  .header = { .start_code = 50333646, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 2 }
};

static const mn_intervals_t M_WDQ_PTRNBUF_DELAY_stride = {
  .header = { .start_code = 67109344, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 32 }
};

static const mn_intervals_t M_ANA_RX_LPBK_SEL_DMI_stride = {
  .header = { .start_code = 932928, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RXDQEN_PIPE_STRETCH_stride = {
  .header = { .start_code = 50331936, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_PLL_CP_CMP_RES_CTRL_stride = {
  .header = { .start_code = 3731973, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_OVR_TXDQSOE_stride = {
  .header = { .start_code = 18874784, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_RDFIFO_READ_POINTER_stride = {
  .header = { .start_code = 327156168, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_ZCODE_PUW_DQ_stride = {
  .header = { .start_code = 5266436, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_INTR_NEED_TO_RETRAIN_stride = {
  .header = { .start_code = 549455790, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_ANA_SEL_PUNB_DQSC_stride = {
  .header = { .start_code = 805904, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_CROSS_RESETN_DMI_stride = {
  .header = { .start_code = 276035, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RXDQEN_PIPE_DLY_stride = {
  .header = { .start_code = 50331744, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_RDQODTEN_PIPE_DLY_stride = {
  .header = { .start_code = 50331776, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_RDFIFO_RESET_N_stride = {
  .header = { .start_code = 400, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_DMI_stride = {
  .header = { .start_code = 537156, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDQ_PTRNBUF_CMP_PF_stride = {
  .header = { .start_code = 281018824, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_RETRAIN_FREEZE_stride = {
  .header = { .start_code = 2428, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DIV_RST_DQS_stride = {
  .header = { .start_code = 273444, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_ANA_DQ_RISE_RX_PBD_CAP_EN_R_stride = {
  .header = { .start_code = 2774019, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_CC_PIPE_DLY_CS_stride = {
  .header = { .start_code = 50333638, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 2 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_DQS_stride = {
  .header = { .start_code = 148993, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDQ_PTRNBUF_CMPR_PF_stride = {
  .header = { .start_code = 268437248, .num_intervals_0 = 2, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 1048576 },
  .strides[1] = { .index = 16, .stride = -15728638 },
  .strides[2] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_WDQ_PIPE_OE_STRETCH_stride = {
  .header = { .start_code = 50331872, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_CKT_stride = {
  .header = { .start_code = 5639, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_ZCODE_PDW_DQ_stride = {
  .header = { .start_code = 5659653, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_RDQODTEN_PIPE_STRETCH_stride = {
  .header = { .start_code = 50331968, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_CC_PIPE_DLY_CA_stride = {
  .header = { .start_code = 50333630, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 2 }
};

static const mn_intervals_t M_OVR_TXDQOE_stride = {
  .header = { .start_code = 16777632, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_CKC_stride = {
  .header = { .start_code = 5645, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_SDL_CK_CTRL_stride = {
  .header = { .start_code = 1053202, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_RDQSEN_PIPE_DLY_stride = {
  .header = { .start_code = 50331728, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_OVR_WREN_EARLY_stride = {
  .header = { .start_code = 16777624, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_ZCODE_PDR_CA_stride = {
  .header = { .start_code = 5254146, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_DQ_RISE_RX_PBD_CTRL_R_stride = {
  .header = { .start_code = 3167235, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_CKE_stride = {
  .header = { .start_code = 5633, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_SDL_HV_BANK_EN_stride = {
  .header = { .start_code = 3412500, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_DQS_stride = {
  .header = { .start_code = 17921, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_OVR_DQSODT_stride = {
  .header = { .start_code = 27263392, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DQ_FALL_RX_PBD_CAP_EN_DMI_F_stride = {
  .header = { .start_code = 2765885, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_ENB_R_stride = {
  .header = { .start_code = 808962, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_CH_PRBS_TYPE_stride = {
  .header = { .start_code = 16779526, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 2, .stride = 2097152 }
};

static const mn_intervals_t M_ANA_DUTY_N_CS_stride = {
  .header = { .start_code = 1311265, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_CC_PTRNBUF_CS_stride = {
  .header = { .start_code = 16779434, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 31, .stride = 2 }
};

static const mn_intervals_t M_ANA_SDL_DQS_BANK_EN_stride = {
  .header = { .start_code = 3424798, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TXSDL_CTRL_DQS_stride = {
  .header = { .start_code = 1065474, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_CKE_stride = {
  .header = { .start_code = 2757122, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 196608 }
};

static const mn_intervals_t M_ANA_PBD_BANK_EN_DQS_stride = {
  .header = { .start_code = 533543, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_ANA_SEL_PUNB_DQST_stride = {
  .header = { .start_code = 805898, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_RISE_RX_PBD_BANK_EN_DMI_R_stride = {
  .header = { .start_code = 537663, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTYB_P_DQSC_stride = {
  .header = { .start_code = 1065493, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_ENB_F_stride = {
  .header = { .start_code = 808960, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_RX_LPBK_SEL_DQ_stride = {
  .header = { .start_code = 941060, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_WDQ_PTRNBUF_START_PTR_stride = {
  .header = { .start_code = 117440976, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DUTYB_P_DMI_stride = {
  .header = { .start_code = 1061445, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_PBD_CTRL_CS_stride = {
  .header = { .start_code = 3146272, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 262144 }
};

static const mn_intervals_t M_ANA_DUTY_N_DQ_stride = {
  .header = { .start_code = 1331721, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_RSTN_stride = {
  .header = { .start_code = 1537, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_TX_PBD_CAP_EN_CKT_stride = {
  .header = { .start_code = 2757128, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 196608 }
};

static const mn_intervals_t M_ANA_SDL_CA_CAP_EN_stride = {
  .header = { .start_code = 2888208, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = -786431 }
};

static const mn_intervals_t M_ANA_DQ_FE_EN_DMI_R_stride = {
  .header = { .start_code = 866366, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_OVR_RXDQSEN_stride = {
  .header = { .start_code = 23069088, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_RDQSODTEN_PIPE_STRETCH_stride = {
  .header = { .start_code = 50331984, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_DQ_RISE_RX_PBD_BANK_EN_R_stride = {
  .header = { .start_code = 545795, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_SDL_DQS_CTRL_stride = {
  .header = { .start_code = 1065502, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FALL_RX_PBD_CTRL_F_stride = {
  .header = { .start_code = 3167233, .num_intervals_0 = 1, .num_intervals_1 = 23 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 6, .stride = 10 },
  .strides[2] = { .index = 7, .stride = -4124 },
  .strides[3] = { .index = 9, .stride = 10 },
  .strides[4] = { .index = 10, .stride = -4148 },
  .strides[5] = { .index = 15, .stride = 10 },
  .strides[6] = { .index = 16, .stride = 20430 },
  .strides[7] = { .index = 22, .stride = 10 },
  .strides[8] = { .index = 23, .stride = -4124 },
  .strides[9] = { .index = 25, .stride = 10 },
  .strides[10] = { .index = 26, .stride = -4148 },
  .strides[11] = { .index = 31, .stride = 10 },
  .strides[12] = { .index = 32, .stride = 20430 },
  .strides[13] = { .index = 38, .stride = 10 },
  .strides[14] = { .index = 39, .stride = -4124 },
  .strides[15] = { .index = 41, .stride = 10 },
  .strides[16] = { .index = 42, .stride = -4148 },
  .strides[17] = { .index = 47, .stride = 10 },
  .strides[18] = { .index = 48, .stride = 20430 },
  .strides[19] = { .index = 54, .stride = 10 },
  .strides[20] = { .index = 55, .stride = -4124 },
  .strides[21] = { .index = 57, .stride = 10 },
  .strides[22] = { .index = 58, .stride = -4148 },
  .strides[23] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_WDQS_PIPE_DLY_stride = {
  .header = { .start_code = 50331664, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_HB_R_stride = {
  .header = { .start_code = 1595394, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_RDFIFO_WRITE_POINTER_ODD_stride = {
  .header = { .start_code = 322961864, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_DUTYB_P_CS_stride = {
  .header = { .start_code = 1049121, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_CA_DFI_MAPPING_stride = {
  .header = { .start_code = 50333662, .num_intervals_0 = 5, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 4194304 },
  .strides[1] = { .index = 4, .stride = -12582910 },
  .strides[2] = { .index = 7, .stride = 4194304 },
  .strides[3] = { .index = 8, .stride = -12582910 },
  .strides[4] = { .index = 9, .stride = 4194304 }
};

static const mn_intervals_t M_ANA_TXSDL_CAP_EN_DQS_stride = {
  .header = { .start_code = 2900482, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = -786431 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQS_FINE_CROSS_SEL_stride = {
  .header = { .start_code = 149015, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_EN_DMI_F_stride = {
  .header = { .start_code = 866364, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_WDQS_PIPE_OE_STRETCH_stride = {
  .header = { .start_code = 50331888, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_KICK_HB_F_stride = {
  .header = { .start_code = 1595392, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_SDL_DQ_CTRL_stride = {
  .header = { .start_code = 1065500, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CC_PRBSGEN_ID_CA_stride = {
  .header = { .start_code = 16779528, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 7, .stride = 2097152 },
  .strides[1] = { .index = 8, .stride = -14680062 },
  .strides[2] = { .index = 9, .stride = 2097152 }
};

static const mn_intervals_t M_ANA_RX_RXPBD_BANK_EN_R_DQS_stride = {
  .header = { .start_code = 17417, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_MAIN_R_stride = {
  .header = { .start_code = 7362562, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_PBD_DQS_DUTY_CTRLN_stride = {
  .header = { .start_code = 1327643, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ZCODE_PDR_DMI_stride = {
  .header = { .start_code = 5258306, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CC_RANK_SEL_PIPE_DLY_stride = {
  .header = { .start_code = 50333642, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 2 }
};

static const mn_intervals_t M_RXDQSEN_PIPE_DLY_stride = {
  .header = { .start_code = 50331760, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_DQ_FALL_RX_PBD_BANK_EN_DMI_F_stride = {
  .header = { .start_code = 537661, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_DQ_PRBS_CHECK_EN_stride = {
  .header = { .start_code = 4196284, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_ANA_PLL_OUT_DIV_LCOUNT_stride = {
  .header = { .start_code = 5304835, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 393216 }
};

static const mn_intervals_t M_ANA_EDGE_RESETB_DQS_stride = {
  .header = { .start_code = 281600, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_DQSC_stride = {
  .header = { .start_code = 149011, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_MAIN_DMI_F_stride = {
  .header = { .start_code = 7354428, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_SHDL_CTRL_DQS_stride = {
  .header = { .start_code = 1057829, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_ANA_TX_T_TX_PBD_CAP_EN_DQS_stride = {
  .header = { .start_code = 2769422, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_PLL_FB_DIV_LCOUNT_stride = {
  .header = { .start_code = 5304833, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 393216 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_CS_stride = {
  .header = { .start_code = 132639, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_SDL_CK_CAP_EN_stride = {
  .header = { .start_code = 2888210, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = -786431 }
};

static const mn_intervals_t M_ANA_ZCODE_X_DMI_stride = {
  .header = { .start_code = 5651520, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_MAX_OSC_CNT_stride = {
  .header = { .start_code = 251660700, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_TX_C_TX_PBD_BANK_EN_DQS_stride = {
  .header = { .start_code = 541204, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FE_DAC_MAIN_DMI_R_stride = {
  .header = { .start_code = 7354430, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_ZCODE_PUW_DMI_stride = {
  .header = { .start_code = 5258304, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_TRN_WRITE_EN_AS_DQS_stride = {
  .header = { .start_code = 4194712, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_ZCODE_PDR_DQSC_stride = {
  .header = { .start_code = 5262354, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_PLL_FB_DIV_HCOUNT_stride = {
  .header = { .start_code = 5304832, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 393216 }
};

static const mn_intervals_t M_ANA_RXSDL_CAP_EN_DQS_stride = {
  .header = { .start_code = 2638855, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_DQ_PRBS_SEED_stride = {
  .header = { .start_code = 234882832, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 2, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 6 }
};

static const mn_intervals_t M_ANA_ZCODE_X_DQSC_stride = {
  .header = { .start_code = 5655568, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_CROSS_SEL_DQSC_stride = {
  .header = { .start_code = 17939, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_TX_PBD_DUTY_CTRLN_RSTN_stride = {
  .header = { .start_code = 1311235, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_CS_stride = {
  .header = { .start_code = 524832, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_SDL_CA_CTRL_stride = {
  .header = { .start_code = 1053200, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 131072 }
};

static const mn_intervals_t M_RX_LAST_DATA_stride = {
  .header = { .start_code = 268435888, .num_intervals_0 = 5, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 1048576 },
  .strides[1] = { .index = 16, .stride = -15728638 },
  .strides[2] = { .index = 31, .stride = 1048576 },
  .strides[3] = { .index = 32, .stride = -15728638 },
  .strides[4] = { .index = 33, .stride = 1048576 },
  .strides[5] = { .index = 3, .stride = 6 }
};

static const mn_intervals_t M_ANA_ZCODE_X_DQST_stride = {
  .header = { .start_code = 5655562, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_WDQS_PIPE_STRETCH_stride = {
  .header = { .start_code = 50331856, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_PBD_DQ_DUTYB_CTRLP_stride = {
  .header = { .start_code = 1065497, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DRVEN_CA_stride = {
  .header = { .start_code = 994304, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_W_DQ_CS_PIPE_DLY_stride = {
  .header = { .start_code = 54526144, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_ZCODE_PDW_CA_stride = {
  .header = { .start_code = 5647361, .num_intervals_0 = 3, .num_intervals_1 = 0 },
  .strides[0] = { .index = 5, .stride = 6 },
  .strides[1] = { .index = 6, .stride = -8218 },
  .strides[2] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_OSC_CNT_stride = {
  .header = { .start_code = 520096140, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 2 }
};

static const mn_intervals_t M_ANA_PBD_CAP_EN_DQS_stride = {
  .header = { .start_code = 2761767, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_RSTN_stride = {
  .header = { .start_code = 524802, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_RDQSEN_PIPE_STRETCH_stride = {
  .header = { .start_code = 50331920, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_W_DQS_CS_PIPE_DLY_stride = {
  .header = { .start_code = 50331840, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_RDPIPE_CONTROL_stride = {
  .header = { .start_code = 50332016, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_HIZ_DMI_stride = {
  .header = { .start_code = 867392, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_DQ_PRBS_RESULT_RESET_stride = {
  .header = { .start_code = 8390588, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 1048576 }
};

static const mn_intervals_t M_RXCS_PIPE_DLY_stride = {
  .header = { .start_code = 50331824, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 4 }
};

static const mn_intervals_t M_ANA_DQ_FE_EN_F_stride = {
  .header = { .start_code = 874496, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_TX_PBD_BANK_EN_CA_stride = {
  .header = { .start_code = 532996, .num_intervals_0 = 1, .num_intervals_1 = 3 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 5, .stride = 6 },
  .strides[2] = { .index = 6, .stride = -8218 },
  .strides[3] = { .index = 9, .stride = 6 }
};

static const mn_intervals_t M_ANA_DQ_FE_EN_R_stride = {
  .header = { .start_code = 874498, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_OSC_EN_DQS_stride = {
  .header = { .start_code = 11300, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 1, .stride = 4 }
};

static const mn_intervals_t M_ANA_ZCODE_PI_DQSC_stride = {
  .header = { .start_code = 5262353, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_CC_PTRNBUF_DELAY_stride = {
  .header = { .start_code = 67110890, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 31, .stride = 2 }
};

static const mn_intervals_t M_ANA_ZCODE_PDR_DQ_stride = {
  .header = { .start_code = 5266438, .num_intervals_0 = 23, .num_intervals_1 = 0 },
  .strides[0] = { .index = 6, .stride = 10 },
  .strides[1] = { .index = 7, .stride = -4124 },
  .strides[2] = { .index = 9, .stride = 10 },
  .strides[3] = { .index = 10, .stride = -4148 },
  .strides[4] = { .index = 15, .stride = 10 },
  .strides[5] = { .index = 16, .stride = 20430 },
  .strides[6] = { .index = 22, .stride = 10 },
  .strides[7] = { .index = 23, .stride = -4124 },
  .strides[8] = { .index = 25, .stride = 10 },
  .strides[9] = { .index = 26, .stride = -4148 },
  .strides[10] = { .index = 31, .stride = 10 },
  .strides[11] = { .index = 32, .stride = 20430 },
  .strides[12] = { .index = 38, .stride = 10 },
  .strides[13] = { .index = 39, .stride = -4124 },
  .strides[14] = { .index = 41, .stride = 10 },
  .strides[15] = { .index = 42, .stride = -4148 },
  .strides[16] = { .index = 47, .stride = 10 },
  .strides[17] = { .index = 48, .stride = 20430 },
  .strides[18] = { .index = 54, .stride = 10 },
  .strides[19] = { .index = 55, .stride = -4124 },
  .strides[20] = { .index = 57, .stride = 10 },
  .strides[21] = { .index = 58, .stride = -4148 },
  .strides[22] = { .index = 63, .stride = 10 }
};

static const mn_intervals_t M_ANA_DUTY_N_DQST_stride = {
  .header = { .start_code = 1327631, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_FINE_CROSS_SEL_RSTN_stride = {
  .header = { .start_code = 132609, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 65536 }
};

static const mn_intervals_t M_ANA_TX_C_TX_PBD_CAP_EN_DQS_stride = {
  .header = { .start_code = 2769428, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 196608 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_PLL_OUT_DIV_HCOUNT_stride = {
  .header = { .start_code = 5304834, .num_intervals_0 = 1, .num_intervals_1 = 0 },
  .strides[0] = { .index = 1, .stride = 393216 }
};

static const mn_intervals_t M_ANA_RXSDL_BANK_EN_R_DQS_stride = {
  .header = { .start_code = 3687430, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DQ_FALL_RX_PBD_CTRL_DMI_F_stride = {
  .header = { .start_code = 3159101, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_RDEN_PTRNBUF_RD_EN_stride = {
  .header = { .start_code = 1264, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 15, .stride = 2 },
  .strides[1] = { .index = 3, .stride = 32 }
};

static const mn_intervals_t M_ANA_DQS_CROSS_SEL_stride = {
  .header = { .start_code = 17943, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 65536 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_PBD_DQS_CTRL_stride = {
  .header = { .start_code = 3162650, .num_intervals_0 = 1, .num_intervals_1 = 1 },
  .strides[0] = { .index = 1, .stride = 262144 },
  .strides[1] = { .index = 3, .stride = 12288 }
};

static const mn_intervals_t M_ANA_DUTYB_P_CA_stride = {
  .header = { .start_code = 1057285, .num_intervals_0 = 1, .num_intervals_1 = 3 },
  .strides[0] = { .index = 1, .stride = 131072 },
  .strides[1] = { .index = 5, .stride = 6 },
  .strides[2] = { .index = 6, .stride = -8218 },
  .strides[3] = { .index = 9, .stride = 6 }
};

extern const uint32_t M_WDQ_PTRNBUF_DQ_MIN[17];
extern const uint32_t M_RDQ_PTRNBUF_DQ_MIN[17];
 extern const uint32_t M_CC_PTRNBUF_CA_MIN[10];
uint32_t get_mn_code(const mn_intervals_t *mn, uint8_t index0, uint8_t index1) {
  uint8_t num_intervals_0 = mn->header.num_intervals_0;
  uint8_t num_intervals_1 = mn->header.num_intervals_1;
  uint32_t mn_code = mn->header.start_code;

  // single_interval_t *intervals_0[num_intervals_0];
  const single_interval_t *intervals_0 = &(mn->strides[0]);
  // if (num_intervals_1 > 0) {
  //   // single_interval_t *intervals_1[num_intervals_1] = &(mn->strides[num_intervals_0]);
  //   const single_interval_t *intervals_1 = &(mn->strides[num_intervals_0]);
  // }

  for (uint8_t i = 0; i < index0; i++) {
    for (uint8_t j = 0; j < num_intervals_0; j++) {
      if (i < intervals_0[j].index) {
        mn_code += intervals_0[j].stride;
        break;
      }
    }
  }

  if (num_intervals_1 > 0) {
    const single_interval_t *intervals_1 = &(mn->strides[num_intervals_0]);
    for (uint8_t i = 0; i < index1; i++) {
      for (uint8_t j = 0; j < num_intervals_1; j++) {
        if (i < intervals_1[j].index) {
          mn_code += intervals_1[j].stride;
          break;
        }
      }
    }
  }

  return mn_code;

}

uint32_t get_wdq_ptrnbuf_dq_code(uint8_t byte_idx, uint8_t row_idx, uint8_t dq_idx) {
    return M_WDQ_PTRNBUF_DQ_MIN[dq_idx] + 6 * row_idx + 96 * byte_idx; 
}

uint32_t get_rdq_ptrnbuf_dq_code(uint8_t byte_idx, uint8_t row_idx, uint8_t dq_idx) {
    return M_RDQ_PTRNBUF_DQ_MIN[dq_idx] + 6 * row_idx + 96 * byte_idx; 
}

uint32_t get_cc_ptrnbuf_ca_code(uint8_t row_idx, uint8_t ca_idx) {
    return M_CC_PTRNBUF_CA_MIN[ca_idx] + 4 * row_idx; 
}
