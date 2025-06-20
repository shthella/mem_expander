#include <stdio.h>
#include <stdint.h>
#include "gpio.h"

// Function prototypes
void gpio_enable_output(int pin);//to write to gpio 
void gpio_enable_input(int pin );//to read from gpio 
int gpio_get(int pin); //read input pin vale 
void gpio_set(int pin, int value); //write a value to input pin 
uint8_t debug_gpio_set(uint8_t state); //debug 3 gpio pins 
uint32_t gpio_read(uint32_t offset);
void gpio_write(uint32_t offset, uint32_t value);

// Enable input on GPIO10–19
void gpio_enable_input(int pin) {
    if (pin < 10 || pin > 19) {
        printf("Invalid GPIO input pin: %d\n", pin);
        return;
    }

    int reg_offset = GPIO_CFGCTL5_REG + ((pin - 10) / 2) * 4;
    int shift = (pin % 2 == 0) ? 0 : 16;

    // Set input enable bit (bit 0 of 13-bit field)
    uint32_t val = gpio_read(reg_offset);
    val &= ~(0x1FFF << shift);      //clear the bits 
    val |= (1 << shift);            // Set input enable
    gpio_write(reg_offset, val);

    // Clear output enable for this pin
    val = gpio_read(GPIO_OUTPUT_EN_REG);
    val &= ~(1 << pin);
    gpio_write(GPIO_OUTPUT_EN_REG, val);
}

// Enable output on a single GPIO pin (0–19)
void gpio_enable_output(int pin) {
    if (pin < 0 || pin > 19) {
        printf("Invalid GPIO pin: %d\n", pin);
        return;
    }
    uint32_t val = gpio_read(GPIO_OUTPUT_EN_REG);
    val |= (1 << pin);
    gpio_write(GPIO_OUTPUT_EN_REG, val);
}

// Set GPIO output value
void gpio_set(int pin, int value) {
    if (pin < 0 || pin > 31) {
        printf("Invalid GPIO pin: %d\n", pin);
        return;
    }

    // Check if output is already enabled
    if ((gpio_read(GPIO_OUTPUT_EN_REG) & (1 << pin)) == 0) {
        printf("Enabling output for GPIO%d\n", pin);
	return;
    }

    uint32_t val = gpio_read(GPIO_OUTPUT_VAL_REG);
    if (value)
        val |= (1 << pin);
    else
        val &= ~(1 << pin);
    gpio_write(GPIO_OUTPUT_VAL_REG, val);
}

// Read GPIO input value
int gpio_get(int pin) {
    if (pin < 0 || pin > 31) {
        printf("Invalid GPIO pin: %d\n", pin);
        return -1;
    }

    if (pin >= 10 && pin <= 19) {
        int reg_offset = GPIO_CFGCTL5_REG + ((pin - 10) / 2) * 4;//to check the registe offset that which pin is used (10-19) 
        uint32_t val = gpio_read(reg_offset);
        int shift = (pin % 2 == 0) ? 0 : 16; //even as 0th bit ,od as 16 th bit to enable input

        if (((val >> shift) & 0x1) == 0) {
            printf("Enabling input for GPIO%d\n", pin);
            return -1;
        }
    }

    return (gpio_read(GPIO_INPUT_VAL_REG) >> pin) & 0x1;
}
//Write to GPIO register via jtag  
void gpio_write(uint32_t offset, uint32_t value) {
    uint32_t addr = GPIO_BASE + offset;
    printf("GPIO WRITE: Address = 0x%08X, Value = 0x%08X\n", addr, value);
    jtag_register_write(addr, value);
}

// Read from GPIO register 
uint32_t gpio_read(uint32_t offset) {
    uint32_t addr = GPIO_BASE + offset;
    printf("GPIO READ: Address = 0x%08X\n", addr);
    jtag_register_read(addr); 
    return 0;
}
