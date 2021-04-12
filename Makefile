CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic

main: main.o
	$(CC) $(CFLAGS) main.o

main.o: main.c
	@echo "Compiling main.c ..."
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o *.out
