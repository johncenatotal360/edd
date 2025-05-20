CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=-lm


SRCS=main.c arithmetic.c trignometry.c
OBJ=main.o arithmetic.o trignometry.o
BIN=calc.out

all: $(BIN)

%.o: %.c
	$(CC) $(CFLAGS) $^ -c 

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)
