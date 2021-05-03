.align 4

.globl _enable_interrupts
_enable_interrupts:
    msr daifclr,#0xf
    isb
    ret

.globl _disable_interrupts
_disable_interrupts:
    msr daifset,#0xf
    isb
    ret
