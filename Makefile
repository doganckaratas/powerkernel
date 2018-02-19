### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
TARGET	= kernel
AS	= nasm
CC	= i686-elf-gcc
CFLAGS	= -I./include/x86 -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fstrength-reduce -fomit-frame-pointer -Wno-uninitialized -masm=intel
LDFLAGS	= -ffreestanding -O2 -nostdlib -m32
AFLAGS	= -felf
ASRC	= ./loader/x86/bootloader.asm
CSRC	= ./kernel/$(TARGET).c
CSRC	+= $(wildcard ./kernel/x86/*.c)
LDSRC	= ./kernel/linker.ld 
OBJ	= $(shell find './' -name '*.o')
IMAGE	= powerkernel.iso

# Build Rules

.PHONY: clean reset

all: link
	
assemble: $(ASRC)
	$(AS) $(AFLAGS) $(ASRC)

compile: $(CSRC)
	$(CC) -c $(CSRC) $(DEPS) $(CFLAGS)
	
link: assemble compile
	$(CC) -T $(LDSRC) -o ./bin/$(TARGET).bin $(LDFLAGS) $(OBJ)

iso: all
	cp ./bin/$(TARGET).bin ./iso/boot/kernel.bin 
	grub-mkrescue -o $(IMAGE) iso

boot: iso clean
	qemu-system-i386 -m 64M -cdrom $(IMAGE) -monitor stdio 

clean:
	rm -rf $(OBJ)
	
reset: clean
	rm -rf $(IMAGE) ./bin/$(TARGET).bin ./iso/boot/$(TARGET).bin

