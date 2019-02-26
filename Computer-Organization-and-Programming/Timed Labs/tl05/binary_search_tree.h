#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

/* DO NOT MODIFY THIS FILE
   all of your cod should be in binary_search_tree.c */

#define UNUSED_PARAM(x) (void)(x)

#define SET_SUCCESS 0

#define SET_FAILURE 1

typedef void (data_op)(void *);

// definition of each of the nodes in our binary search tree
typedef struct bst_node {
    // pointer to the left node in the tree
    struct bst_node *left;
    //pointer to the right node in the tree
    struct bst_node *right;
    // data stored in this node
    int data;

} bst_node;

/* methods to implement. DO NOT EDIT THESE, DO ALL WORK IN
   binary_search_tree.c!!!! */

bst_node *bst_add(bst_node *, int);

int bst_contains(bst_node *, int);

void bst_destroy(bst_node *);

#endif /* BINARY_SEARCH_TREE_H */
