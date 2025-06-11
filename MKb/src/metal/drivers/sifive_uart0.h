/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__SIFIVE_UART0_H
#define METAL__DRIVERS__SIFIVE_UART0_H

#include <metal/clock.h>
#include <metal/compiler.h>
//#include <metal/drivers/riscv_plic0.h>
#include <metal/drivers/sifive_gpio0.h>
#include <metal/io.h>
#include <metal/uart.h>

/* BL defines */

#include <stdint.h>

/**
 * @brief Functional type definition
 */
typedef enum {
    DISABLE = 0,
    ENABLE = 1,
} BL_Fun_Type;

/** @defgroup  UART_Public_Types
 *  @{
 */

/**
 *  @brief UART parity type definition
 */
typedef enum {
    UART_PARITY_NONE, /*!< UART parity none define */
    UART_PARITY_ODD,  /*!< UART parity odd define */
    UART_PARITY_EVEN, /*!< UART parity even define */
} UART_Parity_Type;

/**
 *  @brief UART data bits type definiton
 */
typedef enum {
    UART_DATABITS_5, /*!< UART data bits length:5 bits */
    UART_DATABITS_6, /*!< UART data bits length:6 bits */
    UART_DATABITS_7, /*!< UART data bits length:7 bits */
    UART_DATABITS_8, /*!< UART data bits length:8 bits */
} UART_DataBits_Type;

/**
 *  @brief UART stop bits type definiton
 */
typedef enum {
    UART_STOPBITS_0_5, /*!< UART data stop bits length:0.5 bits */
    UART_STOPBITS_1,   /*!< UART data stop bits length:1 bits */
    UART_STOPBITS_1_5, /*!< UART data stop bits length:1.5 bits */
    UART_STOPBITS_2,   /*!< UART data stop bits length:2 bits */
} UART_StopBits_Type;

/**
 *  @brief UART each data byte is send out LSB-first or MSB-first type definiton
 */
typedef enum {
    UART_LSB_FIRST, /*!< UART each byte is send out LSB-first */
    UART_MSB_FIRST, /*!< UART each byte is send out MSB-first */
} UART_ByteBitInverse_Type;

/**
 *  @brief UART auto baudrate detection using codeword 0x55 or start bit definiton
 */
typedef enum {
    UART_AUTOBAUD_0X55,     /*!< UART auto baudrate detection using codeword 0x55 */
    UART_AUTOBAUD_STARTBIT, /*!< UART auto baudrate detection using start bit */
} UART_AutoBaudDetection_Type;

/**
 *  @brief UART interrupt type definition
 */
typedef enum {
    UART_INT_TX_END,      /*!< UART tx transfer end interrupt */
    UART_INT_RX_END,      /*!< UART rx transfer end interrupt */
    UART_INT_TX_FIFO_REQ, /*!< UART tx fifo interrupt when tx fifo count reaches,auto clear */
    UART_INT_RX_FIFO_REQ, /*!< UART rx fifo interrupt when rx fifo count reaches,auto clear */
    UART_INT_RTO,         /*!< UART rx time-out interrupt */
    UART_INT_PCE,         /*!< UART rx parity check error interrupt */
    UART_INT_TX_FER,      /*!< UART tx fifo overflow/underflow error interrupt */
    UART_INT_RX_FER,      /*!< UART rx fifo overflow/underflow error interrupt */
    UART_INT_LSE,         /*!< UART rx lin mode sync field error interrupt */
    UART_INT_ALL,         /*!< All the interrupt */
} UART_INT_Type;

/**
 *  @brief UART overflow or underflow type definition
 */
typedef enum {
    UART_TX_OVERFLOW,  /*!< UART tx fifo overflow */
    UART_TX_UNDERFLOW, /*!< UART tx fifo underflow */
    UART_RX_OVERFLOW,  /*!< UART rx fifo overflow */
    UART_RX_UNDERFLOW, /*!< UART rx fifo underflow */
} UART_Overflow_Type;

/**
 *  @brief UART configuration structure type definition
 */
typedef struct
{
    uint32_t uartClk;                        /*!< Uart module clock */
    uint32_t baudRate;                       /*!< Uart baudrate */
    UART_DataBits_Type dataBits;             /*!< Uart frame length of data bit */
    UART_StopBits_Type stopBits;             /*!< Uart frame length of stop bit */
    UART_Parity_Type parity;                 /*!< Uart parity check type */
    BL_Fun_Type ctsFlowControl;              /*!< Enable or disable tx CTS flow control */
    BL_Fun_Type rxDeglitch;                  /*!< Enable or disable rx input de-glitch function */
    BL_Fun_Type rtsSoftwareControl;          /*!< Enable or disable rx RTS output SW control mode */
    BL_Fun_Type txSoftwareControl;           /*!< Enable or disable tx output SW control mode */
    BL_Fun_Type txLinMode;                   /*!< Enable or disable tx LIN mode,LIN header will be sent before sending data */
    BL_Fun_Type rxLinMode;                   /*!< Enable or disable rx LIN mode,LIN header will be required and checked before receiving data */
    uint8_t txBreakBitCnt;                   /*!< Uart tx break bit count,additional 8 bit times will be added since LIN break field requires at
                                                 least 13 bit times */
    UART_ByteBitInverse_Type byteBitInverse; /*!< Uart each data byte is send out LSB-first or MSB-first */
} UART_CFG_Type;

/**
 *  @brief UART FIFO configuration structure type definition
 */
typedef struct
{
    uint8_t txFifoDmaThreshold;  /*!< TX FIFO threshold, dma tx request will not be asserted if tx fifo count is less than this value */
    uint8_t rxFifoDmaThreshold;  /*!< RX FIFO threshold, dma rx request will not be asserted if rx fifo count is less than this value */
    BL_Fun_Type txFifoDmaEnable; /*!< Enable or disable tx dma req/ack interface */
    BL_Fun_Type rxFifoDmaEnable; /*!< Enable or disable rx dma req/ack interface */
} UART_FifoCfg_Type;

/**
 *  @brief UART infrared configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type txIrEnable;  /*!< Enable or disable uart tx ir mode */
    BL_Fun_Type rxIrEnable;  /*!< Enable or disable uart rx ir mode */
    BL_Fun_Type txIrInverse; /*!< Enable or disable inverse signal of uart tx output in ir mode */
    BL_Fun_Type rxIrInverse; /*!< Enable or disable inverse signal of uart rx input in ir mode */
    uint16_t txIrPulseStart; /*!< Set start position of uart tx ir pulse */
    uint16_t txIrPulseStop;  /*!< Set stop position of uart tx ir pulse */
    uint16_t rxIrPulseStart; /*!< Set start position of uart rx pulse recovered from ir signal */
} UART_IrCfg_Type;

/*@} end of group UART_Public_Types */

/** @defgroup  UART_Public_Macros
 *  @{
 */
#define UART_RX_FIFO_SIZE         128
#define UART_TX_FIFO_SIZE         128
#define UART_DEFAULT_RECV_TIMEOUT 80

/*@} end of group UART_Public_Macros */

// bl702_driver/hal_drv/default_config/uart_config.h
#define UART_CLOCK_SOURCE_96M_ENABLE (1)
#define UART_CTS_FLOWCONTROL_ENABLE  (0)
#define UART_RTS_FLOWCONTROL_ENABLE  (0)
#define UART_RX_DEGLITCH_ENABLE      (0)
#define UART_MSB_FIRST_ENABLE        (0)
#define UART_TX_SWCONTROL_ENABLE     (0)
#define UART_TX_LINMODE_ENABLE       (0)
#define UART_RX_LINMODE_ENABLE       (0)
#define UART_TX_BREAKBIT_CNT         (0)

#define UART_FIFO_MAX_LEN        128
#define UART_DEFAULT_RTO_TIMEOUT 100

/* end BL defines */

struct __metal_driver_vtable_sifive_uart0 {
    const struct metal_uart_vtable uart;
};

struct __metal_driver_sifive_uart0;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_sifive_uart0)

struct __metal_driver_sifive_uart0 {
    struct metal_uart uart;
    unsigned long baud_rate;
    //metal_clock_callback pre_rate_change_callback;
    //metal_clock_callback post_rate_change_callback;
};


#endif
