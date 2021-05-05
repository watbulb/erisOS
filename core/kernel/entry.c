/*
 * ErisOS Kernel Entrypoint & Setup
 *
*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "common.h"
#include "version.h"
#include "kernel/entry.h"
#include "kernel/irq.h"
#include "kernel/mm.h"
#include "kernel/mmio.h"
#include "kernel/uart.h"

void kernel_entry(__unused uintptr_t *boot_args, __unused uintptr_t *boot_entrypoint) {
    is_16k = check_is_16k();
    // TODO: pass is_16k down to mmu layer

    // TODO: Install exception vector here for IRQ handling

    // Bringup UART0
    uart_bringup();

    // Welcome
    disable_interrupts();
    uart_puts("ErisOS (Version: " VERSION ")\n");
    enable_interrupts();

    /*
     ** TEARDOWN PHASE
     */

    uart_teardown();

#if 0
    do {
    __asm("nop");
    } while(1);
#endif

    return;
}
