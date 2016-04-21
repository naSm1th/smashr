# Makefile for all libraries
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

all: smashr smashd

smashr: smashr.o
	$(CC) -o $(BIN_DIR)/smashr smashr.o

smashd: smashd.o
	$(CC) -o $(BIN_DIR)/smashd smashr.o

smashr.o: smashr.c smashr.h

smashd.o: smashd.c smashd.h

clean:
	rm -rf *.o
