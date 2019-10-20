### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
TARGET	= kernel
IMAGE	= powerkernel.iso
ARCH	= x86
CC	= i686-elf-gcc
MAKE	= make
# generic flags
CFLAGS	+= -I./kernel/include -g ggdb -O0
CFLAGS	+= -I./arch/$(ARCH)/include
LDFLAGS	= -ffreestanding -O2 -nostdlib -m32

OBJ	+= $(shell find './kernel' -name '*.o')
ifeq ($(ARCH), x86)
OBJ	+= $(shell find './arch/x86' -name '*.o')
LD	= ./arch/x86/x86-32.ld
endif
ifeq ($(ARCH), arm)
OBJ	+= $(shell find './arch/arm' -name '*.o')
LD	= ./arch/arm/x86-32.ld
endif

# Build Rules

.PHONY: all
all: link

.PHONY: compile
compile:
	ARCH=$(ARCH) $(MAKE) -C arch all
	ARCH=$(ARCH) $(MAKE) -C kernel all

.PHONY: link
link: compile
	@mkdir -p ./bin
	$(CC) -T $(LD) -o ./bin/$(TARGET).bin $(LDFLAGS) $(OBJ)

.PHONY: iso
iso: all
	@mkdir -p ./tmp
	@mkdir -p ./tmp/boot
	ARCH=$(ARCH) $(MAKE) -C arch iso
	@cp ./bin/$(TARGET).bin ./tmp/boot/$(TARGET).bin
	@grub-mkrescue -o $(IMAGE) tmp
	@rm -rf ./tmp

.PHONY: boot
boot: iso clean
	@echo "qemu-system-i386 -nographic -m 64M -cdrom $(IMAGE) -serial mon:stdio"
	@echo "Boot Emulation Starting..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@qemu-system-i386 -nographic -m 64M -cdrom $(IMAGE) -serial mon:stdio

.PHONY: clean
clean:
	ARCH=$(ARCH) $(MAKE) -C kernel clean
	ARCH=$(ARCH) $(MAKE) -C arch clean
	@find . -name '*.gch' -delete

.PHONY: reset
prune: clean
	@rm -rf $(IMAGE) ./bin/$(TARGET).bin ./boot/$(TARGET).bin tmp bin

