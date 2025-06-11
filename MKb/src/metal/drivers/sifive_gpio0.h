/* Copyright 2018 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#ifndef METAL__DRIVERS__SIFIVE_GPIO0_H
#define METAL__DRIVERS__SIFIVE_GPIO0_H

#include <metal/compiler.h>
#include <metal/gpio.h>

typedef enum {
    UART_RTS,
    UART_CTS,
    UART_TXD,
    UART_RXD,
    SPI_MOSI,
    SPI_MOSO,
    SPI_SS_O,
    SPI_CLK,
    I2C_SCL,
    I2C_SDA,
} GPIO_PIN;


struct __metal_driver_vtable_sifive_gpio0 {
    const struct __metal_gpio_vtable gpio;
};

// struct __metal_driver_sifive_gpio0;

__METAL_DECLARE_VTABLE(__metal_driver_vtable_sifive_gpio0)

struct __metal_driver_sifive_gpio0 {
    struct metal_gpio gpio;
};

#endif
