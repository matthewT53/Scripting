CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: sort

sort: sort.o sortUser.o
	$(CC) sort.o sortUser.o -o sort

sort.o: sort.c
	$(CC) $(CFLAGS) sort.c

sortUser.o: sortUser.c
	$(CC) $(CFLAGS) sortUser.c

clean:
	rm -f *.o sort
