#ifndef ERISOS_COMMON_H
#define ERISOS_COMMON_H

#include <stdint.h>
#include <stddef.h>
// #include <stdio.h>

static uintptr_t *gboot_args = NULL;
static uintptr_t *gboot_entry_point = NULL;

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
