#
# Copyright (c) 2012 Bucknell University
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation;
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# Author: L. Felipe Perrone (perrone@bucknell.edu)
#

CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src
OBJ = ./obj
DOC = ./doc
BIN = ./bin

vpath %.h ./include
vpath %.c ./src

EXECS =	adt-test prodcons

all: mkpaths $(EXECS)

mkpaths:
	mkdir -p $(OBJ)

doc:
	doxygen

$(OBJ)/circular-list.o: $(INC)/circular-list.h $(SRC)/circular-list.c 
	$(CC) $(CFLAGS) -c $(SRC)/circular-list.c -o $(OBJ)/circular-list.o

prodcons: $(OBJ)/circular-list.o
	$(CC) $(CFLAGS) $(SRC)/prodcons.c $(OBJ)/circular-list.o -o $(BIN)/prodcons -lpthread

adt-test: $(OBJ)/circular-list.o
	$(CC) $(CFLAGS) $(SRC)/adt-test.c $(OBJ)/circular-list.o -o $(BIN)/adt-test -lpthread

.PHONY: clean
clean:
	/bin/rm -rf $(OBJ) $(EXECS) core* *~ ./src/*~ ./obj/* ./doc

