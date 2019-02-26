CC = gcc
CHECK_LIBS = $(shell pkg-config --cflags --libs check)
SNEAKYBOI = suites/test_utils.c
OSNEAKYBOI = $(patsubst %.c,%.o,$(SNEAKYBOI))
CFILES = tests.c list.c person.c \
         $(filter-out $(SNEAKYBOI),$(wildcard suites/*.c))
HFILES = list.h person.h $(wildcard suites/*.h)
OFILES = $(patsubst %.c,%.o,$(CFILES)) $(OSNEAKYBOI)

CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra -g \
         -Wstrict-prototypes -Wold-style-definition

.PHONY: default run-tests run-gdb run-valgrind clean ta-clean

default: run-tests

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

list.o: list.c $(HFILES)
	$(CC) $(CFLAGS) -include suites/fakemalloc.h -c $< -o $@

-include sneakyboi.mak

tests: $(OFILES)
	./verify.sh
	$(CC) $(CFLAGS) $^ -o $@ $(CHECK_LIBS)

run-tests: tests
	./tests $(TEST)

run-gdb: tests
	CK_FORK=no gdb --args ./tests $(TEST)

# To prevent leak false postives, tell check not to fork.
# See: http://check.sourceforge.net/doc/check_html/check_4.html#Finding-Memory-Leaks
run-valgrind: tests
	CK_FORK=no valgrind --quiet --leak-check=full --error-exitcode=1 --show-leak-kinds=all --errors-for-leak-kinds=all ./tests $(TEST)

clean:
	rm -rf tests $(filter-out $(OSNEAKYBOI),$(OFILES))

submit:
	tar -czvf submission.tar.gz list.c
