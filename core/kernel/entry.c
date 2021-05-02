/*
 * ErisOS Kernel Entrypoint & Setup
 *
*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "common.h"
#include "kernel/entry.h"
#include "kernel/mm.h"
#include "kernel/mmio.h"

void kernel_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint) {
    is_16k = check_is_16k();
    // mmio_read64(UINT64_MAX);
    // mmio_write64(UINT64_MAX, is_16k);
    return;
}
