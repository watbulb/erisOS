#include <stdint.h>

extern void
stage3_exit_to_el1_image(void* boot_args, void* boot_entry_point);

extern uintptr_t* gboot_args;
extern uintptr_t* gboot_entry_point;

extern void
stage3_handover_kernel(
    uintptr_t *gboot_args,
    uintptr_t *gboot_entry_point,
    void (*stage3_exit_to_el1_image)(void *, void *)
);

