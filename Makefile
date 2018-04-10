# RISCV environment variable must be set
CC=$(RISCV)/bin/riscv32-unknown-elf-gcc
OBJCOPY=$(RISCV)/bin/riscv32-unknown-elf-objcopy
CFLAGS=-march=rv32i -mabi=ilp32 -std=gnu11 -Wall -nostartfiles -fno-common
LFLAGS=-static -L$(RISCV)/lib/gcc/riscv32-unknown-elf/7.2.0/ -lgcc

SRCS=$(wildcard simple/*.c)
HEXS=$(SRCS:%.c=hex/%.hex)
ELFS=$(SRCS:%.c=elf/%.elf)
BINS=$(SRCS:%.c=bin/%.bin)

.PHONY: all
all: directories hex

.PHONY: directories
directories:
	mkdir -p elf/simple bin/simple hex/simple

$(ELFS): elf/%.elf: %.c
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $<

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
	rm -rf $(HEXS) $(ELFS) $(BINS)
