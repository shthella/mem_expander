#include <stdio.h>
#include <unistd.h>
#include"uart.h"

#define UART_BASE       0xE0001000
#define UART_CR         (*(volatile unsigned int *)(UART_BASE + 0x00))
#define UART_MR         (*(volatile unsigned int *)(UART_BASE + 0x04))
#define UART_BAUDGEN    (*(volatile unsigned int *)(UART_BASE + 0x18))
#define UART_BAUDDIV    (*(volatile unsigned int *)(UART_BASE + 0x34))
#define UART_SR         (*(volatile unsigned int *)(UART_BASE + 0x2C))
#define UART_FIFO       (*(volatile unsigned int *)(UART_BASE + 0x30))

#define UART_SR_TXFULL  (1 << 4)


void uart_init() {
    UART_CR = 0x00;                      // Disable TX & RX
    UART_CR = (1 << 4) | (1 << 2);       // Reset RX & TX
    UART_MR = 0x20;                      // 8-bit data, no parity
    UART_BAUDGEN = 0x7C;                 // Baud generator value
    UART_BAUDDIV = 6;                    // Baud divisor
    UART_CR = (1 << 4) | (1 << 2) |      // Reset RX & TX
              (1 << 0) | (1 << 1);       // Enable RX & TX
}


void uart_putc(char c) {
    while (UART_SR & UART_SR_TXFULL);   // Wait until TX not full
    UART_FIFO = c;
}


int _write(int file, char *ptr, int len) {
    for (int i = 0; i < len; i++) {
        uart_putc(ptr[i]);
    }
    return len;
}

