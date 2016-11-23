CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: rb

rb: rb.o rbUser.o
	$(CC) rb.o rbUser.o -o rb

rb.o: rb.c
	$(CC) $(CFLAGS) rb.c

rbUser.o: rbUser.c
	$(CC) $(CFLAGS) rbUser.c

clean:
	rm -f *.o rb
