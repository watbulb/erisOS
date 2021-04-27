#
## ErisOS Core
#
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))


#
## [Core Default General Options]
## TODO: Streamline
ABI  ?= aapcs
ARCH ?= arm64
AUTOBOOT ?= 1
USE_LIBC_STUB ?= 1


#
## [Core Image]
##
IMAGE_BIN ?= $(TARGET_PRODUCT_OUTPUT)/ErisOS.bin


#
## [Core Components]
##
COMPONENTS := \
	S3
#	kernel
#	... (extend as appropriate)
#	...


#
## [Core Include]
##
INC := $(CURDIR)/include


#
## [Core Compiler Options]
##
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
	-Wl,-preload	\
	-Wl,-e,start    \
	-Wl,-order_file,$(CURDIR)/sym_order.txt \
	-Wl,-image_base,0x100000000	        \
	-Wl,-sectalign,__DATA,__common,0x8      \
	-Wl,-segalign,0x4000 		        \

#
## [Core Targets]
##
all: core $(IMAGE_BIN)

core: $(COMPONENTS)
S3:
	$(MAKE) -C $@ all
kernel:
	$(MAKE) -C $@ all

$(IMAGE_BIN):
	$(CC) $(WFLAGS) $(IFLAGS) $(CFLAGS) $(DFLAGS) $(LFLAGS) $(call rwildcard,$(COMPONENTS),*.o) -o $@

clean:
	$(foreach comp,$(COMPONENTS),$(MAKE) -C $(comp) $@)
	@rm -f $(IMAGE_BIN)


## META
.PHONY: all core $(COMPONENTS) clean
.POSIX:
.DEFAULT: all
