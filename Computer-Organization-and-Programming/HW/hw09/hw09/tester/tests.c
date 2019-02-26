#include <check.h>
#include <stdio.h>
#include "graphics_suite.h"

void print_usage(char *progname) {
    fprintf(stderr, "usage: %s [<testcase> [logfile]]\n", progname);
}

int main(int argc, char **argv) {
    char *testcase = NULL;
    char *logfile = NULL;

    if (argc-1 > 2) {
        print_usage(argv[0]);
        return 1;
    } else {
        if (argc-1 >= 1) {
            testcase = argv[1];
        }
        if (argc-1 >= 2) {
            logfile = argv[2];
        }
    }

    Suite *s = graphics_suite();

    if (testcase && !suite_tcase(s, testcase)) {
        print_usage(argv[0]);
        fprintf(stderr, "\n%s: error: `%s' is not a test case\n", argv[0], testcase);
        return 2;
    }

    SRunner *sr = srunner_create(s);
    if (logfile)
        srunner_set_log(sr, logfile);
    srunner_run(sr, NULL, testcase, CK_VERBOSE);
    srunner_free(sr);
    return 0;
}
