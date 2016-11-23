CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: matrix

matrix: matrix.o matrixUser.o
	$(CC) matrix.o matrixUser.o -o mat

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c

matrixUser.o: matrixUser.c
	$(CC) $(CFLAGS) matrixUser.c

clean:
	rm -f *.o mat

