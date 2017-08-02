### PowerKernel 
### 2011 - 2017 -- Doğan Can Karataş
### Son Değişiklik - 08/2017 - v0rev3

# Tools and Definitions
ASM=nasm
CC=i686-elf-gcc
CFLAGS=-I./lib/ -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fstrength-reduce -fomit-frame-pointer -Wno-uninitialized
LDFLAGS=-ffreestanding -O2 -nostdlib -lgcc
ASMFLAGS=-felf32
ASRC=./ldr/bootloader.asm
CSRC=kernel.c
LDSRC=linker.ld 
OBJA=./ldr/bootloader.o
OBJC=kernel.o
TARGET=./bin/kernel.bin
IMAGE=powerkernel.iso

# Build Rules

all: assemble compile link clean

.PHONY: clean

assemble: $(ASRC)
	$(ASM) $(ASMFLAGS) $(ASRC) -o $(OBJA)

compile: $(CSRC)
	$(CC) -c $(CSRC) -o $(OBJC) $(CFLAGS)
	
link: compile assemble
	$(CC) -T $(LDSRC) -o $(TARGET) $(LDFLAGS) $(OBJA) $(OBJC)
	
iso: link
	cp $(TARGET) ./iso/boot/kernel.bin 
	grub-mkrescue -o $(IMAGE) iso

run: iso
	qemu-system-i386 -m 64M -cdrom $(IMAGE)

clean:
	rm -rf $(OBJA) $(OBJC)


