#ifndef ERISOS_CONFIG_H
#define ERISOS_CONFIG_H

/* User Editable Configuration */
#define USE_LIBC_STUB 1
#define ERISOS_ARM_RUNLEVEL 1


/* Non-Editable Configuration */
#if !defined(ERISOS_ARM_RUNLEVEL)
#error "ERISOS_ARM_RUNLEVEL requires definition"
#elif ERISOS_ARM_RUNLEVEL > 3 || ERISOS_ARM_RUNLEVEL < 0
#error "ERISOS_ARM_RUNLEVEL needs to be one of (1 , 2 , 3)"
#else
#define EL3_RUNLEVEL 3
#define EL2_RUNLEVEL 2
#define EL1_RUNLEVEL 1
#endif

#endif // ERISOS_CONFIG_H
