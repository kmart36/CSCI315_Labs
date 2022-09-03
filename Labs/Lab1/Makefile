CC = gcc
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

EXEC = catcount fork-file fork-data myprog cmds cmdreverse fork fork-wait

all: $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

myprog: myprog.o
	$(CC) $(CFLAGS) -o $@ myprog.o

cmds: cmds.o
	$(CC) $(CFLAGS) -o $@ cmds.o

cmdreverse: cmdreverse.o
	$(CC) $(CFLAGS) -o $@ cmdreverse.o

fork: fork.o
	$(CC) $(CFLAGS) -o $@ fork.o

fork-wait: fork-wait.o
	$(CC) $(CFLAGS) -o $@ fork-wait.o

fork-data: fork-data.o
	$(CC) $(CFLAGS) -o $@ fork-data.o

fork-file: fork-file.o
	$(CC) $(CFLAGS) -o $@ fork-file.o

catcount: catcount.o
	$(CC) $(CFLAGS) -o $@ catcount.o
clean:
	/bin/rm -rf core $(EXEC) *~ *.o data.txt

