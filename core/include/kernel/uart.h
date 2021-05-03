#ifndef ERISOS_KERNEL_UART_H
#define ERISOS_KERNEL_UART_H

#include <stdint.h>
#include "common.h"

#define rULCON0     (*(volatile uint32_t*)(gUartBase + 0x00))  //UART 0 Line control
#define rUCON0      (*(volatile uint32_t*)(gUartBase + 0x04))  //UART 0 Control
#define rUFCON0     (*(volatile uint32_t*)(gUartBase + 0x08))  //UART 0 FIFO control
#define rUMCON0     (*(volatile uint32_t*)(gUartBase + 0x0c))  //UART 0 Modem control
#define rUTRSTAT0   (*(volatile uint32_t*)(gUartBase + 0x10))  //UART 0 Tx/Rx status
#define rUERSTAT0   (*(volatile uint32_t*)(gUartBase + 0x14))  //UART 0 Rx error status
#define rUFSTAT0    (*(volatile uint32_t*)(gUartBase + 0x18))  //UART 0 FIFO status
#define rUMSTAT0    (*(volatile uint32_t*)(gUartBase + 0x1c))  //UART 0 Modem status
#define rUTXH0      (*(volatile uint32_t*)(gUartBase + 0x20))  //UART 0 Transmission Hold
#define rURXH0      (*(volatile uint32_t*)(gUartBase + 0x24))  //UART 0 Receive buffer
#define rUBRDIV0    (*(volatile uint32_t*)(gUartBase + 0x28))  //UART 0 Baud rate divisor
#define rUDIVSLOT0  (*(volatile uint32_t*)(gUartBase + 0x2C))  //UART 0 Baud rate divisor
#define rUINTM0     (*(volatile uint32_t*)(gUartBase + 0x38))  //UART 0 Baud rate divisor

#define rT8011RX    (*(volatile uint32_t*)(gGpioBase + 0x2A0))
#define rT8011TX    (*(volatile uint32_t*)(gGpioBase + 0x2A4))
#define UART_TX_MUX 0x8723A0
#define UART_RX_MUX 0x0763A0

void uart_bringup(void);
void uart_pinmux_init(void);
void uart_teardown(void);
void uart_putc(char c);
void uart_puts(const char *str);

#endif // ERISOS_KERNEL_UART_H
