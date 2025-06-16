#ifndef SPI_H
#define SPI_H

#include <common/sflash.h>
#include <stddef.h>
#include <stdint.h>
#include <common/common.h>

#define SF_SRAM_ADDRESS     0x26001600
#define SF_CSR_BASE_ADDR	0x26001000
#define L1C_CSR_BASE_ADDR	0x26002000


#define SF_CTRL_0		    0x00
#define SF_CTRL_1		    0x04
#define SF_IF_SAHB_0		0x08
#define SF_IF_SAHB_1		0x0C
#define SF_IF_SAHB_2		0x10
#define SF_IF_IAHB_0		0x14
#define SF_IF_IAHB_1		0x18
#define SF_IF_IAHB_2		0x1C
#define SF_IF_STATUS_0		0x20
#define SF_IF_STATUS_1		0x24
#define SF_AHB2SIF_STATUS	0x2C
#define SF_IF_IO_DLY_0		0x30
#define SF_IF_IO_DLY_1		0x34
#define SF_IF_IO_DLY_2		0x38
#define SF_IF_IO_DLY_3		0x3C
#define SF_IF_IO_DLY_4		0x40
#define SF_RESERVED         0x44
#define SF_CTRL_4		    0x74

#define SF_SRAM_BASE_ADDR	0x600

typedef enum {
	SINGLE_READ      			= 0x03,
	SINGLE_FAST_READ 			= 0x0B,
	DUAL_OUTPUT_FAST_READ   	= 0x3B,
	DUAL_INPUT_OUTPUT_FAST_READ = 0xBB,
	QUAD_OUTPUT_FAST_READ   	= 0x6B,
	QUAD_INPUT_OUTPUT_FAST_READ = 0xEB
} e_spi_commands;


typedef union {
	struct {
		uint32_t rsvd0:2;
		uint32_t sf_clk_sf_rx_inv_sel:1;
		uint32_t sf_clk_out_gate_en:1;
		uint32_t sf_clk_out_inv_sel:1;
		uint32_t rsvd1:3;
		uint32_t sf_if_read_dly_n:3;
		uint32_t sf_if_read_dly_en:1;
		uint32_t rsvd2:4;
		uint32_t sf_if_int:1;
		uint32_t sf_if_int_clr:1;
		uint32_t sf_if_int_set:1;
		uint32_t sf_if_32b_adr_en:1;
		uint32_t sf_aes_dout_endian:1;
		uint32_t sf_aes_din_endian:1;
		uint32_t sf_aes_key_endian:1;
		uint32_t sf_aes_iv_endian:1;
		uint32_t sf_id:8;
	};
	uint32_t val;
} Sf_ctrl_0;

typedef union {
	struct {
		uint32_t sf_if_sr_pat_mask:8;
		uint32_t sf_if_sr_pat:8;
		uint32_t sf_if_sr_int:1;
		uint32_t sf_if_sr_int_en:1;
		uint32_t sf_if_sr_int_set:1;
		uint32_t rsvd0:1;
		uint32_t sf_if_0_ack_lat:3;
		uint32_t sf_ahb2sif_diswrap:1;
		uint32_t sf_if_reg_hold:1;
		uint32_t sf_if_reg_wp:1;
		uint32_t sf_ahb2sif_stopped:1;
		uint32_t sf_ahb2sif_stop:1;
		uint32_t sf_if_fn_sel:1;
		uint32_t sf_if_en:1;
		uint32_t sf_ahb2sif_en:1;
		uint32_t sf_ahb2sram_en:1;
	};
	uint32_t val;
} Sf_ctrl_1;

typedef union {
	struct {
		uint32_t sf_if_busy:1;
		uint32_t sf_if_0_trig:1;
		uint32_t sf_if_0_dat_byte:10;
		uint32_t sf_if_0_dmy_byte:5;
		uint32_t sf_if_0_adr_byte:3;
		uint32_t sf_if_0_cmd_byte:3;
		uint32_t sf_if_0_dat_rw:1;
		uint32_t sf_if_0_dat_en:1;
		uint32_t sf_if_0_dmy_en:1;
		uint32_t sf_if_0_adr_en:1;
		uint32_t sf_if_0_cmd_en:1;
		uint32_t sf_if_0_spi_mode:3;
		uint32_t sf_if_0_qpi_mode_en:1;
	};
	uint32_t val;
} Sf_if_sahb_0 ;

typedef union {
	struct {
		uint32_t sf_if_0_cmd_buf_0:32;
	};
	uint32_t val;
} Sf_if_sahb_1;

typedef union {
	struct {
		uint32_t sf_if_0_cmd_buf_1:32;
	};
	uint32_t val;
} Sf_if_sahb_2;

typedef union {
	struct {
		uint32_t rsvd0:12;
		uint32_t sf_if_1_dmy_byte:5;
		uint32_t sf_if_1_adr_byte:3;
		uint32_t sf_if_1_cmd_byte:3;
		uint32_t sf_if_1_dat_rw:1;
		uint32_t sf_if_1_dat_en:1;
		uint32_t sf_if_1_dmy_en:1;
		uint32_t sf_if_1_adr_en:1;
		uint32_t sf_if_1_cmd_en:1;
		uint32_t sf_if_1_spi_mode:3;
		uint32_t sf_if_1_qpi_mode_en:1;
	};
	uint32_t val;
} Sf_if_iahb_0;

typedef union {
	struct {
		uint32_t sf_if_1_cmd_buf_0:32;
	};
	uint32_t val;
} Sf_if_iahb_1;

typedef union {
	struct {
		uint32_t sf_if_1_cmd_buf_1:32;
	};
	uint32_t val;
} Sf_if_iahb_2;

typedef union {
	struct {
		uint32_t sf_if_status_0:32;
	};
	uint32_t val;
} Sf_if_status_0;

typedef union {
	struct {
		uint32_t sf_if_status_1:32;
	};
	uint32_t val;
} Sf_if_status_1;

typedef union {
	struct {
		uint32_t sf_ahb2sif_status:32;
	};
	uint32_t val;
} Sf_ahb2sif_status;

typedef union {
	struct {
		uint32_t sf_cs_dly_sel:2;
		uint32_t sf_cs2_dly_sel:2;
		uint32_t rsvd0:4;
		uint32_t sf_clk_out_dly_sel:2;
		uint32_t rsvd1:16;
		uint32_t sf_dqs_oe_dly_sel:2;
		uint32_t sf_dqs_di_dly_sel:2;
		uint32_t sf_dqs_do_dly_sel:2;
	};
	uint32_t val;
} Sf_if_io_dly_0;

typedef union {
	struct {
		uint32_t sf_io_0_oe_dly_sel:2;
		uint32_t rsvd0:6;
		uint32_t sf_io_0_di_dly_sel:2;
		uint32_t rsvd1:6;
		uint32_t sf_io_0_do_dly_sel:2;
		uint32_t rsvd2:14;
	};
	uint32_t val;
} Sf_if_io_dly_1;

typedef union {
	struct {
		uint32_t sf_io_1_oe_dly_sel:2;
		uint32_t rsvd0:6;
		uint32_t sf_io_1_di_dly_sel:2;
		uint32_t rsvd1:6;
		uint32_t sf_io_1_do_dly_sel:2;
		uint32_t rsvd2:14;
	};
	uint32_t val;
} Sf_if_io_dly_2;

typedef union {
	struct {
		uint32_t sf_io_2_oe_dly_sel:2;
		uint32_t rsvd0:6;
		uint32_t sf_io_2_di_dly_sel:2;
		uint32_t rsvd1:6;
		uint32_t sf_io_2_do_dly_sel:2;
		uint32_t rsvd2:14;
	};
	uint32_t val;
} Sf_if_io_dly_3;

typedef union {
	struct {
		uint32_t sf_io_3_oe_dly_sel:2;
		uint32_t rsvd0:6;
		uint32_t sf_io_3_di_dly_sel:2;
		uint32_t rsvd1:6;
		uint32_t sf_io_3_do_dly_sel:2;
		uint32_t rsvd2:14;
	};
	uint32_t val;
} Sf_if_io_dly_4;


typedef union {
	struct {
		uint32_t sf_reserved:32;
	};
	uint32_t val;
} Sf_reserved;

typedef union {
	struct {
		uint32_t rsvd0:13;
		uint32_t sf_cmds_1_wrap_len:4;
		uint32_t sf_cmds_1_en:1;
		uint32_t sf_cmds_1_wrap_mode:2;
		uint32_t sf_cmds_core_en:1;
		uint32_t rsvd1:8;
		uint32_t sf_if_1_ack_lat:3;
	};
	uint32_t val;
} Sf_ctrl_3;

int32_t spi_copy_data(uint8_t *s_addr, uint8_t *d_addr, uint32_t len);
int32_t qspi_mode_init(void);
int32_t qspi_copy_data(uint8_t *s_addr, uint8_t *d_addr, uint32_t len);

typedef int32_t (*CopyFunc)(void *, uint32_t, uint32_t, uint32_t);
int32_t qspi_data_transfer_handler(void *pInfo, CopyFunc pFunc,
                                uint32_t s_addr, uint32_t d_addr,
                                uint32_t len);

#endif
