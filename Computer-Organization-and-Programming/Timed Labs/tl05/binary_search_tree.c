#include "binary_search_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Add given data into the binary search tree in the correct place.
 * Remember the rules of how binary search trees work:
 *      1. Given a parent node, the left child MUST be of LESSER value
 *          than the parent
 *      2. Given a parent node, the right child MUST be of GREATER
 *          value than the parent.
 *
 * If the passed in data is already in the tree, then don't add it to the tree (do nothing).
 *
 * Binary search trees are highly recursive, and it's advised that you
 * follow a recursive strategy to traverse the tree until you find
 * a place to insert your new node.
 *
 * Example steps:
 * 1) Check if currNode is null. If it is, create a new node for the data, set its left and
 * right children to null, and return it.
 * 2) If it isn't, check if data is less than currNode's data.
 * 3) If data is less than currNode's data, set currNode's left child to the 
 * value returned by recursively calling add on currNode's left child.
 * 4) If data is greater than currNode's data, do the same thing as step 3 but 
 * with currNode's right child.
 * 5) If the data is equal to currNode's data, don't make any recursive calls.
 * 5) If currNode wasn't null, return it.
 *
 * @param currNode the current node that add is comparing. This will
 *                 be passed in as the root of the tree at the start
 * @param data the data to be inserted into the tree
 * @return the node being used in the recursive call
*/
bst_node *bst_add(bst_node *currNode, int data) {
	if(!currNode || currNode == NULL) {
		bst_node *newNode = malloc(sizeof(bst_node));
		if(!newNode || newNode == NULL) {
			return NULL;
		} else {
			newNode->data = data;
			newNode->left = NULL;
			newNode->right = NULL;
			return newNode;
		}
	}
	if((data < currNode->data)) {
		currNode->left = (bst_add((currNode->left), data));
	}
	if((data > currNode->data)) {
		currNode->right = (bst_add(currNode->right, data));
	}
	// else if(data == (currNode->data)) {
	// 	return currNode;
	// }
	return currNode;
}

/**
 * Checks to see if the binary search tree contains the data already.
 * As mentioned in the javadocs for the add method, binary search trees
 * are highly recursive, so it is recommended you use a recursive strategy
 * for traversing the tree.
 *
 * Example steps:
 * 1) Check if currNode is null, if it is return 0
 * 2) If the data is equal to currNode's data, return 1
 * 3) If the data is less than currNode's data, recursively call contains on 
 currNode's left child, and return the result.
 * 4) If the data is greater than currNode's data, do the same as 3 but with the right child.
 *
 * @param currNode the current node you are checking. This will be
 *                 passed in as the root of the tree at the start
 * @param data the data that is being search for
 * @return 1 if the data was in the tree, 0 if it wasn't
*/
int bst_contains(bst_node *currNode, int data) {
	if(currNode == NULL) {
		return 0;
	} 
	else if (data < (currNode->data)) {
		currNode = currNode->left;
		return bst_contains(currNode, data);

	} 
	else if (data > (currNode->data)) {
		currNode = currNode->right;
		return bst_contains(currNode, data);

	} 
	else if (currNode->data == data){
		return 1;
	}
	return 0;
}

/**
 * Destoys the binary search tree. After this is called, everything
 * in the tree should be freed.
 *
 * Again, use a recursive strategy.
 *
 * Example logic:
 * If currNode is not null, recursively call destroy on left child and right child, then destroy currNode.
 *
 * @param currNode the current node being destroyed. This will be
 *                 passed in as the root of the tree at the start
*/
void bst_destroy(bst_node *currNode) {
    if(currNode != NULL) {
    	bst_destroy(currNode->left);
    	bst_destroy(currNode->right);
    	free(currNode);
    	return;
    } else {
    	return;
    }
}
