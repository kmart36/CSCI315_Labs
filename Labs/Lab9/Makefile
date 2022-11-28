CC = gcc
CFLAGS = -std=gnu99 -Wall -g -lpthread -lreadline #-DDEBUG

EXEC = ishell

all: $(EXEC)

wrapper.o: wrapper.c wrapper.h
	$(CC) $(CFLAGS) -c wrapper.c -o wrapper.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	/bin/rm -rf core $(EXEC) *~ *.o 

