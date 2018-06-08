### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
TARGET	= kernel
AS	= nasm
CC	= i686-elf-gcc
# if platform == x86
CFLAGS	= -I./platform/x86/include -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fstrength-reduce -fomit-frame-pointer -Wno-uninitialized -masm=intel
CFLAGS += -DSERIAL_DEBUG -DSERIAL_1 #debug related
# else ..
LDFLAGS	= -ffreestanding -O2 -nostdlib -m32
AFLAGS	= -felf
# if platform == x86
ASRC	= ./platform/x86/boot/bootloader.asm
# else ...
CSRC	= ./src/$(TARGET).c
# If platform == x86
CSRC	+= $(wildcard ./platform/x86/*.c)
# else ...
LDSRC	= ./src/linker.ld 
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
	qemu-system-i386 -m 64M -cdrom $(IMAGE) -serial mon:stdio

clean:
	rm -rf $(OBJ)
	
reset: clean
	rm -rf $(IMAGE) ./bin/$(TARGET).bin ./boot/$(TARGET).bin

