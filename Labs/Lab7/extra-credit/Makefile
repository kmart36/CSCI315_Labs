
CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS = dlisttest alloc-dlist_test memory-test

all: $(EXECS)

doc:
	doxygen

$(OBJ)/dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o $(OBJ)/dnode.o

$(OBJ)/dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o $(OBJ)/dlist.o

$(OBJ)/allocator.o: dlist.h allocator.h dnode.h allocator.c
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o $(OBJ)/allocator.o

dlisttest: $(SRC)/dlisttest.c $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/dlisttest.c -o $(BIN)/dlisttest

alloc-dlist_test: $(SRC)/alloc-dlist_test.c $(OBJ)/dnode.o $(OBJ)/dlist.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(SRC)/alloc-dlist_test.c -o $(BIN)/alloc-dlist_test

memory-test: $(SRC)/memory-test.c $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o
	$(CC) $(CFLAGS) $(OBJ)/dnode.o $(OBJ)/dlist.o $(OBJ)/allocator.o $(SRC)/memory-test.c -o $(BIN)/memory-test

.PHONY: clean
clean:
	/bin/rm -rf $(BIN)/* $(OBJ)/* core* $(SRC)/*~ *~

