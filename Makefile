### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
ASM=nasm
CC=i686-elf-gcc
CFLAGS=-I./include/ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fstrength-reduce -fomit-frame-pointer -Wno-uninitialized
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc
ASMFLAGS=-felf32
ASRC=./ldr/bootloader.asm
CSRC=kernel.c
DEPS=$(wildcard ./kernel/*.c)
LDSRC=linker.ld 
OBJA=./ldr/bootloader.o
OBJC=$(wildcard ./*.o)
TARGET=./bin/kernel.bin
IMAGE=powerkernel.iso

# Build Rules

.PHONY: clean

assemble: $(ASRC)
	$(ASM) $(ASMFLAGS) $(ASRC) -o $(OBJA)

compile: $(CSRC)
	$(CC) -c $(CSRC) $(DEPS) $(CFLAGS)
	
link: assemble compile
	$(CC) -T $(LDSRC) -o $(TARGET) $(LDFLAGS) $(OBJA) $(OBJC)
	
iso: link clean
	cp $(TARGET) ./iso/boot/kernel.bin 
	grub-mkrescue -o $(IMAGE) iso

all: assemble compile link clean

boot: iso clean
	qemu-system-i386 -m 64M -cdrom $(IMAGE)

clean:
	rm -rf $(OBJA) $(OBJC)
	
reset: clean
	rm -rf $(IMAGE) $(TARGET) ./iso/boot/kernel.bin 

