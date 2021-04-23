#include <stdint.h>
#include "entry.h"

void stage3_handover_kernel(void) {
    kernel_entry(
        gboot_args,
        gboot_entry_point,
        stage3_exit_to_el1_image
    );
}
