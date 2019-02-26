/**
 * CS 2110 - Fall 2018 - Homework #10
 *
 * Do not modify this file!
 *
 * struct list.h
 */

#ifndef LIST_H
#define LIST_H

#include "person.h"

/**************************
 ** Datatype definitions **
 **************************/

/* Forward declaration
 * Don't know what a forward declaration is?
 * Consult the fountain of knowledge:
 * http://en.wikipedia.org/wiki/Forward_declaration
 */

struct list_node;

/* Given to you for free, however you better know how to do this come time for
 * the final exam!
 * The struct list struct. Has a head pointer.
 */
struct list
{
    // Head pointer either points to a node with data or if the struct list is
    // empty NULL
    struct list_node *head;
    // Tail pointer either points to a node with data or if the struct list is
    // empty NULL
    struct list_node *tail;
    // Size of the struct list
    int size;
};

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check struct list.c.                           **
***************************************************/

/* Creating */
struct list *create_list(void);
struct list *copy_list(struct list *);

/* Adding */
int push_front(struct list *, struct person *);
int push_back(struct list *, struct person *);
int add(struct list *, int index, struct person *);

/* Querying */
int front(struct list *, struct person **);
int back(struct list *, struct person **);
int get(struct list *, int, struct person **);
int size(struct list *, int *);
int contains(struct list *, struct person *, struct person **);

/* Removing */
int pop_front(struct list *, struct person **);
int pop_back(struct list *, struct person **);
int list_remove(struct list *, struct person *, struct person **);
void empty_list(struct list *);

/* Mutating */
int reverse(struct list *);
int concat(struct list *, struct list *);

#endif
