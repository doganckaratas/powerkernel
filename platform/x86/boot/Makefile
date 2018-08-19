# Platform = x86-32

CC = nasm
CFLAGS = -felf

SRC_X86 = $(wildcard *.asm)
OBJ_X86 = $(SRC_X86:.asm=.o)

.PHONY: all
all: $(OBJ_X86)

$(OBJ_X86): $(SRC_X86)
	$(CC) $(CFLAGS) $^

.PHONY: clean
clean:
	rm -rf $(OBJ_X86)
