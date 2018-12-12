# Platform = x86-32

CC	= nasm
CFLAGS	= -felf

SRC	= bootloader.asm
OBJ	= $(SRC:.asm=.o)

.PHONY: all
all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $^

.PHONY: clean
clean:
	rm -rf $(OBJ)
