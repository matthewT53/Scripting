CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c 

all: 2-3-4

2-3-4: 2-3-4.o 2-3-4_user.o
	$(CC) 2-3-4.o 2-3-4_user.o -o funTree

2-3-4.o: 2-3-4.c
	$(CC) $(CFLAGS) 2-3-4.c

2-3-4_user.o: 2-3-4_user.c
	$(CC) $(CFLAGS) 2-3-4_user.c

clean:
	rm -f *.o funTree
