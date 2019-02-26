// Homework 10 Tests, Fall 2018
// Structure by Austin, actual work by Jim and Sanjay (RIP)
//
// Warning: much the structure of this file is shamelessly copypasted from
// https://libcheck.github.io/check/doc/check_html/check_3.html

#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

static struct list *l;

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;

int person_name_is(struct person *person_obj, const char* name) {
    return strcmp(((struct person *)person_obj)->name, name) == 0;
}

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static struct list *_create_length_1_list(void) {
    struct list *shortList = _create_list();
    _push_front(shortList, person_new("jim", "is cool"));
    return shortList;
}

static struct list *_create_longer_list(void) {
    struct list *longerList = _create_list();
    _push_front(longerList, person_new("jim", "is cool"));
    _push_front(longerList, person_new("sanjay", "is cool"));
    _push_front(longerList, person_new("austin", "is cool"));
    return longerList;
}

void teardown_bar_list(void) {
    if (l != NULL) {
        _free_list_nodes_and_data(l, person_free);
        l = NULL;
    }
}

/******************************************************************************/
/*************************** create_list() tests ******************************/
/******************************************************************************/
START_TEST(test_list_create_list_basic) {
    struct list *l1 = create_list();
    ck_assert(l1);
    ck_assert(!l1->size);
    ck_assert(!l1->head);
    ck_assert(!l1->tail);
    free(l1);
}
END_TEST

START_TEST(test_list_create_list_malloc_failure) {
    mallocs_until_fail = 0;
    struct list *l1 = create_list();
    ck_assert(!l1);
}
END_TEST

/******************************************************************************/
/*************************** copy_list() tests ***************************/
/******************************************************************************/
START_TEST(test_list_copy_basic) {
    struct list *l1 = _create_longer_list();

    struct list *l2 = copy_list(l1);

    ck_assert(l2);

    node *current_l1 = l1->head;
    node *current_l2 = l2->head;

    ck_assert(current_l2);

    while (current_l1) {
        ck_assert_int_eq(person_eq(current_l1->data, current_l2->data), 0);
        ck_assert_ptr_ne(current_l1->data, current_l2->data);
        current_l1 = current_l1->next;
        current_l2 = current_l2->next;
    }

    _free_list_nodes_and_data(l1,person_free);
    _free_list_nodes_and_data(l2, person_free);

}
END_TEST

START_TEST(test_list_copy_malloc_failure) {
    struct list *l1 = _create_longer_list();

    mallocs_until_fail = 1;
    struct list *l2 = copy_list(l1);

    ck_assert(!l2);

    _free_list_nodes_and_data(l1, person_free);
}
END_TEST

START_TEST(test_list_copy_null_list) {
    struct list *l1 = copy_list(NULL);
    ck_assert(!l1);
}
END_TEST


/******************************************************************************/
/******************************* front() tests ********************************/
/******************************************************************************/
START_TEST(test_list_front_empty) {
    struct person * outptr;
    struct list *l1 = _create_list();
    ck_assert(!front(l1, &outptr));
    ck_assert(!outptr);
    free(l1);
}
END_TEST
START_TEST(test_list_front_not_empty) {
    struct person * outptr;
    struct list *l1 = _create_list();
    struct person *b0 = person_new("Yeezy", "how ya");
    struct person *b1 = person_new("Yeezy", "doin haaan");

    _push_front(l1, b0);
    _push_front(l1, b1);

    ck_assert(front(l1, &outptr));
    ck_assert_ptr_eq(outptr, b1);

    free(l1->tail);
    free(l1->head);
    free(l1);
    person_free(b0);
    person_free(b1);
}
END_TEST
START_TEST(test_list_front_null) {
    struct list *l1 = _create_longer_list();
    ck_assert(!front(NULL, NULL));
    ck_assert(!front(l1, NULL));
    _free_list_nodes_and_data(l1, person_free);
}
END_TEST
/******************************************************************************/
/******************************** back() tests ********************************/
/******************************************************************************/
START_TEST(test_list_back_empty) {
    struct person * outptr;
    struct list *l1 = _create_list();
    ck_assert(!back(l1, &outptr));
    ck_assert(!outptr);
    free(l1);
}
END_TEST
START_TEST(test_list_back_not_empty) {
    struct person * outptr;
    struct list *l1 = _create_list();
    struct person *b0 = person_new("Yeezy", "how ya");
    struct person *b1 = person_new("Yeezy", "doin haaan");

    _push_front(l1, b0);
    _push_front(l1, b1);

    ck_assert(back(l1, &outptr));
    ck_assert_ptr_eq(outptr, b0);

    free(l1->tail);
    free(l1->head);
    free(l1);
    person_free(b0);
    person_free(b1);
}
END_TEST
START_TEST(test_list_back_null) {
    struct list *l1 = _create_longer_list();
    ck_assert(!back(NULL, NULL));
    ck_assert(!back(l1, NULL));
    _free_list_nodes_and_data(l1, person_free);
}
END_TEST
/******************************************************************************/
/************************** push_front() tests ********************************/
/******************************************************************************/
void setup_list_push_front(void) {
    reset_mallocs_until_fail();
    l = _create_list();
    ck_assert(l);
}

void teardown_list_push_front(void) {
    if (l) {
        free(l);
        l = NULL;
    }
}

START_TEST(test_list_push_front_NULL_list) {
    struct person *b = person_new("Yeezy", "More chips than Pentium");
    ck_assert(!push_front(NULL, b));
    person_free(b);
}
END_TEST

START_TEST(test_list_push_front_NULL_data) {
    ck_assert(push_front(l, NULL));
    ck_assert_int_eq(l->size, 1);
    ck_assert(l->head);
    ck_assert(l->tail);
    ck_assert(!l->head->next);
    ck_assert(!l->tail->next);
    ck_assert(!l->head->data);
    ck_assert(!l->tail->data);

    free(l->head);
}
END_TEST

START_TEST(test_list_push_front_empty) {
    struct person *b = person_new("Yeezy", "Couldn't afford a car, so she named her daughter Alexis");
    ck_assert(push_front(l, b));
    ck_assert_int_eq(l->size, 1);
    ck_assert(l->head);
    ck_assert(l->tail);
    ck_assert(!l->head->next);
    ck_assert(!l->tail->next);
    ck_assert_ptr_eq(l->head->data, b);
    ck_assert_ptr_eq(l->tail->data, b);

    // Don't use empty_list() because we don't want to nail everyone for
    // memory leaks if it's broken
    free(l->head);
    person_free(b);
}
END_TEST

START_TEST(test_list_push_front_nonempty) {
    // Put some stuff in the struct list
    struct person *b0 = person_new("Yeezy", "Work");
    struct person *b1 = person_new("Yeezy", "it");
    struct person *b2 = person_new("Yeezy", "out");
    l->head = _create_node(b0);
    l->head->next = _create_node(b1);
    l->tail = l->head->next->next = _create_node(b2);
    l->size = 3;

    struct person *b3 = person_new("Yeezy", "No dessert");
    ck_assert(push_front(l, b3));
    ck_assert_int_eq(l->size, 4);
    ck_assert(l->head);
    ck_assert(l->tail);
    ck_assert(!l->tail->next);
    ck_assert_ptr_eq(l->head->data, b3);
    ck_assert_ptr_ne(l->tail->data, b3);

    // Don't use empty_list() because we don't want to nail everyone for
    // memory leaks if it's broken
    free(l->head->next->next->next);
    free(l->head->next->next);
    free(l->head->next);
    free(l->head);
    person_free(b0);
    person_free(b1);
    person_free(b2);
    person_free(b3);
}
END_TEST

/******************************************************************************/
/************************** push_back() tests *********************************/
/******************************************************************************/
START_TEST(test_list_push_back_empty) {
    struct list *l1 = _create_list();
    struct person *b0 = person_new("Gucci", "gucci, can I be your main squeeze");
    ck_assert(push_back(l1, b0));
    ck_assert_ptr_eq(l1->head->data, b0);
    ck_assert_ptr_eq(l1->tail->data, b0);
    ck_assert_int_eq(l1->size, 1);
    free(l1->head);
    free(l1);
    person_free(b0);

}
END_TEST
START_TEST(test_list_push_back_non_empty) {
    struct list *l1 = _create_list();
    struct person *b0 = person_new("takeoff", "they think i'm dumb, they don't think I see the plot");
    struct person *b1 = person_new("chris brown", "hundred on my wrist, jumpin out the rari");

    _push_front(l1, b0);

    ck_assert(push_back(l1, b1));
    ck_assert_ptr_eq(b1, l1->tail->data);
    ck_assert_ptr_eq(b0, l1->head->data);
    ck_assert_ptr_eq(l1->tail->data, l1->head->next->data);
    ck_assert_int_eq(l1->size, 2);

    free(l1->head->next);
    free(l1->head);
    person_free(b0);
    person_free(b1);
    free(l1);
}
END_TEST
START_TEST(test_list_push_back_null) {
    struct list *l1 = _create_list();
    struct person *b0 = person_new("kodak black", "snatch your baby girl");
    ck_assert(!push_back(NULL, b0));
    ck_assert(push_back(l1, NULL));
    ck_assert_int_eq(l1->size, 1);
    ck_assert(!l1->tail->data);
    ck_assert(!l1->head->data);

    person_free(b0);
    free(l1->head);
    free(l1);
}
END_TEST


/******************************************************************************/
/************************** add() tests ***************************************/
/******************************************************************************/
START_TEST(test_list_add_out_of_bounds) {
    struct list *l1 = _create_list();
    struct person *b0 = person_new("young thug", "learn how to dress from me");

    ck_assert(!add(l1, -1, b0));

    _push_front(l1, b0);

    ck_assert(!add(l1, 2, b0));

    free(l1->head);
    free(l1);
    person_free(b0);

}
END_TEST

START_TEST(test_list_add_empty_list) {
    struct list *l1 = _create_list();
    struct person *b0 = person_new("bobby shmurda", "shooting is my hobby");
    struct person *b1 = person_new("Ayo", "I just want a rollie rollie rollie and a dab of ranch");

    ck_assert(add(l1,0, b0));
    ck_assert_int_eq(l1->size, 1);
    ck_assert_ptr_eq(l1->head, l1->tail);
    ck_assert_ptr_eq(l1->head->data, b0);

    ck_assert(!add(l1,2, b1));

    ck_assert(add(l1, 1, b1));

    ck_assert_int_eq(l1->size, 2);
    ck_assert_ptr_ne(l1->head, l1->tail);
    ck_assert_ptr_eq(l1->tail->data, b1);


    free(l1->head);
    free(l1->tail);
    free(l1);
    person_free(b0);
    person_free(b1);


}
END_TEST

START_TEST(test_list_add_non_empty_list) {

    struct list *l1 = _create_longer_list();
    struct person *b0 = person_new("gucci", "flying in my rari like a bat that just flew out of hell");
    ck_assert(add(l1,1, b0));
    ck_assert_ptr_eq(l1->head->next->data, b0);
    ck_assert_int_eq(l1->size, 4);

    _free_list_nodes_and_data(l1, person_free);

}
END_TEST

START_TEST(test_list_add_null) {
    struct list *l1 = _create_list();
    struct person *b0 = person_new("gucci", "I'm from the east of A T L but ballin in the Cali hills");

    ck_assert(!add(NULL,0,NULL));

    ck_assert(!add(NULL, 0, b0));

    ck_assert(add(l1, 0, NULL));
    ck_assert_int_eq(l1->size, 1);
    ck_assert(!l1->head->data);
    ck_assert(!l1->tail->data);

    free(l1->head);
    free(l1);
    person_free(b0);
}
END_TEST
/******************************************************************************/
/*************************** pop_front() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_front_NULL_list) {
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    ck_assert(!pop_front(NULL, &dataOut));
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_pop_front_NULL_dataOut) {
    l = _create_list();
    int result = pop_front(l, NULL);
    ck_assert(!result);
}
END_TEST

START_TEST(test_list_pop_front_empty) {
    l = _create_list();
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    int result = pop_front(l, &dataOut);
    ck_assert(!result);
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_pop_front_nonempty) {
    l = _create_length_1_list();
    struct person *jim = NULL;
    int result = pop_front(l, &jim);
    ck_assert(jim);
    int nameCheck = person_name_is(jim, "jim");
    person_free(jim);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_pop_front_longer_list) {
    l = _create_longer_list();
    struct person *data = NULL;
    int result = pop_front(l, &data);
    ck_assert(data);
    int nameCheck = person_name_is(data, "austin");
    person_free(data);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(person_name_is(l->head->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
    result = pop_front(l, &data);
    nameCheck = person_name_is(data, "sanjay");
    person_free(data);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 1);
    ck_assert(person_name_is(l->head->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
}
END_TEST

/******************************************************************************/
/**************************** pop_back() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_back_NULL_list) {
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    ck_assert(!pop_back(NULL, &dataOut));
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_pop_back_NULL_dataOut) {
    l = _create_list();
    int result = pop_back(l, NULL);
    ck_assert(!result);
}
END_TEST

START_TEST(test_list_pop_back_empty) {
    l = _create_list();
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    int result = pop_back(l, &dataOut);
    ck_assert(!result);
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_pop_back_nonempty) {
    l = _create_length_1_list();
    struct person *jim = NULL;
    int result = pop_back(l, (struct person **)&jim);
    ck_assert(jim);
    int nameCheck = person_name_is(jim, "jim");
    person_free(jim);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_pop_back_longer_list) {
    l = _create_longer_list();
    struct person *data = NULL;
    int result = pop_back(l, (struct person **)&data);
    ck_assert(data);
    int name_check = person_name_is(data, "jim");
    person_free(data);
    ck_assert(result);
    ck_assert(name_check);
    ck_assert_int_eq(l->size, 2);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->tail->data, "sanjay"));
    ck_assert(!l->tail->next);
    result = pop_back(l, (struct person **)&data);
    name_check = person_name_is(data, "sanjay");
    person_free(data);
    ck_assert(result);
    ck_assert(name_check);
    ck_assert_int_eq(l->size, 1);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->tail->data, "austin"));
    ck_assert(!l->tail->next);
}
END_TEST

/******************************************************************************/
/**************************** list_remove() tests *****************************/
/******************************************************************************/
START_TEST(test_list_remove_NULL_list) {
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    struct person *a = person_new("a", "b");
    ck_assert(!list_remove(NULL, a, &dataOut));
    ck_assert(!dataOut);
    person_free(a);
}
END_TEST

START_TEST(test_list_remove_NULL_dataOut) {
    l = _create_length_1_list();
    struct person *a = person_new("a", "b");
    int result = list_remove(l, a, NULL);
    ck_assert(!result);
    person_free(a);
}
END_TEST

START_TEST(test_list_remove_front) {
    l = _create_longer_list();
    struct person *dataOut = NULL;
    struct person *austin = person_new("austin", "is cool");
    int result = list_remove(l, austin, &dataOut);
    ck_assert(dataOut);
    int nameCheck = person_name_is(dataOut, "austin");
    person_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(person_name_is(l->head->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
    person_free(austin);
}
END_TEST

START_TEST(test_list_remove_middle) {
    l = _create_longer_list();
    struct person *dataOut = NULL;
    struct person *sanjay = person_new("sanjay", "is cool");
    int result = list_remove(l, sanjay, &dataOut);
    ck_assert(dataOut);
    int nameCheck = person_name_is(dataOut, "sanjay");
    person_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
    person_free(sanjay);
}
END_TEST

START_TEST(test_list_remove_back) {
    l = _create_longer_list();
    struct person *dataOut = NULL;
    struct person *jim = person_new("jim", "is cool");
    int result = list_remove(l, jim, &dataOut);
    ck_assert(dataOut);
    int nameCheck = person_name_is(dataOut, "jim");
    person_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->tail->data, "sanjay"));
    ck_assert(!l->tail->next);
    person_free(jim);
}
END_TEST

START_TEST(test_list_remove_length_1) {
    l = _create_length_1_list();
    struct person *dataOut = NULL;
    struct person *jim = person_new("jim", "is cool");
    int result = list_remove(l, jim, &dataOut);
    ck_assert(dataOut);
    int nameCheck = person_name_is(dataOut, "jim");
    person_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
    person_free(jim);
}
END_TEST

START_TEST(test_list_remove_absent_element) {
    l = _create_length_1_list();
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    struct person *sanjay = person_new("sanjay", "is cool");
    int result = list_remove(l, sanjay, &dataOut);
    ck_assert(!result);
    ck_assert(!dataOut);
    ck_assert_int_eq(l->size, 1);
    person_free(sanjay);
}
END_TEST

/******************************************************************************/
/************************** empty_list() tests ********************************/
/******************************************************************************/
START_TEST(test_list_empty_list_NULL_list) {
    // Success if there is no error
    empty_list(NULL);
}
END_TEST

START_TEST(test_list_empty_list_empty) {
    l = _create_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_empty_list_length_1) {
    l = _create_length_1_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_empty_list_longer_list) {
    l = _create_longer_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

/******************************************************************************/
/***************************** reverse() tests ********************************/
/******************************************************************************/
START_TEST(test_list_reverse_NULL_list) {
    ck_assert(!reverse(NULL));
}
END_TEST

START_TEST(test_list_reverse_empty) {
    l = _create_list();
    ck_assert(reverse(l));
    ck_assert_int_eq(l->size, 0);
    ck_assert(!l->head);
    ck_assert(!l->tail);
}
END_TEST

START_TEST(test_list_reverse_length_1) {
    l = _create_length_1_list();
    ck_assert(reverse(l));
    ck_assert_int_eq(l->size, 1);
    ck_assert(person_name_is(l->head->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->head->next);
    ck_assert(!l->tail->next);
}
END_TEST

START_TEST(test_list_reverse_longer_list) {
    l = _create_longer_list();
    ck_assert(reverse(l));
    ck_assert_int_eq(l->size, 3);
    ck_assert(person_name_is(l->head->data, "jim"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->next->data, "austin"));
    ck_assert(person_name_is(l->tail->data, "austin"));
    ck_assert(!l->tail->next);
}
END_TEST

/******************************************************************************/
/****************************** concat() tests ********************************/
/******************************************************************************/

START_TEST(test_list_concat_NULL_firstList) {
    l = _create_length_1_list();
    int result = concat(NULL, l);
    ck_assert(!result);
    ck_assert(person_name_is(l->head->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
}
END_TEST

START_TEST(test_list_concat_NULL_lastList) {
    l = _create_length_1_list();
    int result = concat(l, NULL);
    ck_assert(!result);
    ck_assert(person_name_is(l->head->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
}
END_TEST

START_TEST(test_list_concat_first_empty) {
    l = _create_list();
    struct list *lastList = _create_longer_list();
    int result = concat(l, lastList);
    ck_assert(result);
    ck_assert_int_eq(l->size,  3);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->next->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
    ck_assert_int_eq(lastList->size, 0);
    ck_assert(!lastList->head);
    ck_assert(!lastList->tail);
    _free_list_nodes(lastList);
}
END_TEST

START_TEST(test_list_concat_second_empty) {
    l = _create_longer_list();
    struct list *lastList = _create_list();
    int result = concat(l, lastList);
    ck_assert(result);
    ck_assert_int_eq(l->size, 3);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->next->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
    ck_assert_int_eq(lastList->size, 0);
    ck_assert(!lastList->head);
    ck_assert(!lastList->tail);
    _free_list_nodes(lastList);
}
END_TEST

START_TEST(test_list_concat_second_length_1) {
    l = _create_longer_list();
    struct list *lastList = _create_length_1_list();
    ((struct person *)lastList->head->data)->name[0] = 'r';
    int result = concat(l, lastList);
    ck_assert(result);
    ck_assert_int_eq(l->size, 4);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->next->data, "jim"));
    ck_assert(person_name_is(l->head->next->next->next->data, "rim"));
    ck_assert(person_name_is(l->tail->data, "rim"));
    ck_assert(!l->tail->next);
    ck_assert_int_eq(lastList->size, 0);
    ck_assert(!lastList->head);
    ck_assert(!lastList->tail);
    _free_list_nodes(lastList);
}
END_TEST

START_TEST(test_list_concat_second_longer) {
    l = _create_longer_list();
    struct list *lastList = _create_longer_list();
    ((struct person *)lastList->head->data)->name[0] = 'r';
    ((struct person *)lastList->head->next->data)->name[0] = 'r';
    ((struct person *)lastList->head->next->next->data)->name[0] = 'r';
    int result = concat(l, lastList);
    ck_assert(result);
    ck_assert_int_eq(l->size, 6);
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->next->data, "jim"));
    ck_assert(person_name_is(l->head->next->next->next->data, "rustin"));
    ck_assert(person_name_is(l->head->next->next->next->next->data, "ranjay"));
    ck_assert(person_name_is(l->head->next->next->next->next->next->data, "rim"));
    ck_assert(person_name_is(l->tail->data, "rim"));
    ck_assert(!l->tail->next);
    ck_assert_int_eq(lastList->size, 0);
    ck_assert(!lastList->head);
    ck_assert(!lastList->tail);
    _free_list_nodes(lastList);
}
END_TEST

/******************************************************************************/
/******************************* get() tests **********************************/
/******************************************************************************/
void checkLongerListUnchanged(void) {
    ck_assert(person_name_is(l->head->data, "austin"));
    ck_assert(person_name_is(l->head->next->data, "sanjay"));
    ck_assert(person_name_is(l->head->next->next->data, "jim"));
    ck_assert(person_name_is(l->tail->data, "jim"));
    ck_assert(!l->tail->next);
}

START_TEST(test_list_get_NULL_list) {
    struct person *b = (struct person *)0xDEADBEEFU;
    ck_assert(!get(NULL, 0, &b));
    ck_assert(!b);
}
END_TEST

START_TEST(test_list_get_NULL_dataOut) {
    l = _create_longer_list();
    ck_assert(!get(l, 0, NULL));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_negative_index) {
    l = _create_longer_list();
    struct person *b = (struct person *)0xDEADBEEFU;
    ck_assert(!get(l, -1, &b));
    ck_assert(!b);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_front) {
    l = _create_longer_list();
    struct person *b = (struct person *)0xDEADBEEFU;
    ck_assert(get(l, 0, &b));
    ck_assert(person_name_is(b, "austin"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_middle) {
    l = _create_longer_list();
    struct person *b = (struct person *)0xDEADBEEFU;
    ck_assert(get(l, 1, &b));
    ck_assert(person_name_is(b, "sanjay"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_back) {
    l = _create_longer_list();
    struct person *b = (struct person *)0xDEADBEEFU;
    ck_assert(get(l, 2, &b));
    ck_assert(person_name_is(b, "jim"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_out_of_bounds_index) {
    l = _create_longer_list();
    struct person *b = (struct person *)0xDEADBEEFU;
    ck_assert(!get(l, 3, &b));
    ck_assert(!b);
    checkLongerListUnchanged();
}
END_TEST

/******************************************************************************/
/******************************** size() tests ********************************/
/******************************************************************************/
START_TEST(test_list_size_listToGetSizeOf_NULL) {
    int sizeOut;
    ck_assert(!size(NULL, &sizeOut));
}
END_TEST

START_TEST(test_list_size_sizeOut_NULL) {
    l = _create_longer_list();
    ck_assert(!size(l, NULL));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_size_empty) {
    l = _create_list();
    int sizeOut;
    ck_assert(size(l, &sizeOut));
    ck_assert_int_eq(sizeOut, 0);
}
END_TEST

START_TEST(test_list_size_longer_list) {
    l = _create_longer_list();
    int sizeOut;
    ck_assert(size(l, &sizeOut));
    ck_assert_int_eq(sizeOut, 3);
    checkLongerListUnchanged();
}
END_TEST

/******************************************************************************/
/**************************** contains() tests ********************************/
/******************************************************************************/

START_TEST(test_list_contains_NULL_list) {
    struct person *jim = person_new("jim", "is cool");
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    int result = contains(NULL, (struct person *)jim, &dataOut);
    person_free(jim);
    ck_assert(!result);
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_contains_NULL_dataOut) {
    struct person *jim = person_new("jim", "is cool");
    l = _create_longer_list();
    int result = contains(l, (struct person *)jim, NULL);
    person_free(jim);
    ck_assert(!result);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_contains_empty) {
    l = _create_list();
    struct person *jim = person_new("jim", "is cool");
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    int result = contains(l, (struct person *)jim, &dataOut);
    person_free(jim);
    ck_assert(!result);
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_contains_not_contained) {
    l = _create_longer_list();
    struct person *jim = person_new("rim", "is cool");
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    int result = contains(l, (struct person *)jim, &dataOut);
    person_free(jim);
    ck_assert(!result);
    ck_assert(!dataOut);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_contains_is_contained) {
    l = _create_longer_list();
    struct person *jim = person_new("jim", "is cool");
    struct person *dataOut = (struct person *)0xDEADBEEFU;
    int result = contains(l, (struct person *)jim, &dataOut);
    person_free(jim);
    ck_assert(result);
    ck_assert(dataOut != jim);
    ck_assert(person_name_is(dataOut, "jim"));
    checkLongerListUnchanged();
}
END_TEST

Suite *list_suite(void) {
    Suite *s = suite_create("struct list");

    // create_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_basic);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_malloc_failure);

    // copy() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_basic);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_malloc_failure);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_null_list);

    // front() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_front_not_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_front_null);

    //back() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_back_not_empty);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_back_null);

    // push_front() tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_NULL_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_NULL_data);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_nonempty);

    // push_back()tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_non_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_null);

    // add() tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_out_of_bounds);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_empty_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_non_empty_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_null);

    // pop_front() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_longer_list);

    // pop_back() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_longer_list);

    // remove() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_front);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_middle);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_back);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_absent_element);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_length_1);

    // empty_list() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_length_1);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_longer_list);

    // reverse() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_reverse_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_reverse_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_reverse_length_1);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_reverse_longer_list);

    // concat() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_concat_NULL_firstList);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_concat_NULL_lastList);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_concat_first_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_concat_second_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_concat_second_length_1);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_concat_second_longer);

    // get() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_negative_index);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_front);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_middle);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_back);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_out_of_bounds_index);

    // size() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_size_listToGetSizeOf_NULL);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_size_sizeOut_NULL);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_size_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_size_longer_list);

    // contains() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_not_contained);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_is_contained);

    return s;
}
