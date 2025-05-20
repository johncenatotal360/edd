CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=-lm


SRCS=calc.c

BIN=calc.out

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(BIN)
