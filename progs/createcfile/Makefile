CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=

SRCS=createFile.c

BIN=a.out

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -rf $(BIN)
