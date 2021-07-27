# This Makefile is set up for CS201 A4
# NOTE: All indented lines are indented with a tab character.
#       This is required.

CC=gcc
# compile for 32-bit rather than 64-bit
CFLAGS=-O0
DFLAGS=-g
PROGS=calc
LDLIBS=-lm

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(PROGS) *.o ~* 

