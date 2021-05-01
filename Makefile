#
## ErisOS Project Makefile
#

export PRODUCT := ErisOS
export TARGET_PRODUCT_OUTPUT := $(CURDIR)/build
export TARGET_PRODUCT_BINARY := $(TARGET_PRODUCT_OUTPUT)/$(PRODUCT)

COMPONENTS := \
	core
#   ... (extend as appropriate)
#   ...


#
## [Default OS Component Compile Options]
##
export SDK     ?= iphoneos
export ABI     ?= aapcs
export ARCH    ?= arm64
export TARGET  ?= arm64-apple-ios13.5
export SYSROOT ?= $(shell xcrun --sdk $(SDK) --show-sdk-path)

export VMACHO  ?= $(CURDIR)/bin/vmacho
export CLANG   ?= $(shell xcrun --sdk $(SDK) -f clang)

ifeq ($(SYSROOT),)
$(error Could not find SDK $(SDK))
else ifeq ($(VMACHO),)
$(error Could not find VMACHO $(VMACHO))
endif

export CFLAGS ?= -std=c17 -mabi=$(ABI)
export WFLAGS ?= -Wall -Wpedantic -Wconversion
ifeq ($(DEBUG),1)
export DFLAGS += -DDEBUG
endif

export CC := $(CLANG) -isysroot $(SYSROOT) -arch $(ARCH) --target=$(TARGET)

# Project Wide Debug
export DEBUG ?= 1

#
## [OS Components & Targets]
##

all: $(TARGET_PRODUCT_OUTPUT) $(COMPONENTS)

$(TARGET_PRODUCT_OUTPUT):
	$(foreach comp,$(COMPONENTS),\
		$(shell mkdir -p $@/$(comp)))

$(COMPONENTS): $(TARGET_PRODUCT_OUTPUT)
	@echo "[ $@ ]"
	@$(MAKE) -C $@ all

tags:
	@ctags -R \
		core  \
		../pongoOS/src ../pongoOS/include
	@ln -fs ./tags ./.vscode/tags

symbols: $(TARGET_PRODUCT_BINARY)
	nm -S $^

undef-symbols: $(TARGET_PRODUCT_BINARY)
	nm -u $^

clean: $(TARGET_PRODUCT_OUTPUT)
	$(foreach comp,$(COMPONENTS),\
		$(MAKE) -C $(comp) $@)
	rm -rf $^


## META
.POSIX:
.DEFAULT: all
.PHONY: all $(COMPONENTS) tags symbols undef-symbols clean
