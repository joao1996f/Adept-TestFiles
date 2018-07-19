# RISCV environment variable must be set
CC=$(RISCV)/bin/riscv32-unknown-elf-gcc
OBJCOPY=$(RISCV)/bin/riscv32-unknown-elf-objcopy
INC=include/
CFLAGS=-march=rv32i -mabi=ilp32 -std=gnu11 -Wall -fno-common -I$(INC)

# Set board support package path
BSP_PATH=../bsp

# Linker Script Flags
LINKER_SCRIPT=$(BSP_PATH)/Adept.lds
LDFLAGS=-T $(LINKER_SCRIPT) -nostartfiles -static
SRCS=$(wildcard src/*.S)
ELFS=$(SRCS:src/%.S=elf/%.elf)
BINS=$(SRCS:src/%.S=bin/%.bin)
HEXS=$(SRCS:src/%.S=hex/%.hex)

.PHONY: all directories clean
all: directories $(HEXS)

directories:
	mkdir -p hex/ elf/ bin/

$(ELFS): elf/%.elf: src/%.S $(LINKER_SCRIPT)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(C_OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BINS): bin/%.bin: elf/%.elf $(ELFS)
	$(OBJCOPY) -O binary $< $@

$(HEXS): hex/%.hex: bin/%.bin $(BINS)
	od -t x4 -An -w4 -v $< > $@
	if [ $@ = "hex/slli.hex" ]; then\
		sed '34s/00/40/' $@ > $(subst slli,slli_trap,$@);\
	fi

clean:
	rm -rf $(ELFS) $(BINS) $(HEXS)
