CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: bstUser.o bst.o
	$(CC) bstUser.o bst.o -o bst

bstUser.o: bstUser.c
	$(CC) $(CFLAGS) bstUser.c

bst.o: bst.c
	$(CC) $(CFLAGS) bst.c

clean:
	rm -f *.o bst
