# RISCV environment variable must be set

CC=$(RISCV)/bin/riscv32-unknown-elf-gcc
OBJCOPY=$(RISCV)/bin/riscv32-unknown-elf-objcopy
CFLAGS=-march=rv32i -mabi=ilp32 -std=gnu11 -Wall -nostartfiles -fno-common
LFLAGS= -static -L$(RISCV)/lib/gcc/riscv32-unknown-elf/7.2.0/ -lgcc
PROG?=

assem := $(PROG).s
$(assem): $(PROG).c
	$(CC) $< -S $(CFLAGS) $(LFLAGS)

.PHONY: assem
assem: $(assem)

elf := $(PROG).elf
$(elf): $(PROG).c
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $(PROG).c

.PHONY: elf
elf: $(elf)

bin := $(PROG).bin
$(bin): $(elf)
	$(OBJCOPY) -O binary $< $@

.PHONY: bin
bin: $(bin)

hex := $(PROG).hex
$(hex): $(bin)
	od -t x4 -An -w4 -v $< > $@

.PHONY: hex
hex: $(hex)

.PHONY: clean
clean:
	rm -rf $(hex) $(elf) $(assem) $(bin)
