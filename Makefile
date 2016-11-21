CC=gcc
CFLAGS=-I.
DEPS = 2048.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o 2048.o
	$(CC) -o main main.o 2048.o -I.
