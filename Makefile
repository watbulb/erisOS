#
## ErisOS Project Makefile
#

export PRODUCT := ErisOS
export TARGET_PRODUCT_OUTPUT := $(CURDIR)/build

COMPONENTS := \
	core
#   ... (extend as appropriate)
#   ...


#
## [Default OS Component Compile Options]
##
export CC     ?= $(shell xcrun -f clang)
export ABI    ?= aapcs
export ARCH   ?= arm64
export CFLAGS ?= -fno-color-diagnostics -std=c17
export WFLAGS ?= -Wall -Wpedantic -Wconversion 


erisos: all
ErisOS: all
all: $(TARGET_PRODUCT_OUTPUT) $(COMPONENTS)

$(TARGET_PRODUCT_OUTPUT):
	mkdir -p $@

#
## [OS Components]
##
$(COMPONENTS): $(TARGET_PRODUCT_OUTPUT)
	$(MAKE) -C $@
	@mkdir -p $^/$@ && ln -s $(CURDIR)/$@/obj $^/$@

clean: $(TARGET_PRODUCT_OUTPUT)
	$(foreach comp,$(COMPONENTS),\
		$(MAKE) -C $(comp) $@)
	rm -rf $^


## META
.POSIX:
.DEFAULT: all
