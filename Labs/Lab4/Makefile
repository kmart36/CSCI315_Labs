CC = gcc
CFLAGS = -std=gnu99 -Wall -g -lpthread #-DDEBUG

EXEC = echod echoreq echoreq2

all: $(EXEC)

wrapper.o: wrapper.c wrapper.h
	$(CC) $(CFLAGS) -c wrapper.c -o wrapper.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	/bin/rm -rf core $(EXEC) *~ *.o 

