# Makefile for a simple echo server
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-Wall

LIBS_DIR = lib
SRC_DIR = src
BIN_DIR = bin

.PHONY: lib
.PHONY: src

all: libs src

libs:
	$(MAKE) -C $(LIBS_DIR)

src:
	$(MAKE) -C $(SRC_DIR)

clean:
	$(MAKE) -C $(LIBS_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean
