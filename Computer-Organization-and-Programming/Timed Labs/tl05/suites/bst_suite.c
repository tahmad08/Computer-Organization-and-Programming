// Timed lab 5 tests
// Structure by Austin, actual work by Jim and Sanjay (RIP)
//
// Warning: much the structure of this file is shamelessly copypasted from
// https://libcheck.github.io/check/doc/check_html/check_3.html

#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;
int malloc_counter = 0;

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static struct bst_node *create_large_tree(void) {
    struct bst_node *root = _bst_add(NULL, 5);
    _bst_add(root, 2);
    _bst_add(root, 4);
    _bst_add(root, 8);
    _bst_add(root, 6);
    return root;
}


/******************************************************************************/
/************************** bst_add() tests ***************************************/
/******************************************************************************/
START_TEST(test_bst_add_left_simple) {
    struct bst_node *b1 = _bst_add(NULL, 5);
    bst_add(b1, 4);
    ck_assert_int_eq(b1->left->data, 4);
    _bst_destroy(b1);
}
END_TEST

START_TEST(test_bst_add_simple_malloc_fail) {
    malloc_counter = 0;
    mallocs_until_fail = 0;
    struct bst_node *b1 = bst_add(NULL, -1);
    ck_assert(!b1);
    ck_assert(malloc_counter != 0);
}
END_TEST


START_TEST(test_bst_add_already_in_tree) {
    malloc_counter = 0;
    struct bst_node *b1 = _bst_add(NULL, 5);
    bst_add(b1, 5);
    ck_assert_int_eq(b1->data, 5);
    ck_assert(!(b1->right));
    ck_assert(!(b1->left));
    ck_assert(malloc_counter == 0);
    _bst_destroy(b1);
}
END_TEST

START_TEST(test_bst_add_left_large_tree) {
    struct bst_node *b1 = create_large_tree();
    bst_add(b1, 1);
    ck_assert_int_eq(b1->left->left->data, 1);
    _bst_destroy(b1);
}
END_TEST

START_TEST(test_bst_add_right_large_tree) {
    struct bst_node *b1 = create_large_tree();
    bst_add(b1, 9);
    ck_assert_int_eq(b1->right->right->data, 9);
    _bst_destroy(b1);
}
END_TEST

START_TEST(test_bst_add_large_tree) {
    struct bst_node *b1 = create_large_tree();
    bst_add(b1, 3);
    ck_assert_int_eq(b1->left->right->left->data, 3);
    _bst_destroy(b1);
}
END_TEST

/******************************************************************************/
/************************** bst_contains() tests **********************************/
/******************************************************************************/

START_TEST(test_bst_contains_simple) {
    struct bst_node *b1 = _bst_add(NULL, 5);
    ck_assert_int_eq(bst_contains(b1, 5), 1);
    _bst_destroy(b1);
}
END_TEST

START_TEST(test_bst_contains_simple_fail) {
    struct bst_node *b1 = _bst_add(NULL, 5);
    ck_assert_int_eq(bst_contains(b1, 4), 0);
    _bst_destroy(b1);
}
END_TEST

START_TEST(test_bst_contains_large_tree) {
    struct bst_node *b1 = create_large_tree();
    ck_assert_int_eq(bst_contains(b1, 5), 1);
    ck_assert_int_eq(bst_contains(b1, 2), 1);
    ck_assert_int_eq(bst_contains(b1, 4), 1);
    ck_assert_int_eq(bst_contains(b1, 6), 1);
    ck_assert_int_eq(bst_contains(b1, 8), 1);
    ck_assert_int_eq(bst_contains(b1, 10), 0);
    ck_assert_int_eq(bst_contains(b1, 0), 0);
    ck_assert_int_eq(bst_contains(b1, 3), 0);
    _bst_destroy(b1);
}
END_TEST

/******************************************************************************/
/************************** bst_destroy() tests **********************************/
/******************************************************************************/

START_TEST(test_bst_destroy_null) {
    bst_destroy(NULL);
}
END_TEST

START_TEST(test_bst_destroy_simple) {
    struct bst_node *b1 = _bst_add(NULL, 5);
    bst_destroy(b1);
}
END_TEST

START_TEST(test_bst_destroy_large_tree) {
    struct bst_node *b1 = create_large_tree();
    bst_destroy(b1);
}
END_TEST

Suite *bst_suite(void) {
    Suite *s = suite_create("struct bst");

    // bst_add() tests

    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_add_left_simple);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_add_simple_malloc_fail);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_add_already_in_tree);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_add_left_large_tree);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_add_right_large_tree);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_add_large_tree);

    // bst_contains() tests

    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_contains_simple);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_contains_simple_fail);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_contains_large_tree);

    // bst_destroy() tests

    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_destroy_simple);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_destroy_null);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_bst_destroy_large_tree);

    return s;
}
