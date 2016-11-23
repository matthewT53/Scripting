CC=gcc
CFLAGS=-Wall -Werror -std=c99 -c

all: graph

graph: graphUser.o graph.o priorityQueue.o queue.o stack.o
	$(CC) graphUser.o graph.o priorityQueue.o queue.o stack.o -o graph

graphUser.o: graphUser.c
	$(CC) $(CFLAGS) graphUser.c

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c

priorityQueue.o: priorityQueue.c
	$(CC) $(CFLAGS) priorityQueue.c

queue.o: queue.c
	$(CC) $(CFLAGS) queue.c

stack.o: stack.c
	$(CC) $(CFLAGS) stack.c

clean:
	rm -f *.o
