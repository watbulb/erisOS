#
## ErisOS Core Subassembly
#
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))


#
## [Core Subassembly Default General Options]
AUTOBOOT ?= 1
USE_LIBC_STUB ?= 1


#
## [Core Subassembly TARGET]
##
CORE_TARGET ?= $(TARGET_PRODUCT_BINARY)


#
## [Core Subassembly Components]
##
COMPONENTS := \
	S3
#	kernel
#	... (extend as appropriate)
#	...


#
## [Core Subassembly Include]
##
INC := $(CURDIR)/include
#	... (extend as appropriate)
#	...


#
## [Core Subassembly Compiler Options]
## [inherits parent & propogates newopts. down to components]
##
export WFLAGS := $(WFLAGS)
export DFLAGS := $(DFLAGS) $\
	-DAUTOBOOT=$(AUTOBOOT) $\
	-DUSE_LIBC_STUB=$(USE_LIBC_STUB)
export CFLAGS := $(CFLAGS) $\
	-O0 $\
	-fno-builtin $\
	-fno-common  $\
	-fno-lto
export SFLAGS := $(SFLAGS) $(CFLAGS)
export IFLAGS := $(IFLAGS) -I$(INC)
LFLAGS := $(LFLAGS)	$\
	-static		    $\
	-nostdlib	    $\
	-Wl,-preload	$\
	-Wl,-e,start    $\
	-Wl,-order_file,./sym_order.txt 	$\
	-Wl,-image_base,0x100000000	        $\
	-Wl,-sectalign,__DATA,__common,0x8  $\
	-Wl,-segalign,0x4000

#
## [Core Subassembly Targets]
##

all: $(COMPONENTS) $(CORE_TARGET)

S3:
	@echo "-> building [ $@ ]"
	@$(MAKE) -C $@ all
	@ln -Fs $(CURDIR)/$@/obj $(TARGET_PRODUCT_OUTPUT)/core/$@

kernel:
	@echo "-> building [ $@ ]"
	@$(MAKE) -C $@ all
	@ln -Fs $(CURDIR)/$@/obj $(TARGET_PRODUCT_OUTPUT)/core/$@

$(CORE_TARGET):
	$(CC) $(CFLAGS) $(sort $(IFLAGS) $(LFLAGS)) $(call rwildcard,$(COMPONENTS),*.o) $(wildcard ../../pongoOS/newlib/build/libc.a) -o $@
	$(VMACHO) -f $@ $@.bin

clean:
	$(foreach comp,$(COMPONENTS),\
		$(MAKE) -C $(comp) $@)


## META
.POSIX:
.PHONY: all $(COMPONENTS) clean
.DEFAULT: all
.NOTPARALLEL:
