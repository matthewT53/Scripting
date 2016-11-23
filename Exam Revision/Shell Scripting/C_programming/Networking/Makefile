CC=gcc
CFLAGS=-c
CFLAGS2=-c

all: server client

server: myserver.o server.o sha_256.o
	$(CC) myserver.o server.o sha_256.o -o server -lpthread

myserver.o: myserver.c
	$(CC) $(CFLAGS) myserver.c

server.o: server.c
	$(CC) $(CFLAGS) server.c

client: myclient.o client.o
	$(CC) myclient.o client.o sha_256.o -o client

myclient.o: myclient.c
	$(CC) $(CFLAGS2) myclient.c

client.o: client.c
	$(CC) $(CFLAGS2) client.c

sha_256.o: sha_256.c
	$(CC) $(CFLAGS) sha_256.c

clean: 
	rm -f *.o server client
