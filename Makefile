### PowerKernel 
### (c) 2011 - 2017 
### Doğan Can Karataş -- v0.3


# Tools and Definitions
TARGET	= kernel
CC	= i686-elf-gcc
MAKE	= make
# generic flags
CFLAGS += -I./src/include -g ggdb -O0
# if platform == x86
CFLAGS += -I./platform/x86/include
# else ..
LDFLAGS	= -ffreestanding -O2 -nostdlib -m32
# generic source files
# If platform == x86
OBJ	+= $(shell find './' -name '*.o')
# else ...
LD	= ./platform/x86/x86-32.ld 
IMAGE	= powerkernel.iso

# Build Rules

.PHONY: all
all: link

.PHONY: compile
compile:
	$(MAKE) -C platform/x86 all
	$(MAKE) -C src all

.PHONY: link
link: compile
	$(CC) -T $(LD) -o ./bin/$(TARGET).bin $(LDFLAGS) $(OBJ)

.PHONY: iso
iso: all
	mkdir ./tmp
	mkdir ./tmp/boot
	cp -R platform/x86/boot/grub tmp/boot/grub
	cp ./bin/$(TARGET).bin ./tmp/boot/$(TARGET).bin
	grub-mkrescue -o $(IMAGE) tmp
	rm -rf ./tmp

.PHONY: boot
boot: iso clean
	@echo "qemu-system-i386 -m 64M -cdrom $(IMAGE) -serial mon:stdio"
	@echo "Boot Emulation Starting..."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
	@qemu-system-i386 -m 64M -cdrom $(IMAGE) -serial mon:stdio

.PHONY: clean
clean:
	$(MAKE) -C src clean
	$(MAKE) -C platform/x86 clean
	find . -name '*.gch' -delete

.PHONY: reset
reset: clean
	rm -rf $(IMAGE) ./bin/$(TARGET).bin ./boot/$(TARGET).bin

