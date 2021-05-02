#ifndef ERISOS_KERNEL_ENTRY_H
#define ERISOS_KERNEL_ENTRY_H

#include <stdint.h>

void kernel_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint);

#endif // ERISOS_KERNEL_ENTRY_H
