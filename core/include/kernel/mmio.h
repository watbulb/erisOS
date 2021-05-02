#ifndef ERISOS_KERNEL_MMIO_H
#define ERISOS_KERNEL_MMIO_H

#include <stdint.h>

/* Read & Write MMIO Registers */

// Read
__attribute__((unused))
static inline uint64_t mmio_read32(uint32_t reg) {
    uint32_t data;
    __asm __volatile(
        "ldr %w[data], [%[reg]]"
        : [data]"=r"(data)
        : [reg]"r"(&reg)
        );
    return data;
}

__attribute__((unused))
static inline uint64_t mmio_read64(uint64_t reg) {
    uint64_t data;
    __asm __volatile(
        "ldr %[data], [%[reg]]"
        : [data]"=r"(data)
        : [reg]"r"(&reg)
        );
    return data;
}

// Write
__attribute__((unused))
static inline void mmio_write32(uint32_t reg, uint32_t data) {
    __asm __volatile(
        "str %w[data], [%[reg]]"
        :: [reg]"r"(&reg), [data]"r"(data)
        );
}
__attribute__((unused))
static inline void mmio_write64(uint64_t reg, uint64_t data) {
    __asm __volatile(
        "str %[data], [%[reg]]"
        :: [reg]"r"(&reg), [data]"r"(data)
        );
}

#endif  // ERISOS_KERNEL_MMIO_H
