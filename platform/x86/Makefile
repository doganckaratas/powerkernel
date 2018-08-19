# Platform = x86-32

CC = i686-elf-gcc
MAKE = make
CFLAGS = -I./include -I../../src/include -std=gnu99 -ffreestanding -O0 -Wall 
CFLAGS += -Werror -Wextra -pedantic -fstrength-reduce -fomit-frame-pointer 
CFLAGS += -Wno-uninitialized -masm=intel

SRC_X86 = $(wildcard *.c)
OBJ_X86 = $(SRC_X86:.c=.o)
DEP_X86 = $(OBJ_X86:.o=.d)

.PHONY: all
all: $(OBJ_X86)
	$(MAKE) -C boot all

$(DEP_X86): %.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(OBJ_X86): $(SRC_X86)
	$(CC) $(CFLAGS) -c $^

-include $(DEP_X86)

.PHONY: clean
clean:
	$(MAKE) -C boot clean
	rm -rf $(OBJ_X86) $(DEP_X86)
