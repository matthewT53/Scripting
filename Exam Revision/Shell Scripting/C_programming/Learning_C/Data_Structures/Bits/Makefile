CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c
LIBS=-lm

all: bitmap

bitmap: bitmap.o setUser.o
	$(CC) bitmap.o setUser.o -o set -lm

bitmap.o: bitmap.c
	$(CC) $(CFLAGS) bitmap.c 

setUser.o: setUser.c
	$(CC) $(CFLAGS) setUser.c

clean: 
	rm -f *.o set

