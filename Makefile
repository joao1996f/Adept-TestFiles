# RISCV environment variable must be set
CC=$(RISCV)/bin/riscv32-unknown-elf-gcc
CFLAGS=-march=rv32i -mabi=ilp32 -std=gnu11 -Wall -fno-common

# Set board support package path
BSP_PATH=bsp

# Linker Script Flags
LINKER_SCRIPT=$(BSP_PATH)/Adept.lds
LDFLAGS=-T $(LINKER_SCRIPT) -nostartfiles -static -L$(RISCV)/lib/gcc/riscv32-unknown-elf/7.2.0/ -lgcc

# Generate sources and outputs lists
ASM_SRC=$(BSP_PATH)/entry.S
C_SRC=$(BSP_PATH)/exit.c
SRCS=$(wildcard simple/*.c)
SRCS+=$(wildcard intermediate/*.c)
ELFS=$(SRCS:%.c=elf/%.elf)
ASM_OBJS=$(ASM_SRC:%.S=%.o)
C_OBJS=$(C_SRC:%.c=%.o)

LINK_OBJS=$(ASM_OBJS) $(C_OBJS)

.PHONY: all directories clean
all: directories $(ELFS)

directories:
	mkdir -p elf/simple
	mkdir -p elf/intermediate

$(ELFS): elf/%.elf: %.c $(LINK_OBJS) $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) $(LINK_OBJS) -o $@ $< $(LDFLAGS)

$(ASM_OBJS): %.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

$(C_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(ELFS) $(ASM_OBJS) $(C_OBJS)
