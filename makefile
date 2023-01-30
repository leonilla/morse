CC=gcc
CFLAGS=-ansi -pedantic -Wall -Wextra
DEPS= include/*

%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

morse: files.o morse.o main.o
	$(CC) -o morse files.o morse.o main.o
