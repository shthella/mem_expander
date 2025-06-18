#include <stdio.h>
#include <stdint.h>
#include "gpio.h"

// Function prototypes
void gpio_enable_output(int pin);//to write to gpio 
void gpio_enable_input(int pin );//to read from gpio 
int gpio_get_input_pin(int pin); //read input pin vale 
void gpio_set_pin(int pin, int value); //write a value to input pin 
void disable_input(); //disable input 
void disable_output(); //disable output 
void debug_gpio_set(uint8_t state); //debug 3 gpio pins 

// Enable input on GPIO10–19
void gpio_enable_input(int pin) {
    uint32_t val;

    // GPIO10 & 11
    val = GPIO_REG(GPIO_CFGCTL5_REG);
    val &= ~((0x1FFF << 0) | (0x1FFF << 16)); //clear the enable input bit value 
    val |= ((1 << 0) << 0) | ((1 << 0) << 16); //set input enable bit (0 ,16 th bit)
    GPIO_REG(GPIO_CFGCTL5_REG) = val;

    // GPIO12 & 13
    val = GPIO_REG(GPIO_CFGCTL6_REG);
    val &= ~((0x1FFF << 0) | (0x1FFF << 16));
    val |= ((1 << 0) << 0) | ((1 << 0) << 16);
    GPIO_REG(GPIO_CFGCTL6_REG) = val;

    // GPIO14 & 15
    val = GPIO_REG(GPIO_CFGCTL7_REG);
    val &= ~((0x1FFF << 0) | (0x1FFF << 16));
    val |= ((1 << 0) << 0) | ((1 << 0) << 16);
    GPIO_REG(GPIO_CFGCTL7_REG) = val;

    // GPIO16 & 17
    val = GPIO_REG(GPIO_CFGCTL8_REG);
    val &= ~((0x1FFF << 0) | (0x1FFF << 16));
    val |= ((1 << 0) << 0) | ((1 << 0) << 16);
    GPIO_REG(GPIO_CFGCTL8_REG) = val;

    // GPIO18 & 19
    val = GPIO_REG(GPIO_CFGCTL9_REG);
    val &= ~((0x1FFF << 0) | (0x1FFF << 16));
    val |= ((1 << 0) << 0) | ((1 << 0) << 16);
    GPIO_REG(GPIO_CFGCTL9_REG) = val;

    // Clear output enable bits for GPIO10–19
    GPIO_REG(GPIO_OUTPUT_EN_REG) &= ~(
        (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14) |
        (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18) | (1 << 19)
    );
}

// Enable output on a single GPIO pin (0–19)
void gpio_enable_output(int pin) {
    if (pin < 0 || pin > 19) {
        printf("Invalid GPIO pin: %d\n", pin);
        return;
    }
    GPIO_REG(GPIO_OUTPUT_EN_REG) |= (1 << pin);
}

// Set GPIO output value
void gpio_set_pin(int pin, int value) {
    if (pin < 0 || pin > 31) {
        printf("Invalid GPIO pin: %d\n", pin);
        return;
    }

    // Check if output is already enabled
    if ((GPIO_REG(GPIO_OUTPUT_EN_REG) & (1 << pin)) == 0) {
        printf("Enabling output for GPIO%d\n", pin);
	return;
    }

    if (value)
        GPIO_REG(GPIO_OUTPUT_VAL_REG) |= (1 << pin);
    else
        GPIO_REG(GPIO_OUTPUT_VAL_REG) &= ~(1 << pin);
}

// Read GPIO input value
int gpio_get_input_pin(int pin) {
    if (pin < 0 || pin > 31) {
        printf("Invalid GPIO pin: %d\n", pin);
        return -1;
    }

    if (pin >= 10 && pin <= 19) {
        int reg_offset = GPIO_CFGCTL5_REG + ((pin - 10) / 2) * 4;//to check the registe offset that which pin is used (10-19) 
        uint32_t val = GPIO_REG(reg_offset);
        int shift = (pin % 2 == 0) ? 0 : 16; //even as 0th bit ,od as 16 th bit to enable input

        if (((val >> shift) & 0x1) == 0) {
            printf("Enabling input for GPIO%d\n", pin);
 	    return -1;
        }
    }

    return (GPIO_REG(GPIO_INPUT_VAL_REG) >> pin) & 0x1;
}

// Disable input on GPIO10–19
void disable_input() {
    uint32_t val;

    val = GPIO_REG(GPIO_CFGCTL5_REG);
    val &= ~((1 << 0) | (1 << 16));
    GPIO_REG(GPIO_CFGCTL5_REG) = val;

    val = GPIO_REG(GPIO_CFGCTL6_REG);
    val &= ~((1 << 0) | (1 << 16));
    GPIO_REG(GPIO_CFGCTL6_REG) = val;

    val = GPIO_REG(GPIO_CFGCTL7_REG);
    val &= ~((1 << 0) | (1 << 16));
    GPIO_REG(GPIO_CFGCTL7_REG) = val;

    val = GPIO_REG(GPIO_CFGCTL8_REG);
    val &= ~((1 << 0) | (1 << 16));
    GPIO_REG(GPIO_CFGCTL8_REG) = val;

    val = GPIO_REG(GPIO_CFGCTL9_REG);
    val &= ~((1 << 0) | (1 << 16));
    GPIO_REG(GPIO_CFGCTL9_REG) = val;
}

// Disable output on GPIO10–19
void disable_output() {
    GPIO_REG(GPIO_OUTPUT_EN_REG) &= ~(
        (1 << 10) | (1 << 11) | (1 << 12) | (1 << 13) | (1 << 14) |
        (1 << 15) | (1 << 16) | (1 << 17) | (1 << 18) | (1 << 19)
    );
}



