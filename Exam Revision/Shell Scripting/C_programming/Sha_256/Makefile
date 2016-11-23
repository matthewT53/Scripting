CC=gcc
CFLAGS=-c

all: sha

sha: driver.o sha_256.o
	$(CC) driver.o sha_256.o -o sha

driver.o: driver.c
	$(CC) $(CFLAGS) driver.c

sha_256.o: sha_256.c
	$(CC) $(CFLAGS) sha_256.c

clean:
	rm -f *.o sha
