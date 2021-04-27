#
## ErisOS Checkra1n Stage3 Component
#

#
## [Component Default General Options]
##
ABI  ?= aapcs
ARCH ?= arm64
AUTOBOOT      ?= 1
USE_LIBC_STUB ?= 1


#
## [Component Include]
##
INC := include


#
## [Component C Sources]
##
C_SRCS := \
	$(wildcard *.c)
#   ... (extend as appropriate)
#   ...
C_SRCS := $(patsubst %.c,%.o,$(C_SRCS))


#
## [Component Assembly Sources]
##
S_SRCS := \
	$(wildcard asm/$(ARCH)/*.S)
#   ... (extend as appropriate)
#   ...
S_SRCS := $(patsubst %.S,%.o,$(S_SRCS))


#
## [Component Overall Sources]
##
SRCS   := $(S_SRCS) $(C_SRCS)


#
## [Component Compiler Options]
##
OUTPUT := obj
WFLAGS := $(WFLAGS)
DFLAGS := $(DFLAGS) \
	-DAUTOBOOT=$(AUTOBOOT) \
	-DUSE_LIBC_STUB=$(USE_LIBC_STUB)
CFLAGS := $(CFLAGS)	\
	-O0		\
	-arch $(ARCH)	\
	-mabi=$(ABI)    \
	-fno-builtin	\
	-fno-common
SFLAGS := $(SFLAGS) $(CFLAGS)
IFLAGS := $(IFLAGS) -I$(INC)
LFLAGS := $(LFLAGS)	\
	-nostdlib	\
	-nostdlibinc	\
	-Wl,-preload	\
	-Wl,-e,start    \
	-Wl,-order_file,$(SRC)/sym_order.txt \
	-Wl,-image_base,0x100000000	     \
	-Wl,-sectalign,__DATA,__common,0x8   \
	-Wl,-segalign,0x4000 		     \


#
## [Component Targets]
##
all: $(OUTPUT) $(S_SRCS) $(C_SRCS)

$(OUTPUT):
	@mkdir -p $@
	$(foreach subdir,$(dir $(C_SRCS) $(S_SRCS)),\
		$(shell mkdir -p $@/$(subdir)))

%.o: %.S | $(OUTPUT)
	$(CC) $(SFLAGS) $(WFLAGS) $(IFLAGS) $(DFLAGS) -c $^ -o $(OUTPUT)/$@

%.o: %.c | $(OUTPUT)
	$(CC) $(CFLAGS) $(WFLAGS) $(IFLAGS) $(DFLAGS) -c $^ -o $(OUTPUT)/$@

clean:
	rm -rf $(OUTPUT)


## META
.POSIX:
.DEFAULT: all
