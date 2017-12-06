c	= new.c String.c Atom.c My_string.c
h	= new.h String.h
m	= strings.c
r	= new.r
t	= strings atoms my_strings

CFLAGS = '-ggdb3'

strings	= strings.o new.o String.o
atoms	= strings.o new.o Atom.o
my_strings = strings.o new.o My_string.o

all:		$t
clean:				; rm -f $t *.o

test::		strings		; strings
test::		atoms		; atoms
test::		my_strings	; my_strings

strings:	$(strings)	; $(CC) $(CFLAGS) -o $@ $(strings)
atoms:		$(atoms)	; $(CC) $(CFLAGS) -o $@ $(atoms)
my_strings:		$(my_strings)	; $(CC) $(CFLAGS) -o $@ $(my_strings)

#include ../make/Makefile.$(OSTYPE)
