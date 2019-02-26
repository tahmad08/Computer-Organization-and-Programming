#ifndef BAR_H
#define BAR_H

extern int copies_until_malloc_fail;
extern int bars_visited;

struct person {
    char *name;
    char *word;
};

struct person *person_new(char *name, char *word);
void person_free(struct person *p);
int person_copy(const struct person *p, struct person **ret);
int person_eq(const struct person *a, const struct person *b);
int person_eq_name(const struct person *a, const struct person *b);
int person_hash(const struct person *a);

#endif
