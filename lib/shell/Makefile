# Makefile for SmSH - the Smith Shell
# modeled by Nathanael A. Smith after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

# our binary output directory
BIN_DIR=../../bin

shell: shell.o cd.o
	$(CC) -o $(BIN_DIR)/$@ $<

shell.o: shell.h shell.c

cd.o: shell.h cd.c

clean: 
	rm *.o $(BIN_DIR)/*
