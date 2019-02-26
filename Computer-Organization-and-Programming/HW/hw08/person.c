#include <check.h>
#include <stdlib.h>
#include "person.h"

int copies_until_malloc_fail = -1;
int bars_visited = 0;

/**
 * Hashes a person based on the first letter in their name. Names that start
 * with upper case letters hash to negative numbers, and those with lower case
 * letters will hash to 0 - 26.
 */
int person_hash(const struct person *a) {
    struct person *person_a = (struct person *)a;
    return (person_a->name)[0] - 97;
}

/**
 * Allocates a new person struct on the heap with the given name and word.
 */
struct person *person_new(char *name, char *word) {
    struct person *result = malloc(sizeof (struct person));
    ck_assert(result);

    result->name = malloc(strlen(name) + 1);
    ck_assert(result->name);
    strcpy(result->name, name);

    result->word = malloc(strlen(word) + 1);
    ck_assert(result->word);
    strcpy(result->word, word);

    return result;
}

/**
 * Deallocates the memory for a person struct.
 */
void person_free(struct person *p) {
    // At the moment, I don't add NULL pointers
    ck_assert(p);

    struct person *b = (struct person *) p;
    free(b->name);
    free(b->word);
    free(b);

    bars_visited++;
}

// Used in test_dll_null_data.
// This is separate from person_free() because I want to catch stray NULL data
// pointers outside test_dll_null_data
void person_free_null(struct person *p) {
    ck_assert(!p);

    bars_visited++;
}

/**
 * Copies the data for a person struct to newly allocated heap memory.
 */
int person_copy(const struct person *p, struct person **ret) {
    if (ret == NULL){
        return 0;
    }

    struct person *b = (struct person *) p;
    *ret = person_new(b->name, b->word);
    return 1;
}

// Used in test_dll_null_data.
// This is separate from person_copy() because I want to catch stray NULL data
// pointers outside test_dll_null_data
struct person *person_copy_null(const struct person *p) {
    ck_assert(!p);

    bars_visited++;

    return NULL;
}

// Used in test_dll_malloc_fail.
// To prevent valgrind from reporting leaks in copy_dllist() allowed by the
// TAs, return the pointer passed in.
struct person *person_copy_fake(const struct person *p) {
    if (!copies_until_malloc_fail) {
        // Simulate a failed malloc in copy_func()
        return NULL;
    } else {
        if (copies_until_malloc_fail != -1) {
            copies_until_malloc_fail--;
        }

        // TODO: This cast is a hack, but it shouldn't cause any issues because
        //       we never write to it. It's just a non-NULL value to send back
        return (struct person *) p;
    }
}

void person_visit(struct person *p) {
    // At the moment, I don't add NULL pointers
    ck_assert(p);
    bars_visited++;
}

// Used in test_dll_null_data.
// This is separate from person_visit() because I want to catch stray NULL data
// pointers outside test_dll_null_data
void person_visit_null(struct person *p) {
    ck_assert(!p);
    bars_visited++;
}

int person_eq(const struct person *a, const struct person *b) {
    ck_assert(a);
    ck_assert(b);
    struct person *person_a = (struct person *) a;
    struct person *person_b = (struct person *) b;
    return strcmp(person_a->name, person_b->name) || strcmp(person_a->word, person_b->word);
}

/**
 * Returns the string comparison of the two person structs' names. Check out
 * the man page for strcmp! (Fun fact, if you're on vim you can put your cursor
 * over the word strcmp (or any c standard library function) and press
 * shift+k to automatically open the man page)
 */
int person_eq_name(const struct person *a, const struct person *b) {
    ck_assert(a);
    ck_assert(b);
    struct person *person_a = (struct person *) a;
    struct person *person_b = (struct person *) b;

    bars_visited++;

    return strcmp(person_a->name, person_b->name);
}

// Used in test_dll_null_data.
// This is separate from person_eq() because I want to catch stray NULL data
// pointers outside test_dll_null_data
// Always find the first match
int person_eq_null_match(const struct person *a, const struct person *b) {
    ck_assert(!a);
    ck_assert(!b);

    bars_visited++;

    return 0;
}

// Same, but never finds a match
int person_eq_null_no_match(const struct person *a, const struct person *b) {
    ck_assert(!a);
    ck_assert(!b);

    bars_visited++;

    return 1;
}
