CFLAGS=-g -Wall -Wextra -pedantic -Wformat=2 -Wextra
c:
	mkdir -p bin/
	gcc -o bin/passwdgen src/main.c $(CFLAGS)
r:
	bin/passwdgen
install: c
	sudo cp bin/passwdgen /usr/bin/
uninstall:
	sudo rm bin/passwdgen
cr:c r
