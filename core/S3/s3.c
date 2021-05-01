#include <stdint.h>
#include "include/s3.h"

uint64_t exception_stack[0x4000 / 8] = {1};
uint64_t sched_stack[0x4000 / 8] = {1};

#if ERISOS_ARM_RUNLEVEL == EL3_RUNLEVEL
/*! Entrypoint for EL3 Hypervisor Runtime */
void runtime_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint)
{
    hypervisor_entry(boot_args, boot_entrypoint);
    runtime_exit(boot_args, boot_entrypoint);
}
#elif ERISOS_ARM_RUNLEVEL == EL2_RUNLEVEL
/*! Entrypoint for EL2 Bootloader Runtime */
void runtime_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint)
{
    bootloader_entry(boot_args, boot_entrypoint);
    runtime_exit(boot_args, boot_entrypoint);
}
#elif ERISOS_ARM_RUNLEVEL == EL1_RUNLEVEL
/*! Entrypoint for EL1 Kernel Runtime     */
void runtime_entry(uintptr_t *boot_args, uintptr_t *boot_entrypoint)
{
    // kernel_entry(boot_args, boot_entrypoint);
    runtime_exit(boot_args, boot_entrypoint);
}
#else
#error "Unknown ERISOS_ARM_RUNLEVEL"
#endif

void runtime_exit(uintptr_t *boot_entrypoint, uintptr_t *boot_args)
{
    jump_to_image((uint64_t) boot_entrypoint, (uint64_t) boot_args);
}

uintptr_t *find_next_insn(uintptr_t *from, uint32_t size, uint32_t insn, uint32_t mask)
{
    while (size)
    {
        if ((*from & mask) == (insn & mask))
            return from;

        from++;
        size -= 4;
    }
    return NULL;
}
uintptr_t *find_prev_insn(uintptr_t *from, uint32_t size, uint32_t insn, uint32_t mask)
{
    while (size)
    {
        if ((*from & mask) == (insn & mask))
            return from;

        from--;
        size -= 4;
    }
    return NULL;
}

void patch_bootloader(uintptr_t *boot_image) {
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
            uintptr_t *func_prolog = find_prev_insn(sys_3_c7_c4_1, // from
                0x100,      // size
                0xaa0103e2, // inst
                0xFFFFFFFF  // mask
                );
            if (func_prolog)
            {
                long offset = ((boot_image + 0x180) - (func_prolog + 0x4));
                clear_hook_orig_backing[0] = (uint32_t)func_prolog[0];
                clear_hook_orig_backing[1] = (uint32_t)func_prolog[1];
                memcpy((char *)(boot_image + 0x180),
                       (void *)(&clear_hook),&clear_hook_end - &clear_hook);
                func_prolog[0] = 0xaa1e03e5;
                func_prolog[1] = 0x94000000 | (((uint64_t)offset >> 2) & 0x3FFFFFF);
                invalidate_icache();
            }
        }
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
        if (tramp)
        {
            tramp[0] = tramp_hook[0];
            tramp[1] = tramp_hook[1];
            tramp[2] = tramp_hook[2];
            tramp[3] = tramp_hook[3];
            tramp[4] = tramp_hook[4];
            invalidate_icache();
        }
    }
    // TODO: aes_keygen
}

void jump_to_runlevel(void)
{
    if (gboot_entry_point == NULL)
        do { ;; } while (1);

    // Jump to a specific runlevel runtime
    switch (ERISOS_ARM_RUNLEVEL)
    {
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

void setup_runlevel(uint8_t runlevel)
{
    if (gboot_entry_point == NULL)
    {
        do { ;; } while (1);
    } else if (gboot_args != NULL) {
        struct boot_args *args = (struct boot_args *)gboot_args;
        strcpy((char *)args->CommandLine, "debug=0x49 serial=1 wdt=0");
        args->Video.v_display = !args->Video.v_display;
    }

    // Run some presetup depending on selected runlevel
    switch (runlevel)
    {
        case EL3_RUNLEVEL:
        case EL2_RUNLEVEL:
            break;
        case EL1_RUNLEVEL:
            setup_el1((void *)jump_to_runlevel,
                    (uint64_t)gboot_entry_point,
                    (uint64_t)gboot_args);
            break;
        default:
            break;
    }
}

void trampoline_entry(uintptr_t *boot_image, uintptr_t *boot_args)
{
    if (__bss_start[0] == 0x746F6F626F737561)
    {
        void *copy_zone = (void *)0x819000000;
        const uint64_t autoboot_sz = (__bss_start[1]);
        smemcpy128(copy_zone, __bss_start, (uint32_t)(autoboot_sz + 64) / 16);
        __bss_start[0] = 0;
    }
    if (!boot_args)
    {
        strcpy((char *)boot_image + 0x200, "Stage 2 ErisOS Loader");
        patch_bootloader(boot_image);
    } else {
        gboot_args = boot_args;
        gboot_entry_point = boot_image;
        setup_runlevel(ERISOS_ARM_RUNLEVEL);
    }
}
