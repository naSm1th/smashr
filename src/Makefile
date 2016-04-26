# Makefile for all libraries
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-Wall

BIN_DIR=../bin
LIBS_DIR=../lib

all: smashr smashd

smashr: smashr.o
	$(CC) -o $(BIN_DIR)/smashr smashr.o $(LIBS_DIR)/simple-socket/client.o

smashd: smashd.o
	$(CC) -o $(BIN_DIR)/smashd smashd.o $(LIBS_DIR)/simple-socket/server.o

smashr.o: smashr.c

smashd.o: smashd.c

clean:
	rm -rf *.o
