CC = gcc
CFLAGS = -std=gnu99 -Wall -g -lpthread -lm #-DDEBUG

EXEC := $(basename $(wildcard *.c))

all: $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	/bin/rm -rf core $(EXEC) *~ *.o 

