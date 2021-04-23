#
## ErisOS Project Makefile
#

OUTPUT := build

# TODO: Extend to fit a `core` general component
COMPONENTS := \
	core/S3
#   ... (extend as appropriate)
#   ...

#
## [Default OS Component Compile Options]
##
export CC     := $(shell xcrun -f clang)
export ABI    ?= aapcs
export ARCH   ?= arm64
export CFLAGS ?= -fno-color-diagnostics
export WFLAGS ?= -Wall -Wpedantic -Wconversion 


all: $(OUTPUT) $(COMPONENTS)

#
## [OS Build Obj Aggregation Path]
##
(OUTPUT):
	mkdir -p $@

#
## [OS Components]
##
$(COMPONENTS): $(OUTPUT)
	$(MAKE) -C $@
	ln -s $@/obj $^/$@_obj

clean: $(OUTPUT)
	$(foreach comp,$(COMPONENTS),\
		$(MAKE) -C $(comp) $@)
	rm -rf $^


## META
.PHONY: $(OUTPUT)
.POSIX:
.DEFAULT: all
