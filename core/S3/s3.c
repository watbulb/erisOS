#include <stdint.h>
#include "include/s3.h"

uint64_t   exception_stack[0x4000/8] = {1};
uint64_t   sched_stack[0x4000/8] = {1};

#if   ERISOS_ARM_RUNLEVEL == EL3_RUNLEVEL
/*! Entrypoint for EL3 Hypervisor Runtime */
void runtime_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint) {
    hypervisor_entry(boot_args, boot_entrypoint);
    runtime_exit(boot_args, boot_entrypoint);
}
#elif ERISOS_ARM_RUNLEVEL == EL2_RUNLEVEL
/*! Entrypoint for EL2 Bootloader Runtime */
void runtime_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint) {
    bootloader_entry(boot_args, boot_entrypoint);
    runtime_exit(boot_args, boot_entrypoint);
}
#elif ERISOS_ARM_RUNLEVEL == EL1_RUNLEVEL
/*! Entrypoint for EL1 Kernel Runtime     */
void runtime_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint) {
    // kernel_entry(boot_args, boot_entrypoint);
    runtime_exit(boot_args, boot_entrypoint);
}
#else
#error "Unknown ERISOS_ARM_RUNLEVEL"
#endif


void runtime_exit(uintptr_t *boot_entrypoint, uintptr_t *boot_args) {
    jump_to_image((uint64_t)boot_entrypoint, (uint64_t)boot_args);
}


/* 
_start -> .trampoline_entry(x0(x9), x1) -> \
patch_bootloader(x0(x9)) -> disable DRAM clear -> \
for i++ in (5): tramp_ins[i] = tramp_hook[i] -> \
iorvbar_yeet -> aes_keygen -> invalidate_icache -> \
hooks run -> gboot* = boot* -> memset(bss_start, 0, end) -> \
setup_runlevel/el1(jump_to_runtime_entry) -> blr jump_to_runtime_entry if currentel != 3 -> jump_to_runtime_entry -> l1_kernel_entry
*/

uintptr_t* find_next_insn(uintptr_t* from, uint32_t size, uint32_t insn, uint32_t mask)
{
    while (size) {
        if ((*from & mask) == (insn & mask)) {
            return from;
        }
        from++;
        size -= 4;
    }
    return NULL;
}
uintptr_t* find_prev_insn(uintptr_t* from, uint32_t size, uint32_t insn, uint32_t mask)
{
    while (size) {
        if ((*from & mask) == (insn & mask))
            return from;
 
        from--;
        size -= 4;
    }
    return NULL;
}


void patch_bootloader(uintptr_t *boot_image) {

    if (!boot_image)
        return;

    /*
     ** Disable DRAM Clear
     */
    {
        uintptr_t *sys_3_c7_c4_1 = find_next_insn(boot_image, // from
            0x80000,    // size
            0xd50b7423, // inst
            0xFFFFFFFF  // mask 
        );
        if (sys_3_c7_c4_1) {
            uintptr_t *func_prolog = find_prev_insn(sys_3_c7_c4_1,
                0x100,      // size
                0xaa0103e2, // inst
                0xFFFFFFFF  // mask
            );
            if (func_prolog) {
                int64_t offset = (0x180 + (uint64_t)boot_image) - (0x4 + (int64_t)func_prolog);
                clear_hook_orig_backing[0] = func_prolog[0];
                clear_hook_orig_backing[1] = func_prolog[1];
                memcpy((void *)0x180 + (uint64_t)boot_image,
                       (void *)&clear_hook, &clear_hook_end - &clear_hook); 
                func_prolog[0] = 0xaa1e03e5;
                func_prolog[1] = 0x94000000 | (((uint64_t)offset >> 2) & 0x3FFFFFF);
            }
        }
        // TODO: invalidate_icache();
    }

    /*
     ** Create Trampoline Hooks
     */
    {
        uintptr_t *tramp = find_next_insn(boot_image,
            0x80000,
            0xd2800012,
            0xFFFFFFFF
        );
        if (tramp) {
            tramp[0] = tramp_hook[0];
            tramp[1] = tramp_hook[1];
            tramp[2] = tramp_hook[2];
            tramp[3] = tramp_hook[3];
            tramp[4] = tramp_hook[4];
        }
        // TODO: invalidate_icache();
    }
}


void jump_to_runtime(void) {
    if (!gboot_entry_point || !gboot_args)
        ;
    switch (ERISOS_ARM_RUNLEVEL) {
        case EL3_RUNLEVEL:
        case EL2_RUNLEVEL:
            // XXX: Minor prejump setup/adjustments
            break;
        case EL1_RUNLEVEL:
            runtime_entry(gboot_entry_point, gboot_args);
            break;
        default:
            break;        
    }
}


void setup_runlevel(uint8_t runlevel) {
    if (!gboot_entry_point || !gboot_args)
        ;
    switch (runlevel) {
        case EL3_RUNLEVEL:
        case EL2_RUNLEVEL:
            break;
        case EL1_RUNLEVEL:
            setup_el1(jump_to_runtime,
                (uint64_t)gboot_entry_point,
                (uint64_t)gboot_args);
            break;
         default:
            break;
    }
}

void trampoline_entry(uintptr_t *boot_image, uintptr_t *boot_args) {
    if (__bss_start[0] == 0x746F6F626F737561) {
        void *copy_zone = (void*)0x819000000;
        const uint32_t autoboot_sz  = (__bss_start[1]);
        smemcpy128(copy_zone, __bss_start, (autoboot_sz + 64)/16);
        __bss_start[0] = 0;
    }
    if (!boot_args) {
        strcpy((char *)boot_image + 0x200, "Stage 2 ErisOS Loader");
        patch_bootloader(boot_image);
    } else {
        gboot_args = boot_args;
        gboot_entry_point = boot_image;
        setup_runlevel(ERISOS_ARM_RUNLEVEL);
    }
}

