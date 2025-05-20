CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=-lm


SRCS=main.c arithmetic.c trignometry.c
OBJ=main.o arithmetic.o trignometry.o
BIN=calc.out

all: $(BIN)

%.o: %.c:
	$(CC) $(CFLAGS) $^ -c -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^  $(LDFLAGS) -o $@

clean:
	rm -rf $(BIN) $(OBJ)
