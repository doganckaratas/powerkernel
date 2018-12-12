# Platform = x86-32

CC	= i686-elf-gcc
MAKE	= make
CFLAGS	= -I./include -I../arch/$(ARCH)/include -std=gnu99 -ffreestanding -O0 -Wall
CFLAGS	+= -Wextra -pedantic -fstrength-reduce -fomit-frame-pointer
CFLAGS	+= -Wno-uninitialized -masm=intel

SRC	+= main.c \
	   string.c

OBJ	= $(SRC:.c=.o)
DEP	= $(OBJ:.o=.d)

.PHONY: all
all: $(OBJ)

$(DEP): %.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^

-include $(DEP)

.PHONY: clean
clean:
	rm -rf $(OBJ) $(DEP)
