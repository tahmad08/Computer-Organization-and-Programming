CC = gcc
CHECK_LIBS = $(shell pkg-config --cflags --libs check)
CFILES = $(wildcard tester/*.c) $(wildcard images/*.c) $(wildcard *.c)
HFILES = $(wildcard tester/*.h) $(wildcard images/*.h) $(wildcard *.h)
OFILES = $(patsubst %.c,%.o,$(CFILES))

CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g \
         -Wstrict-prototypes -Wold-style-definition

.PHONY: default run-tests run-gdb run-valgrind run-sandbox run-sandbox-gdb clean

default: run-tests

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

# Autograder

tests: $(filter-out sandbox.o,$(OFILES))
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_LIBS)

run-tests: tests
	./tests $(TEST)

run-gdb: tests
	CK_FORK=no gdb --args ./tests $(TEST)

# To prevent leak false postives, tell check not to fork.
# See: http://check.sourceforge.net/doc/check_html/check_4.html#Finding-Memory-Leaks
run-valgrind: tests
	CK_FORK=no valgrind --quiet --leak-check=full --error-exitcode=1 --show-leak-kinds=all --errors-for-leak-kinds=all ./tests $(TEST)

# Sandbox

sandbox: $(filter-out %/tests.o %_suite.o,$(OFILES))
	$(CC) $(CFLAGS) -o $@ $^

run-sandbox: sandbox
	./sandbox
	@echo "Sandbox output generated in output.bmp"

run-sandbox-gdb: sandbox
	gdb ./sandbox

clean:
	rm -rf sandbox tests tester/diff/*.bmp tester/actual/*.bmp $(OFILES)
