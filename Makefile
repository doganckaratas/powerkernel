### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
ASM=nasm
CC=i686-elf-gcc
CFLAGS=-I./lib/ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fstrength-reduce -fomit-frame-pointer -Wno-uninitialized
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc
ASMFLAGS=-felf32
ASRC=./ldr/bootloader.asm
CSRC=kernel.c
DEPS=./lib/io.c ./lib/string.c ./lib/tty.c
LDSRC=linker.ld 
OBJA=./ldr/bootloader.o
OBJC=kernel.o io.o string.o tty.o
TARGET=./bin/kernel.bin
IMAGE=powerkernel.iso

# Build Rules
.PHONY: clean

all: assemble compile link clean

assemble: $(ASRC)
	$(ASM) $(ASMFLAGS) $(ASRC) -o $(OBJA)

compile: $(CSRC)
	$(CC) -c $(CSRC) $(DEPS) $(CFLAGS)
	
link: compile assemble
	$(CC) -T $(LDSRC) -o $(TARGET) $(LDFLAGS) $(OBJA) $(OBJC)
	
iso: link clean
	cp $(TARGET) ./iso/boot/kernel.bin 
	grub-mkrescue -o $(IMAGE) iso

boot: iso clean
	qemu-system-i386 -m 64M -cdrom $(IMAGE)

clean:
	rm -rf $(OBJA) $(OBJC)
	
reset: clean
	rm -rf $(IMAGE) $(TARGET) ./iso/boot/kernel.bin 
	