CFLAGS=-g -Wall -Wextra -pedantic -Wformat=2 -Wextra
c:
	mkdir -p bin/
	gcc -o bin/passwdgen src/main.c src/randint.c $(CFLAGS)
r:
	bin/passwdgen
cr:c r
