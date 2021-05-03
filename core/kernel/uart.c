#include "kernel/uart.h"
#include "kernel/irq.h"

uint32_t rULCON0_orig;
uint32_t  rUCON0_orig;
uint32_t rUFCON0_orig;
uint32_t rUMCON0_orig;

// modified from pongo: pongoOS/src/drivers/uart/uart.c
void uart_pinmux_init(void)
{
    // Pinmux debug UART on ATV4K
    // This will also pinmux uart0 on iPad Pro 2G
    rT8011TX = UART_TX_MUX;
    rT8011RX = UART_RX_MUX;
}

void uart_putc(char c) {
    if (c == '\n')
        c  = '\r';
    do {
        __asm("nop");
    } while (!(rUTRSTAT0 & 0x04));
    rUTXH0 = (unsigned)(c);
    return;
}

void uart_puts(const char* str) {
    while (*str) uart_putc(*str++);
}

void uart_teardown(void) {
    // Restore state set by iBoot
    rUCON0  = rUCON0_orig;
    rULCON0 = rULCON0_orig;
    rUFCON0 = rUFCON0_orig;
    rUMCON0 = rUMCON0_orig;
}

void uart_bringup(void)
{
#if defined(SOC_T8011)
    serial_pinmux_init();
#endif
    disable_interrupts();

    rULCON0_orig = rULCON0;
    rULCON0 = 3;

    rUCON0_orig = rUCON0;
    rUCON0  = 0x405;

    rUFCON0_orig = rUFCON0; 
    rUFCON0 = 0;

    rUMCON0_orig = rUMCON0;
    rUMCON0 = 0;

    enable_interrupts();
}
