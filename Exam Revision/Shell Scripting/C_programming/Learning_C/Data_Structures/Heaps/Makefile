CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: heap

heap: heap.o heapUser.o
	$(CC) heap.o heapUser.o -o heap

heap.o: heap.c
	$(CC) $(CFLAGS) heap.c

heapUser.o: heapUser.c
	$(CC) $(CFLAGS) heapUser.c

clean:
	rm -f *.o heap
