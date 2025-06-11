/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__BL_SFLASH0_H
#define METAL__DRIVERS__BL_SFLASH0_H

#include <stdlib.h>
#include <string.h>

#include <metal/compiler.h>
#include <metal/io.h>

#include <metal/clock.h>
#include <metal/interrupt.h>
#include <metal/sflash.h>

#define SF_CTRL_BUF_OFFSET      0x600
#define SF_SRAM_BUF_OFFSET      0x600
#define L1C_OFFSET              0x1000

#define FLASH_CTRL_BUF_SIZE     256

#define FLASH_XIP_BASE          0x30100000
#define FLASH_XIP_END           0x31100000
#define FLASH_CFG_MAGIC         "FCFG"

#define SFCTRL_BUSY_STATE_TIMEOUT (5 * 160 * 1000)

typedef enum {
    SUCCESS = 0,
    ERROR = 1,
    TIMEOUT = 2,
    INVALID = 3, /* invalid arguments */
    NORESC = 4   /* no resource or resource temperary unavailable */
} BL_Err_Type;

typedef enum {
    SF_CTRL_PAD_SEL_SF1,               /*!< SF Ctrl pad select sf1, flash use GPIO 17-22, no psram */
    SF_CTRL_PAD_SEL_SF2,               /*!< SF Ctrl pad select sf2, flash use GPIO 23-28, no psram, embedded flash */
    SF_CTRL_PAD_SEL_SF3,               /*!< SF Ctrl pad select sf3, flash use GPIO 32-37, no psram */
    SF_CTRL_PAD_SEL_DUAL_BANK_SF1_SF2, /*!< SF Ctrl pad select sf1 and sf2, flash use GPIO 17-22, psram use GPIO 23-28 */
    SF_CTRL_PAD_SEL_DUAL_BANK_SF2_SF3, /*!< SF Ctrl pad select sf2 and sf3, flash use GPIO 23-28, psram use GPIO 32-37 */
    SF_CTRL_PAD_SEL_DUAL_BANK_SF3_SF1, /*!< SF Ctrl pad select sf3 and sf1, flash use GPIO 32-37, psram use GPIO 17-22 */
    SF_CTRL_PAD_SEL_DUAL_CS_SF2,       /*!< SF Ctrl pad select sf2, flash/psram use GPIO 23-28, psram use GPIO 17 as CS2 */
    SF_CTRL_PAD_SEL_DUAL_CS_SF3,       /*!< SF Ctrl pad select sf3, flash/psram use GPIO 32-37, psram use GPIO 23 as CS2 */
} SF_Ctrl_Pad_Select;

/**
 *  @brief Serial flash system bus control type definition
 */
typedef enum {
    SF_CTRL_SEL_FLASH, /*!< SF Ctrl system bus control flash */
    SF_CTRL_SEL_PSRAM, /*!< SF Ctrl system bus control psram */
} SF_Ctrl_Select;

/**
 *  @brief Serail flash controller wrap mode len type definition
 */
typedef enum {
    SF_CTRL_WRAP_LEN_8,    /*!< SF Ctrl wrap length: 8 */
    SF_CTRL_WRAP_LEN_16,   /*!< SF Ctrl wrap length: 16 */
    SF_CTRL_WRAP_LEN_32,   /*!< SF Ctrl wrap length: 32 */
    SF_CTRL_WRAP_LEN_64,   /*!< SF Ctrl wrap length: 64 */
    SF_CTRL_WRAP_LEN_128,  /*!< SF Ctrl wrap length: 128 */
    SF_CTRL_WRAP_LEN_256,  /*!< SF Ctrl wrap length: 256 */
    SF_CTRL_WRAP_LEN_512,  /*!< SF Ctrl wrap length: 512 */
    SF_CTRL_WRAP_LEN_1024, /*!< SF Ctrl wrap length: 1024 */
    SF_CTRL_WRAP_LEN_2048, /*!< SF Ctrl wrap length: 2048 */
    SF_CTRL_WRAP_LEN_4096, /*!< SF Ctrl wrap length: 4096 */
} SF_Ctrl_Wrap_Len_Type;

/**
 *  @brief Serial flash controller owner type definition
 */
typedef enum {
    SF_CTRL_OWNER_SAHB, /*!< System AHB bus control serial flash controller */
    SF_CTRL_OWNER_IAHB, /*!< I-Code AHB bus control serial flash controller */
} SF_Ctrl_Owner_Type;

/**
 *  @brief Serial flash controller select clock type definition
 */
typedef enum {
    SF_CTRL_SAHB_CLOCK,  /*!< Serial flash controller select default sahb clock */
    SF_CTRL_FLASH_CLOCK, /*!< Serial flash controller select flash clock */
} SF_Ctrl_Sahb_Type;

/**
 *  @brief Serial flash controller owner type definition
 */
typedef enum {
    HIGH_SPEED_MODE_CLOCK,  /*!< Serial flash controller high speed mode clk_ahb>clk_sf */
    REMOVE_CLOCK_CONSTRAIN, /*!< Serial flash controller remove clock constrain */
} SF_Ctrl_Ahb2sif_Type;

/**
 *  @brief Read and write type definition
 */
typedef enum {
    SF_CTRL_READ,  /*!< Serail flash read command flag */
    SF_CTRL_WRITE, /*!< Serail flash write command flag */
} SF_Ctrl_RW_Type;

/**
 *  @brief Serail flash interface IO type definition
 */
typedef enum {
    SF_CTRL_NIO_MODE, /*!< Normal IO mode define */
    SF_CTRL_DO_MODE,  /*!< Dual Output mode define */
    SF_CTRL_QO_MODE,  /*!< Quad Output mode define */
    SF_CTRL_DIO_MODE, /*!< Dual IO mode define */
    SF_CTRL_QIO_MODE, /*!< Quad IO mode define */
} SF_Ctrl_IO_Type;

/**
 *  @brief Serail flash controller interface mode type definition
 */
typedef enum {
    SF_CTRL_SPI_MODE, /*!< SPI mode define */
    SF_CTRL_QPI_MODE, /*!< QPI mode define */
} SF_Ctrl_Mode_Type;

/**
 *  @brief Serail flash controller command mode type definition
 */
typedef enum {
    SF_CTRL_CMD_1_LINE,  /*!< Command in one line mode */
    SF_CTRL_CMD_4_LINES, /*!< Command in four lines mode */
} SF_Ctrl_Cmd_Mode_Type;

/**
 *  @brief Serail flash controller address mode type definition
 */
typedef enum {
    SF_CTRL_ADDR_1_LINE,  /*!< Address in one line mode */
    SF_CTRL_ADDR_2_LINES, /*!< Address in two lines mode */
    SF_CTRL_ADDR_4_LINES, /*!< Address in four lines mode */
} SF_Ctrl_Addr_Mode_Type;

/**
 *  @brief Serail flash controller dummy mode type definition
 */
typedef enum {
    SF_CTRL_DUMMY_1_LINE,  /*!< Dummy in one line mode */
    SF_CTRL_DUMMY_2_LINES, /*!< Dummy in two lines mode */
    SF_CTRL_DUMMY_4_LINES, /*!< Dummy in four lines mode */
} SF_Ctrl_Dmy_Mode_Type;

/**
 *  @brief Serail flash controller data mode type definition
 */
typedef enum {
    SF_CTRL_DATA_1_LINE,  /*!< Data in one line mode */
    SF_CTRL_DATA_2_LINES, /*!< Data in two lines mode */
    SF_CTRL_DATA_4_LINES, /*!< Data in four lines mode */
} SF_Ctrl_Data_Mode_Type;

/**
 *  @brief Serail flash controller AES type definition
 */
typedef enum {
    SF_CTRL_AES_128BITS,            /*!< Serail flash AES key 128 bits length */
    SF_CTRL_AES_256BITS,            /*!< Serail flash AES key 256 bits length */
    SF_CTRL_AES_192BITS,            /*!< Serail flash AES key 192 bits length */
    SF_CTRL_AES_128BITS_DOUBLE_KEY, /*!< Serail flash AES key 128 bits length double key */
} SF_Ctrl_AES_Key_Type;

typedef enum {
    RESET = 0,
    SET = 1,
} BL_Sts_Type;

typedef struct
{
    uint8_t rwFlag;                  /*!< Read write flag */
    SF_Ctrl_Cmd_Mode_Type cmdMode;   /*!< Command mode */
    SF_Ctrl_Addr_Mode_Type addrMode; /*!< Address mode */
    uint8_t addrSize;                /*!< Address size */
    uint8_t dummyClks;               /*!< Dummy clocks */
    SF_Ctrl_Dmy_Mode_Type dummyMode; /*!< Dummy mode */
    SF_Ctrl_Data_Mode_Type dataMode; /*!< Data mode */
    uint8_t rsv[1];                  /*!<  */
    uint32_t nbData;                 /*!< Transfer number of bytes */
    uint32_t cmdBuf[2];              /*!< Command buffer */
} SF_Ctrl_Cmd_Cfg_Type;

typedef struct
{
    uint32_t jedecID;
    char *name;
    const SPI_Flash_Cfg_Type *cfg;
} Flash_Info_t;

#define BL_SET_REG_BIT(val, bitname)              ((val) | (1U << bitname##_POS))
#define BL_CLR_REG_BIT(val, bitname)              ((val)&bitname##_UMSK)
#define BL_GET_REG_BITS_VAL(val, bitname)         (((val)&bitname##_MSK) >> bitname##_POS)
#define BL_SET_REG_BITS_VAL(val, bitname, bitval) (((val)&bitname##_UMSK) | ((uint32_t)(bitval) << bitname##_POS))
#define BL_IS_REG_BIT_SET(val, bitname)           (((val) & (1U << (bitname##_POS))) != 0)

/* 0x0 : sf_ctrl_0 */
#define SF_CTRL_0_OFFSET                  (0x0)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL      SF_CTRL_SF_CLK_SF_RX_INV_SEL
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_POS  (2U)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_LEN  (1U)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_MSK  (((1U << SF_CTRL_SF_CLK_SF_RX_INV_SEL_LEN) - 1) << SF_CTRL_SF_CLK_SF_RX_INV_SEL_POS)
#define SF_CTRL_SF_CLK_SF_RX_INV_SEL_UMSK (~(((1U << SF_CTRL_SF_CLK_SF_RX_INV_SEL_LEN) - 1) << SF_CTRL_SF_CLK_SF_RX_INV_SEL_POS))
#define SF_CTRL_SF_CLK_OUT_GATE_EN        SF_CTRL_SF_CLK_OUT_GATE_EN
#define SF_CTRL_SF_CLK_OUT_GATE_EN_POS    (3U)
#define SF_CTRL_SF_CLK_OUT_GATE_EN_LEN    (1U)
#define SF_CTRL_SF_CLK_OUT_GATE_EN_MSK    (((1U << SF_CTRL_SF_CLK_OUT_GATE_EN_LEN) - 1) << SF_CTRL_SF_CLK_OUT_GATE_EN_POS)
#define SF_CTRL_SF_CLK_OUT_GATE_EN_UMSK   (~(((1U << SF_CTRL_SF_CLK_OUT_GATE_EN_LEN) - 1) << SF_CTRL_SF_CLK_OUT_GATE_EN_POS))
#define SF_CTRL_SF_CLK_OUT_INV_SEL        SF_CTRL_SF_CLK_OUT_INV_SEL
#define SF_CTRL_SF_CLK_OUT_INV_SEL_POS    (4U)
#define SF_CTRL_SF_CLK_OUT_INV_SEL_LEN    (1U)
#define SF_CTRL_SF_CLK_OUT_INV_SEL_MSK    (((1U << SF_CTRL_SF_CLK_OUT_INV_SEL_LEN) - 1) << SF_CTRL_SF_CLK_OUT_INV_SEL_POS)
#define SF_CTRL_SF_CLK_OUT_INV_SEL_UMSK   (~(((1U << SF_CTRL_SF_CLK_OUT_INV_SEL_LEN) - 1) << SF_CTRL_SF_CLK_OUT_INV_SEL_POS))
#define SF_CTRL_SF_CLK_SAHB_SRAM_SEL      SF_CTRL_SF_CLK_SAHB_SRAM_SEL
#define SF_CTRL_SF_CLK_SAHB_SRAM_SEL_POS  (5U)
#define SF_CTRL_SF_CLK_SAHB_SRAM_SEL_LEN  (1U)
#define SF_CTRL_SF_CLK_SAHB_SRAM_SEL_MSK  (((1U << SF_CTRL_SF_CLK_SAHB_SRAM_SEL_LEN) - 1) << SF_CTRL_SF_CLK_SAHB_SRAM_SEL_POS)
#define SF_CTRL_SF_CLK_SAHB_SRAM_SEL_UMSK (~(((1U << SF_CTRL_SF_CLK_SAHB_SRAM_SEL_LEN) - 1) << SF_CTRL_SF_CLK_SAHB_SRAM_SEL_POS))
#define SF_CTRL_SF_IF_READ_DLY_N          SF_CTRL_SF_IF_READ_DLY_N
#define SF_CTRL_SF_IF_READ_DLY_N_POS      (8U)
#define SF_CTRL_SF_IF_READ_DLY_N_LEN      (3U)
#define SF_CTRL_SF_IF_READ_DLY_N_MSK      (((1U << SF_CTRL_SF_IF_READ_DLY_N_LEN) - 1) << SF_CTRL_SF_IF_READ_DLY_N_POS)
#define SF_CTRL_SF_IF_READ_DLY_N_UMSK     (~(((1U << SF_CTRL_SF_IF_READ_DLY_N_LEN) - 1) << SF_CTRL_SF_IF_READ_DLY_N_POS))
#define SF_CTRL_SF_IF_READ_DLY_EN         SF_CTRL_SF_IF_READ_DLY_EN
#define SF_CTRL_SF_IF_READ_DLY_EN_POS     (11U)
#define SF_CTRL_SF_IF_READ_DLY_EN_LEN     (1U)
#define SF_CTRL_SF_IF_READ_DLY_EN_MSK     (((1U << SF_CTRL_SF_IF_READ_DLY_EN_LEN) - 1) << SF_CTRL_SF_IF_READ_DLY_EN_POS)
#define SF_CTRL_SF_IF_READ_DLY_EN_UMSK    (~(((1U << SF_CTRL_SF_IF_READ_DLY_EN_LEN) - 1) << SF_CTRL_SF_IF_READ_DLY_EN_POS))
#define SF_CTRL_SF_IF_INT                 SF_CTRL_SF_IF_INT
#define SF_CTRL_SF_IF_INT_POS             (16U)
#define SF_CTRL_SF_IF_INT_LEN             (1U)
#define SF_CTRL_SF_IF_INT_MSK             (((1U << SF_CTRL_SF_IF_INT_LEN) - 1) << SF_CTRL_SF_IF_INT_POS)
#define SF_CTRL_SF_IF_INT_UMSK            (~(((1U << SF_CTRL_SF_IF_INT_LEN) - 1) << SF_CTRL_SF_IF_INT_POS))
#define SF_CTRL_SF_IF_INT_CLR             SF_CTRL_SF_IF_INT_CLR
#define SF_CTRL_SF_IF_INT_CLR_POS         (17U)
#define SF_CTRL_SF_IF_INT_CLR_LEN         (1U)
#define SF_CTRL_SF_IF_INT_CLR_MSK         (((1U << SF_CTRL_SF_IF_INT_CLR_LEN) - 1) << SF_CTRL_SF_IF_INT_CLR_POS)
#define SF_CTRL_SF_IF_INT_CLR_UMSK        (~(((1U << SF_CTRL_SF_IF_INT_CLR_LEN) - 1) << SF_CTRL_SF_IF_INT_CLR_POS))
#define SF_CTRL_SF_IF_INT_SET             SF_CTRL_SF_IF_INT_SET
#define SF_CTRL_SF_IF_INT_SET_POS         (18U)
#define SF_CTRL_SF_IF_INT_SET_LEN         (1U)
#define SF_CTRL_SF_IF_INT_SET_MSK         (((1U << SF_CTRL_SF_IF_INT_SET_LEN) - 1) << SF_CTRL_SF_IF_INT_SET_POS)
#define SF_CTRL_SF_IF_INT_SET_UMSK        (~(((1U << SF_CTRL_SF_IF_INT_SET_LEN) - 1) << SF_CTRL_SF_IF_INT_SET_POS))
#define SF_CTRL_SF_AES_DLY_MODE           SF_CTRL_SF_AES_DLY_MODE
#define SF_CTRL_SF_AES_DLY_MODE_POS       (19U)
#define SF_CTRL_SF_AES_DLY_MODE_LEN       (1U)
#define SF_CTRL_SF_AES_DLY_MODE_MSK       (((1U << SF_CTRL_SF_AES_DLY_MODE_LEN) - 1) << SF_CTRL_SF_AES_DLY_MODE_POS)
#define SF_CTRL_SF_AES_DLY_MODE_UMSK      (~(((1U << SF_CTRL_SF_AES_DLY_MODE_LEN) - 1) << SF_CTRL_SF_AES_DLY_MODE_POS))
#define SF_CTRL_SF_AES_DOUT_ENDIAN        SF_CTRL_SF_AES_DOUT_ENDIAN
#define SF_CTRL_SF_AES_DOUT_ENDIAN_POS    (20U)
#define SF_CTRL_SF_AES_DOUT_ENDIAN_LEN    (1U)
#define SF_CTRL_SF_AES_DOUT_ENDIAN_MSK    (((1U << SF_CTRL_SF_AES_DOUT_ENDIAN_LEN) - 1) << SF_CTRL_SF_AES_DOUT_ENDIAN_POS)
#define SF_CTRL_SF_AES_DOUT_ENDIAN_UMSK   (~(((1U << SF_CTRL_SF_AES_DOUT_ENDIAN_LEN) - 1) << SF_CTRL_SF_AES_DOUT_ENDIAN_POS))
#define SF_CTRL_SF_AES_CTR_PLUS_EN        SF_CTRL_SF_AES_CTR_PLUS_EN
#define SF_CTRL_SF_AES_CTR_PLUS_EN_POS    (21U)
#define SF_CTRL_SF_AES_CTR_PLUS_EN_LEN    (1U)
#define SF_CTRL_SF_AES_CTR_PLUS_EN_MSK    (((1U << SF_CTRL_SF_AES_CTR_PLUS_EN_LEN) - 1) << SF_CTRL_SF_AES_CTR_PLUS_EN_POS)
#define SF_CTRL_SF_AES_CTR_PLUS_EN_UMSK   (~(((1U << SF_CTRL_SF_AES_CTR_PLUS_EN_LEN) - 1) << SF_CTRL_SF_AES_CTR_PLUS_EN_POS))
#define SF_CTRL_SF_AES_KEY_ENDIAN         SF_CTRL_SF_AES_KEY_ENDIAN
#define SF_CTRL_SF_AES_KEY_ENDIAN_POS     (22U)
#define SF_CTRL_SF_AES_KEY_ENDIAN_LEN     (1U)
#define SF_CTRL_SF_AES_KEY_ENDIAN_MSK     (((1U << SF_CTRL_SF_AES_KEY_ENDIAN_LEN) - 1) << SF_CTRL_SF_AES_KEY_ENDIAN_POS)
#define SF_CTRL_SF_AES_KEY_ENDIAN_UMSK    (~(((1U << SF_CTRL_SF_AES_KEY_ENDIAN_LEN) - 1) << SF_CTRL_SF_AES_KEY_ENDIAN_POS))
#define SF_CTRL_SF_AES_IV_ENDIAN          SF_CTRL_SF_AES_IV_ENDIAN
#define SF_CTRL_SF_AES_IV_ENDIAN_POS      (23U)
#define SF_CTRL_SF_AES_IV_ENDIAN_LEN      (1U)
#define SF_CTRL_SF_AES_IV_ENDIAN_MSK      (((1U << SF_CTRL_SF_AES_IV_ENDIAN_LEN) - 1) << SF_CTRL_SF_AES_IV_ENDIAN_POS)
#define SF_CTRL_SF_AES_IV_ENDIAN_UMSK     (~(((1U << SF_CTRL_SF_AES_IV_ENDIAN_LEN) - 1) << SF_CTRL_SF_AES_IV_ENDIAN_POS))
#define SF_CTRL_SF_ID                     SF_CTRL_SF_ID
#define SF_CTRL_SF_ID_POS                 (24U)
#define SF_CTRL_SF_ID_LEN                 (8U)
#define SF_CTRL_SF_ID_MSK                 (((1U << SF_CTRL_SF_ID_LEN) - 1) << SF_CTRL_SF_ID_POS)
#define SF_CTRL_SF_ID_UMSK                (~(((1U << SF_CTRL_SF_ID_LEN) - 1) << SF_CTRL_SF_ID_POS))

/* 0x4 : sf_ctrl_1 */
#define SF_CTRL_1_OFFSET                (0x4)
#define SF_CTRL_SF_IF_SR_PAT_MASK       SF_CTRL_SF_IF_SR_PAT_MASK
#define SF_CTRL_SF_IF_SR_PAT_MASK_POS   (0U)
#define SF_CTRL_SF_IF_SR_PAT_MASK_LEN   (8U)
#define SF_CTRL_SF_IF_SR_PAT_MASK_MSK   (((1U << SF_CTRL_SF_IF_SR_PAT_MASK_LEN) - 1) << SF_CTRL_SF_IF_SR_PAT_MASK_POS)
#define SF_CTRL_SF_IF_SR_PAT_MASK_UMSK  (~(((1U << SF_CTRL_SF_IF_SR_PAT_MASK_LEN) - 1) << SF_CTRL_SF_IF_SR_PAT_MASK_POS))
#define SF_CTRL_SF_IF_SR_PAT            SF_CTRL_SF_IF_SR_PAT
#define SF_CTRL_SF_IF_SR_PAT_POS        (8U)
#define SF_CTRL_SF_IF_SR_PAT_LEN        (8U)
#define SF_CTRL_SF_IF_SR_PAT_MSK        (((1U << SF_CTRL_SF_IF_SR_PAT_LEN) - 1) << SF_CTRL_SF_IF_SR_PAT_POS)
#define SF_CTRL_SF_IF_SR_PAT_UMSK       (~(((1U << SF_CTRL_SF_IF_SR_PAT_LEN) - 1) << SF_CTRL_SF_IF_SR_PAT_POS))
#define SF_CTRL_SF_IF_SR_INT            SF_CTRL_SF_IF_SR_INT
#define SF_CTRL_SF_IF_SR_INT_POS        (16U)
#define SF_CTRL_SF_IF_SR_INT_LEN        (1U)
#define SF_CTRL_SF_IF_SR_INT_MSK        (((1U << SF_CTRL_SF_IF_SR_INT_LEN) - 1) << SF_CTRL_SF_IF_SR_INT_POS)
#define SF_CTRL_SF_IF_SR_INT_UMSK       (~(((1U << SF_CTRL_SF_IF_SR_INT_LEN) - 1) << SF_CTRL_SF_IF_SR_INT_POS))
#define SF_CTRL_SF_IF_SR_INT_EN         SF_CTRL_SF_IF_SR_INT_EN
#define SF_CTRL_SF_IF_SR_INT_EN_POS     (17U)
#define SF_CTRL_SF_IF_SR_INT_EN_LEN     (1U)
#define SF_CTRL_SF_IF_SR_INT_EN_MSK     (((1U << SF_CTRL_SF_IF_SR_INT_EN_LEN) - 1) << SF_CTRL_SF_IF_SR_INT_EN_POS)
#define SF_CTRL_SF_IF_SR_INT_EN_UMSK    (~(((1U << SF_CTRL_SF_IF_SR_INT_EN_LEN) - 1) << SF_CTRL_SF_IF_SR_INT_EN_POS))
#define SF_CTRL_SF_IF_SR_INT_SET        SF_CTRL_SF_IF_SR_INT_SET
#define SF_CTRL_SF_IF_SR_INT_SET_POS    (18U)
#define SF_CTRL_SF_IF_SR_INT_SET_LEN    (1U)
#define SF_CTRL_SF_IF_SR_INT_SET_MSK    (((1U << SF_CTRL_SF_IF_SR_INT_SET_LEN) - 1) << SF_CTRL_SF_IF_SR_INT_SET_POS)
#define SF_CTRL_SF_IF_SR_INT_SET_UMSK   (~(((1U << SF_CTRL_SF_IF_SR_INT_SET_LEN) - 1) << SF_CTRL_SF_IF_SR_INT_SET_POS))
#define SF_CTRL_SF_IF_0_ACK_LAT         SF_CTRL_SF_IF_0_ACK_LAT
#define SF_CTRL_SF_IF_0_ACK_LAT_POS     (20U)
#define SF_CTRL_SF_IF_0_ACK_LAT_LEN     (3U)
#define SF_CTRL_SF_IF_0_ACK_LAT_MSK     (((1U << SF_CTRL_SF_IF_0_ACK_LAT_LEN) - 1) << SF_CTRL_SF_IF_0_ACK_LAT_POS)
#define SF_CTRL_SF_IF_0_ACK_LAT_UMSK    (~(((1U << SF_CTRL_SF_IF_0_ACK_LAT_LEN) - 1) << SF_CTRL_SF_IF_0_ACK_LAT_POS))
#define SF_CTRL_SF_IF_REG_HOLD          SF_CTRL_SF_IF_REG_HOLD
#define SF_CTRL_SF_IF_REG_HOLD_POS      (24U)
#define SF_CTRL_SF_IF_REG_HOLD_LEN      (1U)
#define SF_CTRL_SF_IF_REG_HOLD_MSK      (((1U << SF_CTRL_SF_IF_REG_HOLD_LEN) - 1) << SF_CTRL_SF_IF_REG_HOLD_POS)
#define SF_CTRL_SF_IF_REG_HOLD_UMSK     (~(((1U << SF_CTRL_SF_IF_REG_HOLD_LEN) - 1) << SF_CTRL_SF_IF_REG_HOLD_POS))
#define SF_CTRL_SF_IF_REG_WP            SF_CTRL_SF_IF_REG_WP
#define SF_CTRL_SF_IF_REG_WP_POS        (25U)
#define SF_CTRL_SF_IF_REG_WP_LEN        (1U)
#define SF_CTRL_SF_IF_REG_WP_MSK        (((1U << SF_CTRL_SF_IF_REG_WP_LEN) - 1) << SF_CTRL_SF_IF_REG_WP_POS)
#define SF_CTRL_SF_IF_REG_WP_UMSK       (~(((1U << SF_CTRL_SF_IF_REG_WP_LEN) - 1) << SF_CTRL_SF_IF_REG_WP_POS))
#define SF_CTRL_SF_AHB2SIF_STOPPED      SF_CTRL_SF_AHB2SIF_STOPPED
#define SF_CTRL_SF_AHB2SIF_STOPPED_POS  (26U)
#define SF_CTRL_SF_AHB2SIF_STOPPED_LEN  (1U)
#define SF_CTRL_SF_AHB2SIF_STOPPED_MSK  (((1U << SF_CTRL_SF_AHB2SIF_STOPPED_LEN) - 1) << SF_CTRL_SF_AHB2SIF_STOPPED_POS)
#define SF_CTRL_SF_AHB2SIF_STOPPED_UMSK (~(((1U << SF_CTRL_SF_AHB2SIF_STOPPED_LEN) - 1) << SF_CTRL_SF_AHB2SIF_STOPPED_POS))
#define SF_CTRL_SF_AHB2SIF_STOP         SF_CTRL_SF_AHB2SIF_STOP
#define SF_CTRL_SF_AHB2SIF_STOP_POS     (27U)
#define SF_CTRL_SF_AHB2SIF_STOP_LEN     (1U)
#define SF_CTRL_SF_AHB2SIF_STOP_MSK     (((1U << SF_CTRL_SF_AHB2SIF_STOP_LEN) - 1) << SF_CTRL_SF_AHB2SIF_STOP_POS)
#define SF_CTRL_SF_AHB2SIF_STOP_UMSK    (~(((1U << SF_CTRL_SF_AHB2SIF_STOP_LEN) - 1) << SF_CTRL_SF_AHB2SIF_STOP_POS))
#define SF_CTRL_SF_IF_FN_SEL            SF_CTRL_SF_IF_FN_SEL
#define SF_CTRL_SF_IF_FN_SEL_POS        (28U)
#define SF_CTRL_SF_IF_FN_SEL_LEN        (1U)
#define SF_CTRL_SF_IF_FN_SEL_MSK        (((1U << SF_CTRL_SF_IF_FN_SEL_LEN) - 1) << SF_CTRL_SF_IF_FN_SEL_POS)
#define SF_CTRL_SF_IF_FN_SEL_UMSK       (~(((1U << SF_CTRL_SF_IF_FN_SEL_LEN) - 1) << SF_CTRL_SF_IF_FN_SEL_POS))
#define SF_CTRL_SF_IF_EN                SF_CTRL_SF_IF_EN
#define SF_CTRL_SF_IF_EN_POS            (29U)
#define SF_CTRL_SF_IF_EN_LEN            (1U)
#define SF_CTRL_SF_IF_EN_MSK            (((1U << SF_CTRL_SF_IF_EN_LEN) - 1) << SF_CTRL_SF_IF_EN_POS)
#define SF_CTRL_SF_IF_EN_UMSK           (~(((1U << SF_CTRL_SF_IF_EN_LEN) - 1) << SF_CTRL_SF_IF_EN_POS))
#define SF_CTRL_SF_AHB2SIF_EN           SF_CTRL_SF_AHB2SIF_EN
#define SF_CTRL_SF_AHB2SIF_EN_POS       (30U)
#define SF_CTRL_SF_AHB2SIF_EN_LEN       (1U)
#define SF_CTRL_SF_AHB2SIF_EN_MSK       (((1U << SF_CTRL_SF_AHB2SIF_EN_LEN) - 1) << SF_CTRL_SF_AHB2SIF_EN_POS)
#define SF_CTRL_SF_AHB2SIF_EN_UMSK      (~(((1U << SF_CTRL_SF_AHB2SIF_EN_LEN) - 1) << SF_CTRL_SF_AHB2SIF_EN_POS))
#define SF_CTRL_SF_AHB2SRAM_EN          SF_CTRL_SF_AHB2SRAM_EN
#define SF_CTRL_SF_AHB2SRAM_EN_POS      (31U)
#define SF_CTRL_SF_AHB2SRAM_EN_LEN      (1U)
#define SF_CTRL_SF_AHB2SRAM_EN_MSK      (((1U << SF_CTRL_SF_AHB2SRAM_EN_LEN) - 1) << SF_CTRL_SF_AHB2SRAM_EN_POS)
#define SF_CTRL_SF_AHB2SRAM_EN_UMSK     (~(((1U << SF_CTRL_SF_AHB2SRAM_EN_LEN) - 1) << SF_CTRL_SF_AHB2SRAM_EN_POS))

/* 0x8 : sf_if_sahb_0 */
#define SF_CTRL_SF_IF_SAHB_0_OFFSET      (0x8)
#define SF_CTRL_SF_IF_BUSY               SF_CTRL_SF_IF_BUSY
#define SF_CTRL_SF_IF_BUSY_POS           (0U)
#define SF_CTRL_SF_IF_BUSY_LEN           (1U)
#define SF_CTRL_SF_IF_BUSY_MSK           (((1U << SF_CTRL_SF_IF_BUSY_LEN) - 1) << SF_CTRL_SF_IF_BUSY_POS)
#define SF_CTRL_SF_IF_BUSY_UMSK          (~(((1U << SF_CTRL_SF_IF_BUSY_LEN) - 1) << SF_CTRL_SF_IF_BUSY_POS))
#define SF_CTRL_SF_IF_0_TRIG             SF_CTRL_SF_IF_0_TRIG
#define SF_CTRL_SF_IF_0_TRIG_POS         (1U)
#define SF_CTRL_SF_IF_0_TRIG_LEN         (1U)
#define SF_CTRL_SF_IF_0_TRIG_MSK         (((1U << SF_CTRL_SF_IF_0_TRIG_LEN) - 1) << SF_CTRL_SF_IF_0_TRIG_POS)
#define SF_CTRL_SF_IF_0_TRIG_UMSK        (~(((1U << SF_CTRL_SF_IF_0_TRIG_LEN) - 1) << SF_CTRL_SF_IF_0_TRIG_POS))
#define SF_CTRL_SF_IF_0_DAT_BYTE         SF_CTRL_SF_IF_0_DAT_BYTE
#define SF_CTRL_SF_IF_0_DAT_BYTE_POS     (2U)
#define SF_CTRL_SF_IF_0_DAT_BYTE_LEN     (10U)
#define SF_CTRL_SF_IF_0_DAT_BYTE_MSK     (((1U << SF_CTRL_SF_IF_0_DAT_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_DAT_BYTE_POS)
#define SF_CTRL_SF_IF_0_DAT_BYTE_UMSK    (~(((1U << SF_CTRL_SF_IF_0_DAT_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_DAT_BYTE_POS))
#define SF_CTRL_SF_IF_0_DMY_BYTE         SF_CTRL_SF_IF_0_DMY_BYTE
#define SF_CTRL_SF_IF_0_DMY_BYTE_POS     (12U)
#define SF_CTRL_SF_IF_0_DMY_BYTE_LEN     (5U)
#define SF_CTRL_SF_IF_0_DMY_BYTE_MSK     (((1U << SF_CTRL_SF_IF_0_DMY_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_DMY_BYTE_POS)
#define SF_CTRL_SF_IF_0_DMY_BYTE_UMSK    (~(((1U << SF_CTRL_SF_IF_0_DMY_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_DMY_BYTE_POS))
#define SF_CTRL_SF_IF_0_ADR_BYTE         SF_CTRL_SF_IF_0_ADR_BYTE
#define SF_CTRL_SF_IF_0_ADR_BYTE_POS     (17U)
#define SF_CTRL_SF_IF_0_ADR_BYTE_LEN     (3U)
#define SF_CTRL_SF_IF_0_ADR_BYTE_MSK     (((1U << SF_CTRL_SF_IF_0_ADR_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_ADR_BYTE_POS)
#define SF_CTRL_SF_IF_0_ADR_BYTE_UMSK    (~(((1U << SF_CTRL_SF_IF_0_ADR_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_ADR_BYTE_POS))
#define SF_CTRL_SF_IF_0_CMD_BYTE         SF_CTRL_SF_IF_0_CMD_BYTE
#define SF_CTRL_SF_IF_0_CMD_BYTE_POS     (20U)
#define SF_CTRL_SF_IF_0_CMD_BYTE_LEN     (3U)
#define SF_CTRL_SF_IF_0_CMD_BYTE_MSK     (((1U << SF_CTRL_SF_IF_0_CMD_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_BYTE_POS)
#define SF_CTRL_SF_IF_0_CMD_BYTE_UMSK    (~(((1U << SF_CTRL_SF_IF_0_CMD_BYTE_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_BYTE_POS))
#define SF_CTRL_SF_IF_0_DAT_RW           SF_CTRL_SF_IF_0_DAT_RW
#define SF_CTRL_SF_IF_0_DAT_RW_POS       (23U)
#define SF_CTRL_SF_IF_0_DAT_RW_LEN       (1U)
#define SF_CTRL_SF_IF_0_DAT_RW_MSK       (((1U << SF_CTRL_SF_IF_0_DAT_RW_LEN) - 1) << SF_CTRL_SF_IF_0_DAT_RW_POS)
#define SF_CTRL_SF_IF_0_DAT_RW_UMSK      (~(((1U << SF_CTRL_SF_IF_0_DAT_RW_LEN) - 1) << SF_CTRL_SF_IF_0_DAT_RW_POS))
#define SF_CTRL_SF_IF_0_DAT_EN           SF_CTRL_SF_IF_0_DAT_EN
#define SF_CTRL_SF_IF_0_DAT_EN_POS       (24U)
#define SF_CTRL_SF_IF_0_DAT_EN_LEN       (1U)
#define SF_CTRL_SF_IF_0_DAT_EN_MSK       (((1U << SF_CTRL_SF_IF_0_DAT_EN_LEN) - 1) << SF_CTRL_SF_IF_0_DAT_EN_POS)
#define SF_CTRL_SF_IF_0_DAT_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_0_DAT_EN_LEN) - 1) << SF_CTRL_SF_IF_0_DAT_EN_POS))
#define SF_CTRL_SF_IF_0_DMY_EN           SF_CTRL_SF_IF_0_DMY_EN
#define SF_CTRL_SF_IF_0_DMY_EN_POS       (25U)
#define SF_CTRL_SF_IF_0_DMY_EN_LEN       (1U)
#define SF_CTRL_SF_IF_0_DMY_EN_MSK       (((1U << SF_CTRL_SF_IF_0_DMY_EN_LEN) - 1) << SF_CTRL_SF_IF_0_DMY_EN_POS)
#define SF_CTRL_SF_IF_0_DMY_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_0_DMY_EN_LEN) - 1) << SF_CTRL_SF_IF_0_DMY_EN_POS))
#define SF_CTRL_SF_IF_0_ADR_EN           SF_CTRL_SF_IF_0_ADR_EN
#define SF_CTRL_SF_IF_0_ADR_EN_POS       (26U)
#define SF_CTRL_SF_IF_0_ADR_EN_LEN       (1U)
#define SF_CTRL_SF_IF_0_ADR_EN_MSK       (((1U << SF_CTRL_SF_IF_0_ADR_EN_LEN) - 1) << SF_CTRL_SF_IF_0_ADR_EN_POS)
#define SF_CTRL_SF_IF_0_ADR_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_0_ADR_EN_LEN) - 1) << SF_CTRL_SF_IF_0_ADR_EN_POS))
#define SF_CTRL_SF_IF_0_CMD_EN           SF_CTRL_SF_IF_0_CMD_EN
#define SF_CTRL_SF_IF_0_CMD_EN_POS       (27U)
#define SF_CTRL_SF_IF_0_CMD_EN_LEN       (1U)
#define SF_CTRL_SF_IF_0_CMD_EN_MSK       (((1U << SF_CTRL_SF_IF_0_CMD_EN_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_EN_POS)
#define SF_CTRL_SF_IF_0_CMD_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_0_CMD_EN_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_EN_POS))
#define SF_CTRL_SF_IF_0_SPI_MODE         SF_CTRL_SF_IF_0_SPI_MODE
#define SF_CTRL_SF_IF_0_SPI_MODE_POS     (28U)
#define SF_CTRL_SF_IF_0_SPI_MODE_LEN     (3U)
#define SF_CTRL_SF_IF_0_SPI_MODE_MSK     (((1U << SF_CTRL_SF_IF_0_SPI_MODE_LEN) - 1) << SF_CTRL_SF_IF_0_SPI_MODE_POS)
#define SF_CTRL_SF_IF_0_SPI_MODE_UMSK    (~(((1U << SF_CTRL_SF_IF_0_SPI_MODE_LEN) - 1) << SF_CTRL_SF_IF_0_SPI_MODE_POS))
#define SF_CTRL_SF_IF_0_QPI_MODE_EN      SF_CTRL_SF_IF_0_QPI_MODE_EN
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_POS  (31U)
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_LEN  (1U)
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_MSK  (((1U << SF_CTRL_SF_IF_0_QPI_MODE_EN_LEN) - 1) << SF_CTRL_SF_IF_0_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF_0_QPI_MODE_EN_UMSK (~(((1U << SF_CTRL_SF_IF_0_QPI_MODE_EN_LEN) - 1) << SF_CTRL_SF_IF_0_QPI_MODE_EN_POS))

/* 0xC : sf_if_sahb_1 */
#define SF_CTRL_SF_IF_SAHB_1_OFFSET    (0xC)
#define SF_CTRL_SF_IF_0_CMD_BUF_0      SF_CTRL_SF_IF_0_CMD_BUF_0
#define SF_CTRL_SF_IF_0_CMD_BUF_0_POS  (0U)
#define SF_CTRL_SF_IF_0_CMD_BUF_0_LEN  (32U)
#define SF_CTRL_SF_IF_0_CMD_BUF_0_MSK  (((1U << SF_CTRL_SF_IF_0_CMD_BUF_0_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF_0_CMD_BUF_0_UMSK (~(((1U << SF_CTRL_SF_IF_0_CMD_BUF_0_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_BUF_0_POS))

/* 0x10 : sf_if_sahb_2 */
#define SF_CTRL_SF_IF_SAHB_2_OFFSET    (0x10)
#define SF_CTRL_SF_IF_0_CMD_BUF_1      SF_CTRL_SF_IF_0_CMD_BUF_1
#define SF_CTRL_SF_IF_0_CMD_BUF_1_POS  (0U)
#define SF_CTRL_SF_IF_0_CMD_BUF_1_LEN  (32U)
#define SF_CTRL_SF_IF_0_CMD_BUF_1_MSK  (((1U << SF_CTRL_SF_IF_0_CMD_BUF_1_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF_0_CMD_BUF_1_UMSK (~(((1U << SF_CTRL_SF_IF_0_CMD_BUF_1_LEN) - 1) << SF_CTRL_SF_IF_0_CMD_BUF_1_POS))

/* 0x14 : sf_if_iahb_0 */
#define SF_CTRL_SF_IF_IAHB_0_OFFSET      (0x14)
#define SF_CTRL_SF_IF_1_DMY_BYTE         SF_CTRL_SF_IF_1_DMY_BYTE
#define SF_CTRL_SF_IF_1_DMY_BYTE_POS     (12U)
#define SF_CTRL_SF_IF_1_DMY_BYTE_LEN     (5U)
#define SF_CTRL_SF_IF_1_DMY_BYTE_MSK     (((1U << SF_CTRL_SF_IF_1_DMY_BYTE_LEN) - 1) << SF_CTRL_SF_IF_1_DMY_BYTE_POS)
#define SF_CTRL_SF_IF_1_DMY_BYTE_UMSK    (~(((1U << SF_CTRL_SF_IF_1_DMY_BYTE_LEN) - 1) << SF_CTRL_SF_IF_1_DMY_BYTE_POS))
#define SF_CTRL_SF_IF_1_ADR_BYTE         SF_CTRL_SF_IF_1_ADR_BYTE
#define SF_CTRL_SF_IF_1_ADR_BYTE_POS     (17U)
#define SF_CTRL_SF_IF_1_ADR_BYTE_LEN     (3U)
#define SF_CTRL_SF_IF_1_ADR_BYTE_MSK     (((1U << SF_CTRL_SF_IF_1_ADR_BYTE_LEN) - 1) << SF_CTRL_SF_IF_1_ADR_BYTE_POS)
#define SF_CTRL_SF_IF_1_ADR_BYTE_UMSK    (~(((1U << SF_CTRL_SF_IF_1_ADR_BYTE_LEN) - 1) << SF_CTRL_SF_IF_1_ADR_BYTE_POS))
#define SF_CTRL_SF_IF_1_CMD_BYTE         SF_CTRL_SF_IF_1_CMD_BYTE
#define SF_CTRL_SF_IF_1_CMD_BYTE_POS     (20U)
#define SF_CTRL_SF_IF_1_CMD_BYTE_LEN     (3U)
#define SF_CTRL_SF_IF_1_CMD_BYTE_MSK     (((1U << SF_CTRL_SF_IF_1_CMD_BYTE_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_BYTE_POS)
#define SF_CTRL_SF_IF_1_CMD_BYTE_UMSK    (~(((1U << SF_CTRL_SF_IF_1_CMD_BYTE_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_BYTE_POS))
#define SF_CTRL_SF_IF_1_DAT_RW           SF_CTRL_SF_IF_1_DAT_RW
#define SF_CTRL_SF_IF_1_DAT_RW_POS       (23U)
#define SF_CTRL_SF_IF_1_DAT_RW_LEN       (1U)
#define SF_CTRL_SF_IF_1_DAT_RW_MSK       (((1U << SF_CTRL_SF_IF_1_DAT_RW_LEN) - 1) << SF_CTRL_SF_IF_1_DAT_RW_POS)
#define SF_CTRL_SF_IF_1_DAT_RW_UMSK      (~(((1U << SF_CTRL_SF_IF_1_DAT_RW_LEN) - 1) << SF_CTRL_SF_IF_1_DAT_RW_POS))
#define SF_CTRL_SF_IF_1_DAT_EN           SF_CTRL_SF_IF_1_DAT_EN
#define SF_CTRL_SF_IF_1_DAT_EN_POS       (24U)
#define SF_CTRL_SF_IF_1_DAT_EN_LEN       (1U)
#define SF_CTRL_SF_IF_1_DAT_EN_MSK       (((1U << SF_CTRL_SF_IF_1_DAT_EN_LEN) - 1) << SF_CTRL_SF_IF_1_DAT_EN_POS)
#define SF_CTRL_SF_IF_1_DAT_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_1_DAT_EN_LEN) - 1) << SF_CTRL_SF_IF_1_DAT_EN_POS))
#define SF_CTRL_SF_IF_1_DMY_EN           SF_CTRL_SF_IF_1_DMY_EN
#define SF_CTRL_SF_IF_1_DMY_EN_POS       (25U)
#define SF_CTRL_SF_IF_1_DMY_EN_LEN       (1U)
#define SF_CTRL_SF_IF_1_DMY_EN_MSK       (((1U << SF_CTRL_SF_IF_1_DMY_EN_LEN) - 1) << SF_CTRL_SF_IF_1_DMY_EN_POS)
#define SF_CTRL_SF_IF_1_DMY_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_1_DMY_EN_LEN) - 1) << SF_CTRL_SF_IF_1_DMY_EN_POS))
#define SF_CTRL_SF_IF_1_ADR_EN           SF_CTRL_SF_IF_1_ADR_EN
#define SF_CTRL_SF_IF_1_ADR_EN_POS       (26U)
#define SF_CTRL_SF_IF_1_ADR_EN_LEN       (1U)
#define SF_CTRL_SF_IF_1_ADR_EN_MSK       (((1U << SF_CTRL_SF_IF_1_ADR_EN_LEN) - 1) << SF_CTRL_SF_IF_1_ADR_EN_POS)
#define SF_CTRL_SF_IF_1_ADR_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_1_ADR_EN_LEN) - 1) << SF_CTRL_SF_IF_1_ADR_EN_POS))
#define SF_CTRL_SF_IF_1_CMD_EN           SF_CTRL_SF_IF_1_CMD_EN
#define SF_CTRL_SF_IF_1_CMD_EN_POS       (27U)
#define SF_CTRL_SF_IF_1_CMD_EN_LEN       (1U)
#define SF_CTRL_SF_IF_1_CMD_EN_MSK       (((1U << SF_CTRL_SF_IF_1_CMD_EN_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_EN_POS)
#define SF_CTRL_SF_IF_1_CMD_EN_UMSK      (~(((1U << SF_CTRL_SF_IF_1_CMD_EN_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_EN_POS))
#define SF_CTRL_SF_IF_1_SPI_MODE         SF_CTRL_SF_IF_1_SPI_MODE
#define SF_CTRL_SF_IF_1_SPI_MODE_POS     (28U)
#define SF_CTRL_SF_IF_1_SPI_MODE_LEN     (3U)
#define SF_CTRL_SF_IF_1_SPI_MODE_MSK     (((1U << SF_CTRL_SF_IF_1_SPI_MODE_LEN) - 1) << SF_CTRL_SF_IF_1_SPI_MODE_POS)
#define SF_CTRL_SF_IF_1_SPI_MODE_UMSK    (~(((1U << SF_CTRL_SF_IF_1_SPI_MODE_LEN) - 1) << SF_CTRL_SF_IF_1_SPI_MODE_POS))
#define SF_CTRL_SF_IF_1_QPI_MODE_EN      SF_CTRL_SF_IF_1_QPI_MODE_EN
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_POS  (31U)
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_LEN  (1U)
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_MSK  (((1U << SF_CTRL_SF_IF_1_QPI_MODE_EN_LEN) - 1) << SF_CTRL_SF_IF_1_QPI_MODE_EN_POS)
#define SF_CTRL_SF_IF_1_QPI_MODE_EN_UMSK (~(((1U << SF_CTRL_SF_IF_1_QPI_MODE_EN_LEN) - 1) << SF_CTRL_SF_IF_1_QPI_MODE_EN_POS))

/* 0x18 : sf_if_iahb_1 */
#define SF_CTRL_SF_IF_IAHB_1_OFFSET    (0x18)
#define SF_CTRL_SF_IF_1_CMD_BUF_0      SF_CTRL_SF_IF_1_CMD_BUF_0
#define SF_CTRL_SF_IF_1_CMD_BUF_0_POS  (0U)
#define SF_CTRL_SF_IF_1_CMD_BUF_0_LEN  (32U)
#define SF_CTRL_SF_IF_1_CMD_BUF_0_MSK  (((1U << SF_CTRL_SF_IF_1_CMD_BUF_0_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_BUF_0_POS)
#define SF_CTRL_SF_IF_1_CMD_BUF_0_UMSK (~(((1U << SF_CTRL_SF_IF_1_CMD_BUF_0_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_BUF_0_POS))

/* 0x1C : sf_if_iahb_2 */
#define SF_CTRL_SF_IF_IAHB_2_OFFSET    (0x1C)
#define SF_CTRL_SF_IF_1_CMD_BUF_1      SF_CTRL_SF_IF_1_CMD_BUF_1
#define SF_CTRL_SF_IF_1_CMD_BUF_1_POS  (0U)
#define SF_CTRL_SF_IF_1_CMD_BUF_1_LEN  (32U)
#define SF_CTRL_SF_IF_1_CMD_BUF_1_MSK  (((1U << SF_CTRL_SF_IF_1_CMD_BUF_1_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_BUF_1_POS)
#define SF_CTRL_SF_IF_1_CMD_BUF_1_UMSK (~(((1U << SF_CTRL_SF_IF_1_CMD_BUF_1_LEN) - 1) << SF_CTRL_SF_IF_1_CMD_BUF_1_POS))

/* 0x20 : sf_if_status_0 */
#define SF_CTRL_SF_IF_STATUS_0_OFFSET (0x20)
#define SF_CTRL_SF_IF_STATUS_0        SF_CTRL_SF_IF_STATUS_0
#define SF_CTRL_SF_IF_STATUS_0_POS    (0U)
#define SF_CTRL_SF_IF_STATUS_0_LEN    (32U)
#define SF_CTRL_SF_IF_STATUS_0_MSK    (((1U << SF_CTRL_SF_IF_STATUS_0_LEN) - 1) << SF_CTRL_SF_IF_STATUS_0_POS)
#define SF_CTRL_SF_IF_STATUS_0_UMSK   (~(((1U << SF_CTRL_SF_IF_STATUS_0_LEN) - 1) << SF_CTRL_SF_IF_STATUS_0_POS))

/* 0x24 : sf_if_status_1 */
#define SF_CTRL_SF_IF_STATUS_1_OFFSET (0x24)
#define SF_CTRL_SF_IF_STATUS_1        SF_CTRL_SF_IF_STATUS_1
#define SF_CTRL_SF_IF_STATUS_1_POS    (0U)
#define SF_CTRL_SF_IF_STATUS_1_LEN    (32U)
#define SF_CTRL_SF_IF_STATUS_1_MSK    (((1U << SF_CTRL_SF_IF_STATUS_1_LEN) - 1) << SF_CTRL_SF_IF_STATUS_1_POS)
#define SF_CTRL_SF_IF_STATUS_1_UMSK   (~(((1U << SF_CTRL_SF_IF_STATUS_1_LEN) - 1) << SF_CTRL_SF_IF_STATUS_1_POS))

/* 0x28 : sf_aes */
#define SF_CTRL_SF_AES_OFFSET         (0x28)
#define SF_CTRL_SF_AES_EN             SF_CTRL_SF_AES_EN
#define SF_CTRL_SF_AES_EN_POS         (0U)
#define SF_CTRL_SF_AES_EN_LEN         (1U)
#define SF_CTRL_SF_AES_EN_MSK         (((1U << SF_CTRL_SF_AES_EN_LEN) - 1) << SF_CTRL_SF_AES_EN_POS)
#define SF_CTRL_SF_AES_EN_UMSK        (~(((1U << SF_CTRL_SF_AES_EN_LEN) - 1) << SF_CTRL_SF_AES_EN_POS))
#define SF_CTRL_SF_AES_MODE           SF_CTRL_SF_AES_MODE
#define SF_CTRL_SF_AES_MODE_POS       (1U)
#define SF_CTRL_SF_AES_MODE_LEN       (2U)
#define SF_CTRL_SF_AES_MODE_MSK       (((1U << SF_CTRL_SF_AES_MODE_LEN) - 1) << SF_CTRL_SF_AES_MODE_POS)
#define SF_CTRL_SF_AES_MODE_UMSK      (~(((1U << SF_CTRL_SF_AES_MODE_LEN) - 1) << SF_CTRL_SF_AES_MODE_POS))
#define SF_CTRL_SF_AES_PREF_TRIG      SF_CTRL_SF_AES_PREF_TRIG
#define SF_CTRL_SF_AES_PREF_TRIG_POS  (3U)
#define SF_CTRL_SF_AES_PREF_TRIG_LEN  (1U)
#define SF_CTRL_SF_AES_PREF_TRIG_MSK  (((1U << SF_CTRL_SF_AES_PREF_TRIG_LEN) - 1) << SF_CTRL_SF_AES_PREF_TRIG_POS)
#define SF_CTRL_SF_AES_PREF_TRIG_UMSK (~(((1U << SF_CTRL_SF_AES_PREF_TRIG_LEN) - 1) << SF_CTRL_SF_AES_PREF_TRIG_POS))
#define SF_CTRL_SF_AES_PREF_BUSY      SF_CTRL_SF_AES_PREF_BUSY
#define SF_CTRL_SF_AES_PREF_BUSY_POS  (4U)
#define SF_CTRL_SF_AES_PREF_BUSY_LEN  (1U)
#define SF_CTRL_SF_AES_PREF_BUSY_MSK  (((1U << SF_CTRL_SF_AES_PREF_BUSY_LEN) - 1) << SF_CTRL_SF_AES_PREF_BUSY_POS)
#define SF_CTRL_SF_AES_PREF_BUSY_UMSK (~(((1U << SF_CTRL_SF_AES_PREF_BUSY_LEN) - 1) << SF_CTRL_SF_AES_PREF_BUSY_POS))
#define SF_CTRL_SF_AES_STATUS         SF_CTRL_SF_AES_STATUS
#define SF_CTRL_SF_AES_STATUS_POS     (5U)
#define SF_CTRL_SF_AES_STATUS_LEN     (27U)
#define SF_CTRL_SF_AES_STATUS_MSK     (((1U << SF_CTRL_SF_AES_STATUS_LEN) - 1) << SF_CTRL_SF_AES_STATUS_POS)
#define SF_CTRL_SF_AES_STATUS_UMSK    (~(((1U << SF_CTRL_SF_AES_STATUS_LEN) - 1) << SF_CTRL_SF_AES_STATUS_POS))

/* 0x2C : sf_ahb2sif_status */
#define SF_CTRL_SF_AHB2SIF_STATUS_OFFSET (0x2C)
#define SF_CTRL_SF_AHB2SIF_STATUS        SF_CTRL_SF_AHB2SIF_STATUS
#define SF_CTRL_SF_AHB2SIF_STATUS_POS    (0U)
#define SF_CTRL_SF_AHB2SIF_STATUS_LEN    (32U)
#define SF_CTRL_SF_AHB2SIF_STATUS_MSK    (((1U << SF_CTRL_SF_AHB2SIF_STATUS_LEN) - 1) << SF_CTRL_SF_AHB2SIF_STATUS_POS)
#define SF_CTRL_SF_AHB2SIF_STATUS_UMSK   (~(((1U << SF_CTRL_SF_AHB2SIF_STATUS_LEN) - 1) << SF_CTRL_SF_AHB2SIF_STATUS_POS))

/* 0x30 : sf_if_io_dly_0 */
#define SF_CTRL_SF_IF_IO_DLY_0_OFFSET   (0x30)
#define SF_CTRL_SF_CS_DLY_SEL           SF_CTRL_SF_CS_DLY_SEL
#define SF_CTRL_SF_CS_DLY_SEL_POS       (0U)
#define SF_CTRL_SF_CS_DLY_SEL_LEN       (2U)
#define SF_CTRL_SF_CS_DLY_SEL_MSK       (((1U << SF_CTRL_SF_CS_DLY_SEL_LEN) - 1) << SF_CTRL_SF_CS_DLY_SEL_POS)
#define SF_CTRL_SF_CS_DLY_SEL_UMSK      (~(((1U << SF_CTRL_SF_CS_DLY_SEL_LEN) - 1) << SF_CTRL_SF_CS_DLY_SEL_POS))
#define SF_CTRL_SF_CS2_DLY_SEL          SF_CTRL_SF_CS2_DLY_SEL
#define SF_CTRL_SF_CS2_DLY_SEL_POS      (2U)
#define SF_CTRL_SF_CS2_DLY_SEL_LEN      (2U)
#define SF_CTRL_SF_CS2_DLY_SEL_MSK      (((1U << SF_CTRL_SF_CS2_DLY_SEL_LEN) - 1) << SF_CTRL_SF_CS2_DLY_SEL_POS)
#define SF_CTRL_SF_CS2_DLY_SEL_UMSK     (~(((1U << SF_CTRL_SF_CS2_DLY_SEL_LEN) - 1) << SF_CTRL_SF_CS2_DLY_SEL_POS))
#define SF_CTRL_SF_CLK_OUT_DLY_SEL      SF_CTRL_SF_CLK_OUT_DLY_SEL
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_POS  (8U)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_MSK  (((1U << SF_CTRL_SF_CLK_OUT_DLY_SEL_LEN) - 1) << SF_CTRL_SF_CLK_OUT_DLY_SEL_POS)
#define SF_CTRL_SF_CLK_OUT_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_CLK_OUT_DLY_SEL_LEN) - 1) << SF_CTRL_SF_CLK_OUT_DLY_SEL_POS))
#define SF_CTRL_SF_DQS_OE_DLY_SEL       SF_CTRL_SF_DQS_OE_DLY_SEL
#define SF_CTRL_SF_DQS_OE_DLY_SEL_POS   (26U)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_MSK   (((1U << SF_CTRL_SF_DQS_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_DQS_OE_DLY_SEL_POS)
#define SF_CTRL_SF_DQS_OE_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF_DQS_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_DQS_OE_DLY_SEL_POS))
#define SF_CTRL_SF_DQS_DI_DLY_SEL       SF_CTRL_SF_DQS_DI_DLY_SEL
#define SF_CTRL_SF_DQS_DI_DLY_SEL_POS   (28U)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_MSK   (((1U << SF_CTRL_SF_DQS_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_DQS_DI_DLY_SEL_POS)
#define SF_CTRL_SF_DQS_DI_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF_DQS_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_DQS_DI_DLY_SEL_POS))
#define SF_CTRL_SF_DQS_DO_DLY_SEL       SF_CTRL_SF_DQS_DO_DLY_SEL
#define SF_CTRL_SF_DQS_DO_DLY_SEL_POS   (30U)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_MSK   (((1U << SF_CTRL_SF_DQS_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_DQS_DO_DLY_SEL_POS)
#define SF_CTRL_SF_DQS_DO_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF_DQS_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_DQS_DO_DLY_SEL_POS))

/* 0x34 : sf_if_io_dly_1 */
#define SF_CTRL_SF_IF_IO_DLY_1_OFFSET   (0x34)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL      SF_CTRL_SF_IO_0_OE_DLY_SEL
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_0_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_0_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_0_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_0_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_0_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_0_DI_DLY_SEL      SF_CTRL_SF_IO_0_DI_DLY_SEL
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_0_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_0_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_0_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_0_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_0_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_0_DO_DLY_SEL      SF_CTRL_SF_IO_0_DO_DLY_SEL
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_0_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_0_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_0_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_0_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_0_DO_DLY_SEL_POS))

/* 0x38 : sf_if_io_dly_2 */
#define SF_CTRL_SF_IF_IO_DLY_2_OFFSET   (0x38)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL      SF_CTRL_SF_IO_1_OE_DLY_SEL
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_1_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_1_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_1_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_1_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_1_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_1_DI_DLY_SEL      SF_CTRL_SF_IO_1_DI_DLY_SEL
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_1_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_1_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_1_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_1_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_1_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_1_DO_DLY_SEL      SF_CTRL_SF_IO_1_DO_DLY_SEL
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_1_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_1_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_1_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_1_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_1_DO_DLY_SEL_POS))

/* 0x3C : sf_if_io_dly_3 */
#define SF_CTRL_SF_IF_IO_DLY_3_OFFSET   (0x3C)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL      SF_CTRL_SF_IO_2_OE_DLY_SEL
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_2_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_2_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_2_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_2_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_2_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_2_DI_DLY_SEL      SF_CTRL_SF_IO_2_DI_DLY_SEL
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_2_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_2_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_2_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_2_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_2_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_2_DO_DLY_SEL      SF_CTRL_SF_IO_2_DO_DLY_SEL
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_2_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_2_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_2_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_2_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_2_DO_DLY_SEL_POS))

/* 0x40 : sf_if_io_dly_4 */
#define SF_CTRL_SF_IF_IO_DLY_4_OFFSET   (0x40)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL      SF_CTRL_SF_IO_3_OE_DLY_SEL
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_3_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_3_OE_DLY_SEL_POS)
#define SF_CTRL_SF_IO_3_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_3_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_3_OE_DLY_SEL_POS))
#define SF_CTRL_SF_IO_3_DI_DLY_SEL      SF_CTRL_SF_IO_3_DI_DLY_SEL
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_3_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_3_DI_DLY_SEL_POS)
#define SF_CTRL_SF_IO_3_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_3_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_3_DI_DLY_SEL_POS))
#define SF_CTRL_SF_IO_3_DO_DLY_SEL      SF_CTRL_SF_IO_3_DO_DLY_SEL
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF_IO_3_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_3_DO_DLY_SEL_POS)
#define SF_CTRL_SF_IO_3_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF_IO_3_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF_IO_3_DO_DLY_SEL_POS))

/* 0x44 : sf_reserved */
#define SF_CTRL_SF_RESERVED_OFFSET (0x44)
#define SF_CTRL_SF_RESERVED        SF_CTRL_SF_RESERVED
#define SF_CTRL_SF_RESERVED_POS    (0U)
#define SF_CTRL_SF_RESERVED_LEN    (32U)
#define SF_CTRL_SF_RESERVED_MSK    (((1U << SF_CTRL_SF_RESERVED_LEN) - 1) << SF_CTRL_SF_RESERVED_POS)
#define SF_CTRL_SF_RESERVED_UMSK   (~(((1U << SF_CTRL_SF_RESERVED_LEN) - 1) << SF_CTRL_SF_RESERVED_POS))

/* 0x48 : sf2_if_io_dly_0 */
#define SF_CTRL_SF2_IF_IO_DLY_0_OFFSET   (0x48)
#define SF_CTRL_SF2_CS_DLY_SEL           SF_CTRL_SF2_CS_DLY_SEL
#define SF_CTRL_SF2_CS_DLY_SEL_POS       (0U)
#define SF_CTRL_SF2_CS_DLY_SEL_LEN       (2U)
#define SF_CTRL_SF2_CS_DLY_SEL_MSK       (((1U << SF_CTRL_SF2_CS_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_CS_DLY_SEL_POS)
#define SF_CTRL_SF2_CS_DLY_SEL_UMSK      (~(((1U << SF_CTRL_SF2_CS_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_CS_DLY_SEL_POS))
#define SF_CTRL_SF2_CS2_DLY_SEL          SF_CTRL_SF2_CS2_DLY_SEL
#define SF_CTRL_SF2_CS2_DLY_SEL_POS      (2U)
#define SF_CTRL_SF2_CS2_DLY_SEL_LEN      (2U)
#define SF_CTRL_SF2_CS2_DLY_SEL_MSK      (((1U << SF_CTRL_SF2_CS2_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_CS2_DLY_SEL_POS)
#define SF_CTRL_SF2_CS2_DLY_SEL_UMSK     (~(((1U << SF_CTRL_SF2_CS2_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_CS2_DLY_SEL_POS))
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL      SF_CTRL_SF2_CLK_OUT_DLY_SEL
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_POS  (8U)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_CLK_OUT_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_CLK_OUT_DLY_SEL_POS)
#define SF_CTRL_SF2_CLK_OUT_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_CLK_OUT_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_CLK_OUT_DLY_SEL_POS))
#define SF_CTRL_SF2_DQS_OE_DLY_SEL       SF_CTRL_SF2_DQS_OE_DLY_SEL
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_POS   (26U)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_MSK   (((1U << SF_CTRL_SF2_DQS_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_DQS_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_DQS_OE_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF2_DQS_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_DQS_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_DQS_DI_DLY_SEL       SF_CTRL_SF2_DQS_DI_DLY_SEL
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_POS   (28U)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_MSK   (((1U << SF_CTRL_SF2_DQS_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_DQS_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_DQS_DI_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF2_DQS_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_DQS_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_DQS_DO_DLY_SEL       SF_CTRL_SF2_DQS_DO_DLY_SEL
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_POS   (30U)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_MSK   (((1U << SF_CTRL_SF2_DQS_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_DQS_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_DQS_DO_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF2_DQS_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_DQS_DO_DLY_SEL_POS))

/* 0x4C : sf2_if_io_dly_1 */
#define SF_CTRL_SF2_IF_IO_DLY_1_OFFSET   (0x4C)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL      SF_CTRL_SF2_IO_0_OE_DLY_SEL
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_0_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_0_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_0_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_0_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_0_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL      SF_CTRL_SF2_IO_0_DI_DLY_SEL
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_0_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_0_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_0_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_0_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_0_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL      SF_CTRL_SF2_IO_0_DO_DLY_SEL
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_0_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_0_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_0_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_0_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_0_DO_DLY_SEL_POS))

/* 0x50 : sf2_if_io_dly_2 */
#define SF_CTRL_SF2_IF_IO_DLY_2_OFFSET   (0x50)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL      SF_CTRL_SF2_IO_1_OE_DLY_SEL
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_1_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_1_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_1_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_1_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_1_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL      SF_CTRL_SF2_IO_1_DI_DLY_SEL
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_1_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_1_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_1_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_1_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_1_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL      SF_CTRL_SF2_IO_1_DO_DLY_SEL
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_1_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_1_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_1_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_1_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_1_DO_DLY_SEL_POS))

/* 0x54 : sf2_if_io_dly_3 */
#define SF_CTRL_SF2_IF_IO_DLY_3_OFFSET   (0x54)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL      SF_CTRL_SF2_IO_2_OE_DLY_SEL
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_2_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_2_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_2_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_2_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_2_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL      SF_CTRL_SF2_IO_2_DI_DLY_SEL
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_2_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_2_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_2_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_2_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_2_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL      SF_CTRL_SF2_IO_2_DO_DLY_SEL
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_2_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_2_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_2_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_2_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_2_DO_DLY_SEL_POS))

/* 0x58 : sf2_if_io_dly_4 */
#define SF_CTRL_SF2_IF_IO_DLY_4_OFFSET   (0x58)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL      SF_CTRL_SF2_IO_3_OE_DLY_SEL
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_3_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_3_OE_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_3_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_3_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_3_OE_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL      SF_CTRL_SF2_IO_3_DI_DLY_SEL
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_3_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_3_DI_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_3_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_3_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_3_DI_DLY_SEL_POS))
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL      SF_CTRL_SF2_IO_3_DO_DLY_SEL
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF2_IO_3_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_3_DO_DLY_SEL_POS)
#define SF_CTRL_SF2_IO_3_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF2_IO_3_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF2_IO_3_DO_DLY_SEL_POS))

/* 0x5C : sf3_if_io_dly_0 */
#define SF_CTRL_SF3_IF_IO_DLY_0_OFFSET   (0x5C)
#define SF_CTRL_SF3_CS_DLY_SEL           SF_CTRL_SF3_CS_DLY_SEL
#define SF_CTRL_SF3_CS_DLY_SEL_POS       (0U)
#define SF_CTRL_SF3_CS_DLY_SEL_LEN       (2U)
#define SF_CTRL_SF3_CS_DLY_SEL_MSK       (((1U << SF_CTRL_SF3_CS_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_CS_DLY_SEL_POS)
#define SF_CTRL_SF3_CS_DLY_SEL_UMSK      (~(((1U << SF_CTRL_SF3_CS_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_CS_DLY_SEL_POS))
#define SF_CTRL_SF3_CS2_DLY_SEL          SF_CTRL_SF3_CS2_DLY_SEL
#define SF_CTRL_SF3_CS2_DLY_SEL_POS      (2U)
#define SF_CTRL_SF3_CS2_DLY_SEL_LEN      (2U)
#define SF_CTRL_SF3_CS2_DLY_SEL_MSK      (((1U << SF_CTRL_SF3_CS2_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_CS2_DLY_SEL_POS)
#define SF_CTRL_SF3_CS2_DLY_SEL_UMSK     (~(((1U << SF_CTRL_SF3_CS2_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_CS2_DLY_SEL_POS))
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL      SF_CTRL_SF3_CLK_OUT_DLY_SEL
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_POS  (8U)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_CLK_OUT_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_CLK_OUT_DLY_SEL_POS)
#define SF_CTRL_SF3_CLK_OUT_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_CLK_OUT_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_CLK_OUT_DLY_SEL_POS))
#define SF_CTRL_SF3_DQS_OE_DLY_SEL       SF_CTRL_SF3_DQS_OE_DLY_SEL
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_POS   (26U)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_MSK   (((1U << SF_CTRL_SF3_DQS_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_DQS_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_DQS_OE_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF3_DQS_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_DQS_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_DQS_DI_DLY_SEL       SF_CTRL_SF3_DQS_DI_DLY_SEL
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_POS   (28U)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_MSK   (((1U << SF_CTRL_SF3_DQS_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_DQS_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_DQS_DI_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF3_DQS_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_DQS_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_DQS_DO_DLY_SEL       SF_CTRL_SF3_DQS_DO_DLY_SEL
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_POS   (30U)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_LEN   (2U)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_MSK   (((1U << SF_CTRL_SF3_DQS_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_DQS_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_DQS_DO_DLY_SEL_UMSK  (~(((1U << SF_CTRL_SF3_DQS_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_DQS_DO_DLY_SEL_POS))

/* 0x60 : sf3_if_io_dly_1 */
#define SF_CTRL_SF3_IF_IO_DLY_1_OFFSET   (0x60)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL      SF_CTRL_SF3_IO_0_OE_DLY_SEL
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_0_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_0_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_0_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_0_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_0_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL      SF_CTRL_SF3_IO_0_DI_DLY_SEL
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_0_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_0_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_0_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_0_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_0_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL      SF_CTRL_SF3_IO_0_DO_DLY_SEL
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_0_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_0_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_0_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_0_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_0_DO_DLY_SEL_POS))

/* 0x64 : sf3_if_io_dly_2 */
#define SF_CTRL_SF3_IF_IO_DLY_2_OFFSET   (0x64)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL      SF_CTRL_SF3_IO_1_OE_DLY_SEL
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_1_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_1_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_1_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_1_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_1_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL      SF_CTRL_SF3_IO_1_DI_DLY_SEL
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_1_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_1_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_1_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_1_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_1_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL      SF_CTRL_SF3_IO_1_DO_DLY_SEL
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_1_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_1_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_1_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_1_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_1_DO_DLY_SEL_POS))

/* 0x68 : sf3_if_io_dly_3 */
#define SF_CTRL_SF3_IF_IO_DLY_3_OFFSET   (0x68)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL      SF_CTRL_SF3_IO_2_OE_DLY_SEL
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_2_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_2_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_2_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_2_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_2_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL      SF_CTRL_SF3_IO_2_DI_DLY_SEL
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_2_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_2_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_2_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_2_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_2_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL      SF_CTRL_SF3_IO_2_DO_DLY_SEL
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_2_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_2_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_2_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_2_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_2_DO_DLY_SEL_POS))

/* 0x6C : sf3_if_io_dly_4 */
#define SF_CTRL_SF3_IF_IO_DLY_4_OFFSET   (0x6C)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL      SF_CTRL_SF3_IO_3_OE_DLY_SEL
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_POS  (0U)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_3_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_3_OE_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_3_OE_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_3_OE_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_3_OE_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL      SF_CTRL_SF3_IO_3_DI_DLY_SEL
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_POS  (8U)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_3_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_3_DI_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_3_DI_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_3_DI_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_3_DI_DLY_SEL_POS))
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL      SF_CTRL_SF3_IO_3_DO_DLY_SEL
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_POS  (16U)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_LEN  (2U)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_MSK  (((1U << SF_CTRL_SF3_IO_3_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_3_DO_DLY_SEL_POS)
#define SF_CTRL_SF3_IO_3_DO_DLY_SEL_UMSK (~(((1U << SF_CTRL_SF3_IO_3_DO_DLY_SEL_LEN) - 1) << SF_CTRL_SF3_IO_3_DO_DLY_SEL_POS))

/* 0x70 : sf_ctrl_2 */
#define SF_CTRL_2_OFFSET                (0x70)
#define SF_CTRL_SF_IF_PAD_SEL           SF_CTRL_SF_IF_PAD_SEL
#define SF_CTRL_SF_IF_PAD_SEL_POS       (0U)
#define SF_CTRL_SF_IF_PAD_SEL_LEN       (2U)
#define SF_CTRL_SF_IF_PAD_SEL_MSK       (((1U << SF_CTRL_SF_IF_PAD_SEL_LEN) - 1) << SF_CTRL_SF_IF_PAD_SEL_POS)
#define SF_CTRL_SF_IF_PAD_SEL_UMSK      (~(((1U << SF_CTRL_SF_IF_PAD_SEL_LEN) - 1) << SF_CTRL_SF_IF_PAD_SEL_POS))
#define SF_CTRL_SF_IF_PAD_SEL_LOCK      SF_CTRL_SF_IF_PAD_SEL_LOCK
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_POS  (3U)
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_LEN  (1U)
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_MSK  (((1U << SF_CTRL_SF_IF_PAD_SEL_LOCK_LEN) - 1) << SF_CTRL_SF_IF_PAD_SEL_LOCK_POS)
#define SF_CTRL_SF_IF_PAD_SEL_LOCK_UMSK (~(((1U << SF_CTRL_SF_IF_PAD_SEL_LOCK_LEN) - 1) << SF_CTRL_SF_IF_PAD_SEL_LOCK_POS))
#define SF_CTRL_SF_IF_DTR_EN            SF_CTRL_SF_IF_DTR_EN
#define SF_CTRL_SF_IF_DTR_EN_POS        (4U)
#define SF_CTRL_SF_IF_DTR_EN_LEN        (1U)
#define SF_CTRL_SF_IF_DTR_EN_MSK        (((1U << SF_CTRL_SF_IF_DTR_EN_LEN) - 1) << SF_CTRL_SF_IF_DTR_EN_POS)
#define SF_CTRL_SF_IF_DTR_EN_UMSK       (~(((1U << SF_CTRL_SF_IF_DTR_EN_LEN) - 1) << SF_CTRL_SF_IF_DTR_EN_POS))
#define SF_CTRL_SF_IF_DQS_EN            SF_CTRL_SF_IF_DQS_EN
#define SF_CTRL_SF_IF_DQS_EN_POS        (5U)
#define SF_CTRL_SF_IF_DQS_EN_LEN        (1U)
#define SF_CTRL_SF_IF_DQS_EN_MSK        (((1U << SF_CTRL_SF_IF_DQS_EN_LEN) - 1) << SF_CTRL_SF_IF_DQS_EN_POS)
#define SF_CTRL_SF_IF_DQS_EN_UMSK       (~(((1U << SF_CTRL_SF_IF_DQS_EN_LEN) - 1) << SF_CTRL_SF_IF_DQS_EN_POS))
#define SF_CTRL_SF_IF_BK_SWAP           SF_CTRL_SF_IF_BK_SWAP
#define SF_CTRL_SF_IF_BK_SWAP_POS       (28U)
#define SF_CTRL_SF_IF_BK_SWAP_LEN       (1U)
#define SF_CTRL_SF_IF_BK_SWAP_MSK       (((1U << SF_CTRL_SF_IF_BK_SWAP_LEN) - 1) << SF_CTRL_SF_IF_BK_SWAP_POS)
#define SF_CTRL_SF_IF_BK_SWAP_UMSK      (~(((1U << SF_CTRL_SF_IF_BK_SWAP_LEN) - 1) << SF_CTRL_SF_IF_BK_SWAP_POS))
#define SF_CTRL_SF_IF_BK2_MODE          SF_CTRL_SF_IF_BK2_MODE
#define SF_CTRL_SF_IF_BK2_MODE_POS      (29U)
#define SF_CTRL_SF_IF_BK2_MODE_LEN      (1U)
#define SF_CTRL_SF_IF_BK2_MODE_MSK      (((1U << SF_CTRL_SF_IF_BK2_MODE_LEN) - 1) << SF_CTRL_SF_IF_BK2_MODE_POS)
#define SF_CTRL_SF_IF_BK2_MODE_UMSK     (~(((1U << SF_CTRL_SF_IF_BK2_MODE_LEN) - 1) << SF_CTRL_SF_IF_BK2_MODE_POS))
#define SF_CTRL_SF_IF_BK2_EN            SF_CTRL_SF_IF_BK2_EN
#define SF_CTRL_SF_IF_BK2_EN_POS        (30U)
#define SF_CTRL_SF_IF_BK2_EN_LEN        (1U)
#define SF_CTRL_SF_IF_BK2_EN_MSK        (((1U << SF_CTRL_SF_IF_BK2_EN_LEN) - 1) << SF_CTRL_SF_IF_BK2_EN_POS)
#define SF_CTRL_SF_IF_BK2_EN_UMSK       (~(((1U << SF_CTRL_SF_IF_BK2_EN_LEN) - 1) << SF_CTRL_SF_IF_BK2_EN_POS))
#define SF_CTRL_SF_IF_0_BK_SEL          SF_CTRL_SF_IF_0_BK_SEL
#define SF_CTRL_SF_IF_0_BK_SEL_POS      (31U)
#define SF_CTRL_SF_IF_0_BK_SEL_LEN      (1U)
#define SF_CTRL_SF_IF_0_BK_SEL_MSK      (((1U << SF_CTRL_SF_IF_0_BK_SEL_LEN) - 1) << SF_CTRL_SF_IF_0_BK_SEL_POS)
#define SF_CTRL_SF_IF_0_BK_SEL_UMSK     (~(((1U << SF_CTRL_SF_IF_0_BK_SEL_LEN) - 1) << SF_CTRL_SF_IF_0_BK_SEL_POS))

/* 0x74 : sf_ctrl_3 */
#define SF_CTRL_3_OFFSET                (0x74)
#define SF_CTRL_SF_CMDS_WRAP_LEN        SF_CTRL_SF_CMDS_WRAP_LEN
#define SF_CTRL_SF_CMDS_WRAP_LEN_POS    (0U)
#define SF_CTRL_SF_CMDS_WRAP_LEN_LEN    (4U)
#define SF_CTRL_SF_CMDS_WRAP_LEN_MSK    (((1U << SF_CTRL_SF_CMDS_WRAP_LEN_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_LEN_POS)
#define SF_CTRL_SF_CMDS_WRAP_LEN_UMSK   (~(((1U << SF_CTRL_SF_CMDS_WRAP_LEN_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_LEN_POS))
#define SF_CTRL_SF_CMDS_EN              SF_CTRL_SF_CMDS_EN
#define SF_CTRL_SF_CMDS_EN_POS          (4U)
#define SF_CTRL_SF_CMDS_EN_LEN          (1U)
#define SF_CTRL_SF_CMDS_EN_MSK          (((1U << SF_CTRL_SF_CMDS_EN_LEN) - 1) << SF_CTRL_SF_CMDS_EN_POS)
#define SF_CTRL_SF_CMDS_EN_UMSK         (~(((1U << SF_CTRL_SF_CMDS_EN_LEN) - 1) << SF_CTRL_SF_CMDS_EN_POS))
#define SF_CTRL_SF_CMDS_BT_DLY          SF_CTRL_SF_CMDS_BT_DLY
#define SF_CTRL_SF_CMDS_BT_DLY_POS      (5U)
#define SF_CTRL_SF_CMDS_BT_DLY_LEN      (3U)
#define SF_CTRL_SF_CMDS_BT_DLY_MSK      (((1U << SF_CTRL_SF_CMDS_BT_DLY_LEN) - 1) << SF_CTRL_SF_CMDS_BT_DLY_POS)
#define SF_CTRL_SF_CMDS_BT_DLY_UMSK     (~(((1U << SF_CTRL_SF_CMDS_BT_DLY_LEN) - 1) << SF_CTRL_SF_CMDS_BT_DLY_POS))
#define SF_CTRL_SF_CMDS_BT_EN           SF_CTRL_SF_CMDS_BT_EN
#define SF_CTRL_SF_CMDS_BT_EN_POS       (8U)
#define SF_CTRL_SF_CMDS_BT_EN_LEN       (1U)
#define SF_CTRL_SF_CMDS_BT_EN_MSK       (((1U << SF_CTRL_SF_CMDS_BT_EN_LEN) - 1) << SF_CTRL_SF_CMDS_BT_EN_POS)
#define SF_CTRL_SF_CMDS_BT_EN_UMSK      (~(((1U << SF_CTRL_SF_CMDS_BT_EN_LEN) - 1) << SF_CTRL_SF_CMDS_BT_EN_POS))
#define SF_CTRL_SF_CMDS_WRAP_Q_INI      SF_CTRL_SF_CMDS_WRAP_Q_INI
#define SF_CTRL_SF_CMDS_WRAP_Q_INI_POS  (9U)
#define SF_CTRL_SF_CMDS_WRAP_Q_INI_LEN  (1U)
#define SF_CTRL_SF_CMDS_WRAP_Q_INI_MSK  (((1U << SF_CTRL_SF_CMDS_WRAP_Q_INI_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_Q_INI_POS)
#define SF_CTRL_SF_CMDS_WRAP_Q_INI_UMSK (~(((1U << SF_CTRL_SF_CMDS_WRAP_Q_INI_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_Q_INI_POS))
#define SF_CTRL_SF_CMDS_WRAP_MODE       SF_CTRL_SF_CMDS_WRAP_MODE
#define SF_CTRL_SF_CMDS_WRAP_MODE_POS   (10U)
#define SF_CTRL_SF_CMDS_WRAP_MODE_LEN   (1U)
#define SF_CTRL_SF_CMDS_WRAP_MODE_MSK   (((1U << SF_CTRL_SF_CMDS_WRAP_MODE_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_MODE_POS)
#define SF_CTRL_SF_CMDS_WRAP_MODE_UMSK  (~(((1U << SF_CTRL_SF_CMDS_WRAP_MODE_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_MODE_POS))
#define SF_CTRL_SF_CMDS_WRAP_Q          SF_CTRL_SF_CMDS_WRAP_Q
#define SF_CTRL_SF_CMDS_WRAP_Q_POS      (11U)
#define SF_CTRL_SF_CMDS_WRAP_Q_LEN      (1U)
#define SF_CTRL_SF_CMDS_WRAP_Q_MSK      (((1U << SF_CTRL_SF_CMDS_WRAP_Q_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_Q_POS)
#define SF_CTRL_SF_CMDS_WRAP_Q_UMSK     (~(((1U << SF_CTRL_SF_CMDS_WRAP_Q_LEN) - 1) << SF_CTRL_SF_CMDS_WRAP_Q_POS))
#define SF_CTRL_SF_IF_1_ACK_LAT         SF_CTRL_SF_IF_1_ACK_LAT
#define SF_CTRL_SF_IF_1_ACK_LAT_POS     (29U)
#define SF_CTRL_SF_IF_1_ACK_LAT_LEN     (3U)
#define SF_CTRL_SF_IF_1_ACK_LAT_MSK     (((1U << SF_CTRL_SF_IF_1_ACK_LAT_LEN) - 1) << SF_CTRL_SF_IF_1_ACK_LAT_POS)
#define SF_CTRL_SF_IF_1_ACK_LAT_UMSK    (~(((1U << SF_CTRL_SF_IF_1_ACK_LAT_LEN) - 1) << SF_CTRL_SF_IF_1_ACK_LAT_POS))

/* 0x0 : l1c_config */
#define L1C_CONFIG_OFFSET            (0x0)
#define L1C_CACHEABLE                L1C_CACHEABLE
#define L1C_CACHEABLE_POS            (0U)
#define L1C_CACHEABLE_LEN            (1U)
#define L1C_CACHEABLE_MSK            (((1U << L1C_CACHEABLE_LEN) - 1) << L1C_CACHEABLE_POS)
#define L1C_CACHEABLE_UMSK           (~(((1U << L1C_CACHEABLE_LEN) - 1) << L1C_CACHEABLE_POS))
#define L1C_CNT_EN                   L1C_CNT_EN
#define L1C_CNT_EN_POS               (1U)
#define L1C_CNT_EN_LEN               (1U)
#define L1C_CNT_EN_MSK               (((1U << L1C_CNT_EN_LEN) - 1) << L1C_CNT_EN_POS)
#define L1C_CNT_EN_UMSK              (~(((1U << L1C_CNT_EN_LEN) - 1) << L1C_CNT_EN_POS))
#define L1C_INVALID_EN               L1C_INVALID_EN
#define L1C_INVALID_EN_POS           (2U)
#define L1C_INVALID_EN_LEN           (1U)
#define L1C_INVALID_EN_MSK           (((1U << L1C_INVALID_EN_LEN) - 1) << L1C_INVALID_EN_POS)
#define L1C_INVALID_EN_UMSK          (~(((1U << L1C_INVALID_EN_LEN) - 1) << L1C_INVALID_EN_POS))
#define L1C_INVALID_DONE             L1C_INVALID_DONE
#define L1C_INVALID_DONE_POS         (3U)
#define L1C_INVALID_DONE_LEN         (1U)
#define L1C_INVALID_DONE_MSK         (((1U << L1C_INVALID_DONE_LEN) - 1) << L1C_INVALID_DONE_POS)
#define L1C_INVALID_DONE_UMSK        (~(((1U << L1C_INVALID_DONE_LEN) - 1) << L1C_INVALID_DONE_POS))
#define L1C_WT_EN                    L1C_WT_EN
#define L1C_WT_EN_POS                (4U)
#define L1C_WT_EN_LEN                (1U)
#define L1C_WT_EN_MSK                (((1U << L1C_WT_EN_LEN) - 1) << L1C_WT_EN_POS)
#define L1C_WT_EN_UMSK               (~(((1U << L1C_WT_EN_LEN) - 1) << L1C_WT_EN_POS))
#define L1C_WB_EN                    L1C_WB_EN
#define L1C_WB_EN_POS                (5U)
#define L1C_WB_EN_LEN                (1U)
#define L1C_WB_EN_MSK                (((1U << L1C_WB_EN_LEN) - 1) << L1C_WB_EN_POS)
#define L1C_WB_EN_UMSK               (~(((1U << L1C_WB_EN_LEN) - 1) << L1C_WB_EN_POS))
#define L1C_WA_EN                    L1C_WA_EN
#define L1C_WA_EN_POS                (6U)
#define L1C_WA_EN_LEN                (1U)
#define L1C_WA_EN_MSK                (((1U << L1C_WA_EN_LEN) - 1) << L1C_WA_EN_POS)
#define L1C_WA_EN_UMSK               (~(((1U << L1C_WA_EN_LEN) - 1) << L1C_WA_EN_POS))
#define L1C_RANDOM_REPLACE           L1C_RANDOM_REPLACE
#define L1C_RANDOM_REPLACE_POS       (7U)
#define L1C_RANDOM_REPLACE_LEN       (1U)
#define L1C_RANDOM_REPLACE_MSK       (((1U << L1C_RANDOM_REPLACE_LEN) - 1) << L1C_RANDOM_REPLACE_POS)
#define L1C_RANDOM_REPLACE_UMSK      (~(((1U << L1C_RANDOM_REPLACE_LEN) - 1) << L1C_RANDOM_REPLACE_POS))
#define L1C_WAY_DIS                  L1C_WAY_DIS
#define L1C_WAY_DIS_POS              (8U)
#define L1C_WAY_DIS_LEN              (4U)
#define L1C_WAY_DIS_MSK              (((1U << L1C_WAY_DIS_LEN) - 1) << L1C_WAY_DIS_POS)
#define L1C_WAY_DIS_UMSK             (~(((1U << L1C_WAY_DIS_LEN) - 1) << L1C_WAY_DIS_POS))
#define L1C_IROM_2T_ACCESS           L1C_IROM_2T_ACCESS
#define L1C_IROM_2T_ACCESS_POS       (12U)
#define L1C_IROM_2T_ACCESS_LEN       (1U)
#define L1C_IROM_2T_ACCESS_MSK       (((1U << L1C_IROM_2T_ACCESS_LEN) - 1) << L1C_IROM_2T_ACCESS_POS)
#define L1C_IROM_2T_ACCESS_UMSK      (~(((1U << L1C_IROM_2T_ACCESS_LEN) - 1) << L1C_IROM_2T_ACCESS_POS))
#define L1C_BYPASS                   L1C_BYPASS
#define L1C_BYPASS_POS               (14U)
#define L1C_BYPASS_LEN               (1U)
#define L1C_BYPASS_MSK               (((1U << L1C_BYPASS_LEN) - 1) << L1C_BYPASS_POS)
#define L1C_BYPASS_UMSK              (~(((1U << L1C_BYPASS_LEN) - 1) << L1C_BYPASS_POS))
#define L1C_BMX_ERR_EN               L1C_BMX_ERR_EN
#define L1C_BMX_ERR_EN_POS           (15U)
#define L1C_BMX_ERR_EN_LEN           (1U)
#define L1C_BMX_ERR_EN_MSK           (((1U << L1C_BMX_ERR_EN_LEN) - 1) << L1C_BMX_ERR_EN_POS)
#define L1C_BMX_ERR_EN_UMSK          (~(((1U << L1C_BMX_ERR_EN_LEN) - 1) << L1C_BMX_ERR_EN_POS))
#define L1C_BMX_ARB_MODE             L1C_BMX_ARB_MODE
#define L1C_BMX_ARB_MODE_POS         (16U)
#define L1C_BMX_ARB_MODE_LEN         (2U)
#define L1C_BMX_ARB_MODE_MSK         (((1U << L1C_BMX_ARB_MODE_LEN) - 1) << L1C_BMX_ARB_MODE_POS)
#define L1C_BMX_ARB_MODE_UMSK        (~(((1U << L1C_BMX_ARB_MODE_LEN) - 1) << L1C_BMX_ARB_MODE_POS))
#define L1C_BMX_TIMEOUT_EN           L1C_BMX_TIMEOUT_EN
#define L1C_BMX_TIMEOUT_EN_POS       (20U)
#define L1C_BMX_TIMEOUT_EN_LEN       (4U)
#define L1C_BMX_TIMEOUT_EN_MSK       (((1U << L1C_BMX_TIMEOUT_EN_LEN) - 1) << L1C_BMX_TIMEOUT_EN_POS)
#define L1C_BMX_TIMEOUT_EN_UMSK      (~(((1U << L1C_BMX_TIMEOUT_EN_LEN) - 1) << L1C_BMX_TIMEOUT_EN_POS))
#define L1C_BMX_BUSY_OPTION_DIS      L1C_BMX_BUSY_OPTION_DIS
#define L1C_BMX_BUSY_OPTION_DIS_POS  (24U)
#define L1C_BMX_BUSY_OPTION_DIS_LEN  (1U)
#define L1C_BMX_BUSY_OPTION_DIS_MSK  (((1U << L1C_BMX_BUSY_OPTION_DIS_LEN) - 1) << L1C_BMX_BUSY_OPTION_DIS_POS)
#define L1C_BMX_BUSY_OPTION_DIS_UMSK (~(((1U << L1C_BMX_BUSY_OPTION_DIS_LEN) - 1) << L1C_BMX_BUSY_OPTION_DIS_POS))
#define L1C_EARLY_RESP_DIS           L1C_EARLY_RESP_DIS
#define L1C_EARLY_RESP_DIS_POS       (25U)
#define L1C_EARLY_RESP_DIS_LEN       (1U)
#define L1C_EARLY_RESP_DIS_MSK       (((1U << L1C_EARLY_RESP_DIS_LEN) - 1) << L1C_EARLY_RESP_DIS_POS)
#define L1C_EARLY_RESP_DIS_UMSK      (~(((1U << L1C_EARLY_RESP_DIS_LEN) - 1) << L1C_EARLY_RESP_DIS_POS))
#define L1C_WRAP_DIS                 L1C_WRAP_DIS
#define L1C_WRAP_DIS_POS             (26U)
#define L1C_WRAP_DIS_LEN             (1U)
#define L1C_WRAP_DIS_MSK             (((1U << L1C_WRAP_DIS_LEN) - 1) << L1C_WRAP_DIS_POS)
#define L1C_WRAP_DIS_UMSK            (~(((1U << L1C_WRAP_DIS_LEN) - 1) << L1C_WRAP_DIS_POS))
#define L1C_FLUSH_EN                 L1C_FLUSH_EN
#define L1C_FLUSH_EN_POS             (28U)
#define L1C_FLUSH_EN_LEN             (1U)
#define L1C_FLUSH_EN_MSK             (((1U << L1C_FLUSH_EN_LEN) - 1) << L1C_FLUSH_EN_POS)
#define L1C_FLUSH_EN_UMSK            (~(((1U << L1C_FLUSH_EN_LEN) - 1) << L1C_FLUSH_EN_POS))
#define L1C_FLUSH_DONE               L1C_FLUSH_DONE
#define L1C_FLUSH_DONE_POS           (29U)
#define L1C_FLUSH_DONE_LEN           (1U)
#define L1C_FLUSH_DONE_MSK           (((1U << L1C_FLUSH_DONE_LEN) - 1) << L1C_FLUSH_DONE_POS)
#define L1C_FLUSH_DONE_UMSK          (~(((1U << L1C_FLUSH_DONE_LEN) - 1) << L1C_FLUSH_DONE_POS))

/* 0x4 : hit_cnt_lsb */
#define L1C_HIT_CNT_LSB_OFFSET (0x4)
#define L1C_HIT_CNT_LSB        L1C_HIT_CNT_LSB
#define L1C_HIT_CNT_LSB_POS    (0U)
#define L1C_HIT_CNT_LSB_LEN    (32U)
#define L1C_HIT_CNT_LSB_MSK    (((1U << L1C_HIT_CNT_LSB_LEN) - 1) << L1C_HIT_CNT_LSB_POS)
#define L1C_HIT_CNT_LSB_UMSK   (~(((1U << L1C_HIT_CNT_LSB_LEN) - 1) << L1C_HIT_CNT_LSB_POS))

/* 0x8 : hit_cnt_msb */
#define L1C_HIT_CNT_MSB_OFFSET (0x8)
#define L1C_HIT_CNT_MSB        L1C_HIT_CNT_MSB
#define L1C_HIT_CNT_MSB_POS    (0U)
#define L1C_HIT_CNT_MSB_LEN    (32U)
#define L1C_HIT_CNT_MSB_MSK    (((1U << L1C_HIT_CNT_MSB_LEN) - 1) << L1C_HIT_CNT_MSB_POS)
#define L1C_HIT_CNT_MSB_UMSK   (~(((1U << L1C_HIT_CNT_MSB_LEN) - 1) << L1C_HIT_CNT_MSB_POS))

/* 0xC : miss_cnt */
#define L1C_MISS_CNT_OFFSET (0xC)
#define L1C_MISS_CNT        L1C_MISS_CNT
#define L1C_MISS_CNT_POS    (0U)
#define L1C_MISS_CNT_LEN    (32U)
#define L1C_MISS_CNT_MSK    (((1U << L1C_MISS_CNT_LEN) - 1) << L1C_MISS_CNT_POS)
#define L1C_MISS_CNT_UMSK   (~(((1U << L1C_MISS_CNT_LEN) - 1) << L1C_MISS_CNT_POS))

/* 0x10 : l1c_misc */
#define L1C_MISC_OFFSET (0x10)
#define L1C_FSM         L1C_FSM
#define L1C_FSM_POS     (28U)
#define L1C_FSM_LEN     (3U)
#define L1C_FSM_MSK     (((1U << L1C_FSM_LEN) - 1) << L1C_FSM_POS)
#define L1C_FSM_UMSK    (~(((1U << L1C_FSM_LEN) - 1) << L1C_FSM_POS))


void SF_Ctrl_Set_Owner(uintptr_t base, SF_Ctrl_Owner_Type owner);

struct __metal_driver_vtable_bl_sflash0 {
    const struct metal_sflash_vtable sflash;
};

struct __metal_driver_bl_sflash0;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_bl_sflash0)

struct __metal_driver_bl_sflash0 {
    const struct metal_sflash sflash;
};

#endif
