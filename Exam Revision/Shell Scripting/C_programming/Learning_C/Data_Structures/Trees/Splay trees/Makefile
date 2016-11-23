CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: splay

splay: splay.o splayUser.o queue.o
	$(CC) splay.o splayUser.o queue.o -o splay

splay.o: splay.c
	$(CC) $(CFLAGS) splay.c

splayUser.o: splayUser.c
	$(CC) $(CFLAGS) splayUser.c

queue.o: queue.c
	$(CC) $(CFLAGS) queue.c

clean: 
	rm -f *.o splay 
