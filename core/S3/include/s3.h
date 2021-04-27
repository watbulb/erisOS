#include <stdint.h>

#include "lc_stub.h"
#include "asm_stub.h"
#include "../../include/config.h"
#include "../../include/common.h"

// /pexpert/pexpert/arm64/boot.h
#define BOOT_LINE_LENGTH 608


extern uint64_t __bss_start[] __asm("section$start$__DATA$__common");
extern uint64_t __bss_end[]   __asm("segment$end$__DATA");


// /pexpert/pexpert/arm64/boot.h
struct Boot_Video {
    unsigned long	v_baseAddr;	/* Base address of video memory */
    unsigned long	v_display;	/* Display Code (if Applicable */
    unsigned long	v_rowBytes;	/* Number of bytes per pixel row */
    unsigned long	v_width;	/* Width */
    unsigned long	v_height;	/* Height */
    unsigned long	v_depth;	/* Pixel Depth and other parameters */
};

// /pexpert/pexpert/arm64/boot.h
typedef struct boot_args {
    uint16_t		Revision;			            /* Revision of boot_args structure */
    uint16_t		Version;			            /* Version of boot_args structure */
    uint64_t		virtBase;			            /* Virtual base of memory */
    uint64_t		physBase;			            /* Physical base of memory */
    uint64_t		memSize;			            /* Size of memory */
    uint64_t		topOfKernelData;	            /* Highest physical address used in kernel data area */
    struct          Boot_Video Video;	            /* Video Information */
    uint32_t		machineType;		            /* Machine Type */
    void			*deviceTreeP;		            /* Base of flattened device tree */
    uint32_t		deviceTreeLength;	            /* Length of flattened tree */
    char			CommandLine[BOOT_LINE_LENGTH];	/* Passed in command line */
    uint64_t		bootFlags;		                /* Additional flags specified by the bootloader */
    uint64_t		memSizeActual;		            /* Actual size of memory */
} boot_args;


// typedef void (*s3_el3_handover_t) (void *, void *);
// typedef void (*s3_el2_handover_t) (void *, void *);
// typedef void (*s3_el1_handover_t) (void *, void *);


void
runtime_exit(
        uintptr_t *boot_args,
        uintptr_t *boot_entry_point
        );
void
runtime_entry(
        uintptr_t *boot_args,
        uintptr_t *boot_entry_point
        );

void
patch_bootloader(uintptr_t *boot_image);
void
jump_to_runlevel(void);
void
setup_runlevel(uint8_t runlevel);


uintptr_t*
find_next_insn(
        uintptr_t *from,
        uint32_t  size,
        uint32_t  insn,
        uint32_t  mask
        );
uintptr_t*
find_prev_insn(
        uintptr_t *from,
        uint32_t  size,
        uint32_t  insn,
        uint32_t  mask
        );

void
trampoline_entry(uintptr_t *boot_image, uintptr_t *boot_args);

