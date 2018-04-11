# RISCV environment variable must be set
CC=$(RISCV)/bin/riscv32-unknown-elf-gcc
OBJCOPY=$(RISCV)/bin/riscv32-unknown-elf-objcopy
CFLAGS=-march=rv32i -mabi=ilp32 -std=gnu11 -Wall -fno-common

# Set board support package path
BSP_PATH=bsp

# Linker Script Flags
LINKER_SCRIPT=$(BSP_PATH)/Adept.lds
LDFLAGS=-T $(LINKER_SCRIPT) -nostartfiles -static -L$(RISCV)/lib/gcc/riscv32-unknown-elf/7.2.0/ -lgcc

# Generate sources and outputs lists
ASM_SRC=$(BSP_PATH)/entry.S
SRCS=$(wildcard simple/*.c)
SRCS+=$(wildcard intermediate/*.c)
HEXS=$(SRCS:%.c=hex/%.hex)
ELFS=$(SRCS:%.c=elf/%.elf)
BINS=$(SRCS:%.c=bin/%.bin)
ASM_OBJS=$(ASM_SRC:%.S=%.o)

LINK_OBJS=$(ASM_OBJS)

.PHONY: all
all: directories hex

.PHONY: directories
directories:
	mkdir -p elf/simple bin/simple hex/simple
	mkdir -p elf/intermediate bin/intermediate hex/intermediate

$(ELFS): elf/%.elf: %.c $(LINK_OBJS) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) $(LINK_OBJS) -o $@ $< $(LDFLAGS)

.PHONY: asm_obj
asm_obj: $(ASM_OBJS)

$(ASM_OBJS): %.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: elf
elf: $(ELFS)

$(BINS): bin/%.bin: elf/%.elf
	$(OBJCOPY) -O binary $< $@

.PHONY: bin
bin: $(BINS)

$(HEXS): hex/%.hex: bin/%.bin
	od -t x4 -An -w4 -v $< > $@

.PHONY: hex
hex: $(HEXS)

.PHONY: clean
clean:
	rm -rf $(HEXS) $(ELFS) $(BINS) $(ASM_OBJS)
