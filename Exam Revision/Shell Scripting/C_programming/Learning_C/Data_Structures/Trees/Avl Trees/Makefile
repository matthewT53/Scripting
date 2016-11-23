CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c
LIBS=-lm

all: avl

avl: avl.o avluser.o queue.o
	$(CC) avl.o avluser.o queue.o -o avl

avl.o: avl.c
	$(CC) $(CFLAGS) avl.c 
avluser.o: avluser.c
	$(CC) $(CFLAGS) avluser.c
queue.o: queue.c
	$(CC) $(CFLAGS) queue.c

clean:
	rm -f *.o avl
