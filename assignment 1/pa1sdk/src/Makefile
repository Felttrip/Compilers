PROGRAM = pa1
CFILES = frontend.c
YFILE =
LFILE = lexer.l

CC = gcc
CFLAGS = -Wall
LDLIBS =
LEX = flex
YACC = bison

YFLAGS =
LFLAGS =

$(PROGRAM): $(YFILE:.y=.o) $(LFILE:.l=.o) $(CFILES:.c=.o)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	-rm $(YFILE:.y=.o) $(YFILE:.y=.c)
	-rm $(LFILE:.l=.o) $(LFILE:.l=.c)
	-rm $(CFILES:.c=.o)
	-rm $(PROGRAM)
