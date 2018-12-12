# Platform = x86-32

CC	= i686-elf-gcc
MAKE	= make
CFLAGS	= -I./include -I../../kernel/include -std=gnu99 -ffreestanding -O0 -Wall
CFLAGS	+= -Werror -Wextra -pedantic -fstrength-reduce -fomit-frame-pointer
CFLAGS	+= -Wno-uninitialized -masm=intel

SRC 	= io.c \
	  serial.c

OBJ	= $(SRC:.c=.o)
DEP	= $(OBJ:.o=.d)

.PHONY: all
all: $(OBJ)
	$(MAKE) -C boot all

$(DEP): %.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^

-include $(DEP)

.PHONY: clean
clean:
	$(MAKE) -C boot clean
	rm -rf $(OBJ) $(DEP)
