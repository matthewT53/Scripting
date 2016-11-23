CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: tries

tries: tries.o triesUser.o
	$(CC) tries.o triesUser.o -o tries

tries.o: tries.c
	$(CC) $(CFLAGS) tries.c

triesUser.o: triesUser.c
	$(CC) $(CFLAGS) triesUser.c

clean:
	rm -f *.o tries
