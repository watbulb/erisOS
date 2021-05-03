#ifndef ERISOS_COMMON_H
#define ERISOS_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
// #include <stdio.h>

static bool is_16k;
static uintptr_t *gboot_args;
static uintptr_t *gboot_entry_point;

/*
SOC Bases (Taken from Device-Tree):

T8010:
gIOBase:   0x200000000
gGpioBase: 0x20f100000
gUartBase: 0x20a0c0000

T8011: TODO
*/
static const uint64_t gIOBase   = 0x200000000;
static const uint64_t gGpioBase = 0x20f100000;  // +=gIOBase
static const uint64_t gUartBase = 0x20a0c0000;  // +=gIOBase

// #define INFO(fmt, ...)     printf("(ErisOS) "fmt"\n", ##__VA_ARGS__)
// #define ERROR(fmt, ...)    printf("(ErisOS) [E]: "fmt"\n", ##__VA_ARGS__)
// #define WARNING(fmt, ...)  printf("(ErisOS) [W]: "fmt"\n", ##__VA_ARGS__)

// #ifdef  DEBUG
// #define DEBUG_ENABLED 1
// #undef  DEBUG
// #define DEBUG(fmt, ...)    printf("(ErisOS) [D]: "fmt"\n", ##__VA_ARGS__)
// #else
// #define DEBUG(x, ...)
// #endif

#endif // ERISOS_COMMON_H
