CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic -std=c99

server: main.o
	$(CC) $(CFLAGS) main.o -o server.out

client: client.o
	$(CC) $(CFLAGS) client.o -o client.out

client.o: client.c
	$(CC) $(CFLAGS) -c client.c
main.o: main.c
	@echo "Compiling main.c ..."
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o *.out
