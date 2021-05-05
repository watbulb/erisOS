#
## ErisOS Core Subassembly
#
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

ifeq ($(TARGET_PRODUCT_OUTPUT),)
$(error Subassembly $(notdir $(basename $(CURDIR))) requires a TARGET_PRODUCT_OUTPUT var)
endif

#
## [Core Subassembly Default General Options]
AUTOBOOT ?= 1
USE_LIBC_STUB ?= 1


#
## [Core Subassembly TARGET]
##
CORE_TARGET ?= $(PRODUCT)


#
## [Core Subassembly Components]
##
COMPONENTS := S3 kernel
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
	-O $\
	-fno-builtin $\
	-fno-common  $\
	-fno-lto
export SFLAGS := $(SFLAGS) $(CFLAGS)
export IFLAGS := $(IFLAGS) $(foreach inc,$(INC),-I$(inc) )
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

all: $(COMPONENTS)

S3:
	$(info )
	$(info [ $@ ])
	$(info )
	@$(MAKE) -C $@ all
	@# Symlink Component Object Folder to Build Root
	@rm -f $(TARGET_PRODUCT_OUTPUT)/core/$@
	@ln -s $(CURDIR)/$@/obj $(TARGET_PRODUCT_OUTPUT)/core/$@ || :

kernel:
	$(info )
	$(info [ $@ ])
	$(info )
	@$(MAKE) -C $@ clean all
	@# Symlink Component Object Folder to Build Root
	@rm -f $(TARGET_PRODUCT_OUTPUT)/core/$@
	@ln -s core/$@/obj $(TARGET_PRODUCT_OUTPUT)/core/$@ || :

$(CORE_TARGET):
	$(CC) $(CFLAGS) $(sort $(IFLAGS) $(LFLAGS)) $(sort $(call rwildcard,$(COMPONENTS),*.o) $(TARGET_PRODUCT_OUTPUT)/lib/libc.a) -o $(TARGET_PRODUCT_BINARY)
	$(VMACHO) -f $(TARGET_PRODUCT_BINARY) $(TARGET_PRODUCT_BINARY).bin

clean:
	$(foreach comp,$(COMPONENTS),\
		$(info $(shell $(MAKE) -C $(comp) $@)))


## META
.POSIX:
.PHONY: all $(COMPONENTS) $(CORE_TARGET) clean
.DEFAULT: all
.NOTPARALLEL:
