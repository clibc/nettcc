CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic

main: main.o
	$(CC) $(CFLAGS) main.o

clean:
	rm -f *.o
