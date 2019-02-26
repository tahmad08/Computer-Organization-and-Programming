#include "../binary_search_tree.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define tcase_hack(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(STRINGIFY(func)); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(s, tc); \
}

bst_node *_bst_add(bst_node *currNode, int data);
int _bst_contains(bst_node *currNode, int data);
void _bst_destroy(bst_node *currNode);

