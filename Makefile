### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
ASM=nasm
CC=i686-elf-gcc
CFLAGS=-I./include/ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fstrength-reduce -fomit-frame-pointer -Wno-uninitialized
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc
ASMFLAGS=-felf32
ASRC=./loader/bootloader.asm
CSRC=kernel.c
DEPS=$(wildcard ./kernel/*.c)
LDSRC=linker.ld 
OBJ=$(shell find './' -name '*.o')
TARGET=./bin/kernel.bin
IMAGE=powerkernel.iso

# Build Rules

.PHONY: clean

assemble: $(ASRC)
	$(ASM) $(ASMFLAGS) $(ASRC)

compile: $(CSRC)
	$(CC) -c $(CSRC) $(DEPS) $(CFLAGS)
	
link: assemble compile
	$(CC) -T $(LDSRC) -o $(TARGET) $(LDFLAGS) $(OBJ)

all: link
	
iso: all
	cp $(TARGET) ./iso/boot/kernel.bin 
	grub-mkrescue -o $(IMAGE) iso

boot: iso clean
	qemu-system-i386 -m 64M -cdrom $(IMAGE)

clean:
	rm -rf $(OBJ)
	
reset: clean
	rm -rf $(IMAGE) $(TARGET) ./iso/boot/kernel.bin ./tmp/*

