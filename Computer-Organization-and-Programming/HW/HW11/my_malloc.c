/*
 * CS 2110 Fall 2018
 * Author: Tahirah AhMAD
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"
/* include this for any boolean methods */
#include <stdbool.h>

/*Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */

/* Our freelist structure - our freelist is represented as two doubly linked lists
 * the address_list orders the free blocks in ascending address
 * the size_list orders the free blocks by size
 */

metadata_t *address_list;
metadata_t *size_list;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

/* MALLOC
 * See my_malloc.h for documentation
 */
void *my_malloc(size_t size) {
	if(size <= 0) {
		my_malloc_errno = NO_ERROR;
		return NULL;
	}
	size_t rSize = size + TOTAL_METADATA_SIZE;
	if (rSize >= SBRK_SIZE){
		my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
		return NULL;
	}
	my_malloc_errno = NO_ERROR;

	//initialize the free list i guess
	if(address_list == NULL || size_list == NULL){
		metadata_t *nHead = my_sbrk(SBRK_SIZE);
		if(nHead == NULL){
			my_malloc_errno = OUT_OF_MEMORY;
			return NULL;
		}
		nHead->prev_addr = NULL;
		nHead->next_addr = NULL;
		nHead->prev_size = 0;
		nHead->size = SBRK_SIZE;
		address_list = nHead;
		size_list = nHead;
	}


	return (NULL);
}

/* REALLOC
 * See my_malloc.h for documentation
 */
void *my_realloc(void *ptr, size_t size) {
	UNUSED_PARAMETER(ptr);
	UNUSED_PARAMETER(size);
	return (NULL);
}

/* CALLOC
 * See my_malloc.h for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
	UNUSED_PARAMETER(nmemb);
	UNUSED_PARAMETER(size);
	return (NULL);
}

/* FREE
 * See my_malloc.h for documentation
 */
void my_free(void *ptr) {
	UNUSED_PARAMETER(ptr);
}
