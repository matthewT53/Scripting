CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: graph

graph: graphUser.o graph.o queue.o stack.o
	$(CC) graphUser.o graph.o queue.o stack.o -o graphUse

graphUser.o: graphUser.c 
	$(CC) $(CFLAGS) graphUser.c

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c

queue.o: queue.c
	$(CC) $(CFLAGS) queue.c
stack.o: stack.c
	$(CC) $(CFLAGS) stack.c

clean: 
	rm -f *.o
