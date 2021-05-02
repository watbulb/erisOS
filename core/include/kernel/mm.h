#ifndef ERISOS_KERNEL_MM_H
#define ERISOS_KERNEL_MM_H

#include <stdint.h>
#include <stdbool.h>

extern uint64_t get_mmfr0(void);
static bool check_is_16k(void)
{
    return ((get_mmfr0() >> 20) & 0xf) == 0x1;
}

#endif  // ERISOS_KERNEL_MM_H
