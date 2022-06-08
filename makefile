CFLAGS=-Wall -Wextra -pedantic -Wformat=2 -Wextra
compile:
	mkdir -p bin/
	gcc -o bin/passwdgen src/main.c $(CFLAGS)
compile-debug: CFLAGS += -g
compile-debug: compile

run:
	bin/passwdgen
install:
	sudo cp bin/passwdgen /usr/bin/
uninstall:
	sudo rm bin/passwdgen
