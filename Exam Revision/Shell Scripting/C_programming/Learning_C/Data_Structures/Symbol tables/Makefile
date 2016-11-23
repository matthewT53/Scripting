CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: symTable

symTable: symTableUser.o symTable.o
	$(CC) symTableUser.o symTable.o -o sym

symTableUser.o: symTableUser.c
	$(CC) $(CFLAGS) symTableUser.c

symTable.o: symTable.c
	$(CC) $(CFLAGS) symTable.c

clean:
	rm -f *.o sym
