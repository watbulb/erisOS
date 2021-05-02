.align 4
.globl _get_mmfr0
_get_mmfr0:
    mrs x0, id_aa64mmfr0_el1
    ret
