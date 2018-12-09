# Platform

CC = i686-elf-gcc
MAKE = make


.PHONY: all
all:
	$(MAKE) -C $(ARCH) all
	$(MAKE) -C $(ARCH)/boot all

.PHONY: iso
iso:
	ifeq($(ARCH), x86)
		cp -R $(ARCH)/boot/grub ../tmp/boot/grub
	endif

.PHONY: clean
clean:
	$(MAKE) -C $(ARCH) clean
	$(MAKE) -C $(ARCH)/boot clean
