CC = gcc
CFLAGS = -std=gnu99 -Wall -g -lreadline #-DDEBUG

EXEC = tokens upper pipes pipe-test heap-test

all: $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o
	$(CC) $(CFLAGS) -o $@ $<

clean:
	/bin/rm -rf core $(EXEC) *~ *.o 

