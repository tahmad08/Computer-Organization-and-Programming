CC = gcc-5
CHECK_LIBS = $(shell pkg-config --cflags --libs check)
HFILES = graphics.h azul.h qdbmp.h austinbear.h
OFILES = tests.o graphics.o graphics_suite.o azul.o austinbear.o qdbmp.o
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g

.PHONY: default gdb valgrind clean

default: tests

tests: $(OFILES) $(HFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $@ $(CHECK_LIBS)

%.o: %.c $(HFILES)
	$(CC) -c $(CFLAGS) $<

clean:
	rm -f tests *.o
	rm actual/*.bmp
