#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdio.h>

// Base address of GPIO controller
#define GPIO_BASE               0x20005000UL

// Configuration registers for GPIO10–19 (each configures 2 GPIOs)
#define GPIO_CFGCTL5_REG        0x114  // GPIO10, 11
#define GPIO_CFGCTL6_REG        0x118  // GPIO12, 13
#define GPIO_CFGCTL7_REG        0x11C  // GPIO14, 15
#define GPIO_CFGCTL8_REG        0x120  // GPIO16, 17
#define GPIO_CFGCTL9_REG        0x124  // GPIO18, 19

// Value and enable registers
#define GPIO_INPUT_VAL_REG      0x180  // Input value register
#define GPIO_OUTPUT_VAL_REG     0x188  // Output value register
#define GPIO_OUTPUT_EN_REG      0x190  // Output enable register

// Register access macro
#define GPIO_REG(offset)        (*(volatile uint32_t *)(GPIO_BASE + (offset)))

// GPIO debug test pins
#define PIN_12                  12
#define PIN_13                  13
#define PIN_14                  14

#ifdef __cplusplus
extern "C" {
#endif

// Function prototypes

/**
 * @brief Enable a GPIO pin as output (only for pins 0–19).
 * 
 * @param pin GPIO pin number
 */
void gpio_enable_output(int pin);

/**
 * @brief Enable GPIO10–19 pins as inputs and disable their output enable.
 * 
 * @param pin Ignored (full range enabled inside)
 */
void gpio_enable_input(int pin);

/**
 * @brief Set the output level of a GPIO pin (if output already enabled).
 * 
 * @param pin GPIO pin number (0–31)
 * @param value 0 or 1
 */
void gpio_set_pin(int pin, int value);

/**
 * @brief Get the value of a GPIO input pin.
 * 
 * @param pin GPIO pin number
 * @return int 0 or 1 if input is enabled, -1 if not
 */
int gpio_get_input_pin(int pin);

/**
 * @brief Disable input configuration for GPIO10–19.
 */
void disable_input(void);

/**
 * @brief Disable output enable for GPIO10–19.
 */
void disable_output(void);

/**
 * @brief Set debug value on GPIO12–14 using 3-bit `state`.
 * 
 * @param state 3-bit value (bits [2:0] go to GPIO12, 13, 14)
 */
void debug_gpio_set(uint8_t state);

#ifdef __cplusplus
}
#endif

#endif // GPIO_H

