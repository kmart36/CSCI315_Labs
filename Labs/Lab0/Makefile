CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXECS = dlisttest

all: $(EXECS)

dnode.o: dnode.c dnode.h
	$(CC) $(CFLAGS) -c dnode.c 

dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c dlist.c 

dlisttest: dlisttest.c dnode.o dlist.o
	$(CC) $(CFLAGS) -o dlisttest dnode.o dlist.o dlisttest.c

.PHONY: clean
clean:
	/bin/rm -rf $(EXECS) dnode.o dlist.o

