CC=gcc
CFLAGS=-I.
DEPS = minimax_solver.h 2048.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o 2048.o minimax_solver.o
	$(CC) -o main main.o minimax_solver.o 2048.o -I.
clean:
	rm main *.o *~
