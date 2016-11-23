CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: ht

ht: ht.o htuser.o
	$(CC) ht.o htuser.o -o ht

ht.o: ht.c
	$(CC) $(CFLAGS) ht.c
htuser.o: htuser.c
	$(CC) $(CFLAGS) htuser.c

clean:
	rm -f *.o ht 
