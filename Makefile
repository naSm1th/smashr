# Makefile for a simple echo server
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

LIBS_DIR = libs
SRC_DIR = src

.PHONY: libs
.PHONY: src

all: src libs

libs:
	$(MAKE) -C $(LIBS_DIR)

src:
	$(MAKE) -C $(SRC_DIR)

clean:
	$(MAKE) -C $(TESTS_DIR) clean
	$(MAKE) -C $(SRC_DIR) clean
