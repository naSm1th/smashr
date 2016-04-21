# Makefile for all libraries
# modeled by Nathanael A. Smith/Austin Burdine after Dr. Vail's Makefile
# also modeled after an example at http://mrbook.org/blog/tutorials/make


# our C compiler
CC=gcc
# the C compiler flags
CFLAGS=-c -Wall

SIMPLESOCKET_DIR = simple-socket
SHELL_DIR = shell

.PHONY: simple-socket
.PHONY: shell

all: simple-socket shell

shell:
	$(MAKE) -C $(SIMPLESOCKET_DIR) 
	$(MAKE) -C $(SHELL_DIR)

clean:
	$(MAKE) -C $(SIMPLESOCKET_DIR) clean
	$(MAKE) -C $(SHELL_DIR) clean
