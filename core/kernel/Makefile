#
## ErisOS Core Kernel Component
#

#
## [Component Include (Extras)]
##
INC :=


#
## [Component C Sources]
##
C_SRCS := \
	$(wildcard *.c)
#   ... (extend as appropriate)
#   ...
C_SRCS := $(sort $(patsubst %.c,%.o,$(C_SRCS)))


#
## [Component Assembly Sources]
##
S_SRCS := \
	$(wildcard arch/$(ARCH)/*.S)
#   ... (extend as appropriate)
#   ...
S_SRCS := $(sort $(patsubst %.S,%.o,$(S_SRCS)))


#
## [Component Overall Sources]
##
SRCS   := $(S_SRCS) $(C_SRCS)


#
## [Component Compiler Options]
##
OUTPUT := $(CURDIR)/obj
WFLAGS := $(WFLAGS)
DFLAGS := $(DFLAGS)
IFLAGS := $(IFLAGS) $(foreach inc,$(INC),-I$(inc) )
# ... CFLAGS
# ... SFLAGS
# (extend as appropriate)


#
## [Component Targets]
##
all: $(OUTPUT) $(S_SRCS) $(C_SRCS)

$(OUTPUT):
	@mkdir -p $@
	$(foreach subdir,$(dir $(C_SRCS) $(S_SRCS)),\
		$(shell mkdir -p $@/$(subdir)))

%.o: %.S | $(OUTPUT)
	 $(CC) $(WFLAGS) $(SFLAGS) $(IFLAGS) $(DFLAGS) -c $^ -o $(OUTPUT)/$@

%.o: %.c | $(OUTPUT)
	 $(CC) $(WFLAGS) $(CFLAGS) $(IFLAGS) $(DFLAGS) -c $^ -o $(OUTPUT)/$@

clean:
	rm -rf $(OUTPUT)


## META
.POSIX:
.PHONY: all $(OUTPUT) clean
.DEFAULT: all
