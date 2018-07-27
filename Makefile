### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
TARGET	= kernel
AS	= nasm
CC	= i686-elf-gcc
# generic flags
CFLAGS += -I./src/include
# if platform == x86
CFLAGS += -I./platform/x86/include -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fstrength-reduce -fomit-frame-pointer -Wno-uninitialized -masm=intel
# else ..
LDFLAGS	= -ffreestanding -O2 -nostdlib -m32
AFLAGS	= -felf
# if platform == x86
ASRC	= ./platform/x86/boot/bootloader.asm
# else ...
# generic source files
CSRC	+= $(wildcard ./src/*.c)
# If platform == x86
CSRC	+= $(wildcard ./platform/x86/*.c)
# else ...
LDSRC	= ./platform/x86/x86-32.ld 
OBJ	= $(shell find './' -name '*.o')
IMAGE	= powerkernel.iso

# Build Rules

.PHONY: clean reset iso boot

all: link
	
assemble: $(ASRC)
	$(AS) $(AFLAGS) $(ASRC)

compile: $(CSRC)
	$(CC) -c $(CSRC) $(DEPS) $(CFLAGS)
	
link: assemble compile
	$(CC) -T $(LDSRC) -o ./bin/$(TARGET).bin $(LDFLAGS) $(OBJ)

iso: all
	mkdir ./tmp
	mkdir ./tmp/boot
	cp -R platform/x86/boot/grub tmp/boot/grub
	cp ./bin/$(TARGET).bin ./tmp/boot/$(TARGET).bin
	grub-mkrescue -o $(IMAGE) tmp
	rm -rf ./tmp

boot: iso clean
	@echo "qemu-system-i386 -m 64M -cdrom $(IMAGE) -serial mon:stdio"
	@echo "Boot Emulation Starting..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@qemu-system-i386 -m 64M -cdrom $(IMAGE) -serial mon:stdio

clean:
	rm -rf $(OBJ)
	
reset: clean
	rm -rf $(IMAGE) ./bin/$(TARGET).bin ./boot/$(TARGET).bin

