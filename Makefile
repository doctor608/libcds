CC = gcc
CFLAGS = -W -Wall -Wextra

default: test_arraylist

arraylist.o: arraylist.c
	$(CC) -c $(CFLAGS) $^

test_arraylist: test_arraylist.c arraylist.o
	$(CC) $(CFLAGS) $^ -o $@
