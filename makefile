CFLAGS=-Wall -Wextra -pedantic -std=c11 -O3
CC=gcc

BIN=bin

clean:
	rm -rf $(BIN)

compile:
	mkdir -p $(BIN)
	$(CC) -o $(BIN)/passwdgen src/main.c $(CFLAGS)

compile-debug: CFLAGS += -g
compile-debug: compile

install:
	sudo cp $(BIN)/passwdgen /usr/bin/

uninstall:
	sudo rm $(BIN)/passwdgen
