#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXBLOCKS 128
#define MAXSIZE 4096

void showfreelist(char *);

int  main(int argc, char *argv[]) {
	char *block[MAXBLOCKS];
	int size[MAXBLOCKS];
	int i;
	
	/* allocate some memory blocks */
	for (i = 0; i < MAXBLOCKS; i++) {
		assert(block[i] = malloc(size[i] = rand() % MAXSIZE));
	}
	showfreelist("after allocation");

	/* show the list of blocks */
	printf("\nAllocated blocks:\n");
	for (i = 0; i < MAXBLOCKS; i++) {
		printf("%-10lx size=%d\n", (long)block[i], size[i]);
	}

	/* free up the even blocks */
	for (i = 0; i < MAXBLOCKS; i += 2) {
		free(block[i]);
	}
	showfreelist("even blocks freed");

	/* free up the odd blocks */
	for (i = 1; i < MAXBLOCKS; i += 2) {
		free (block[i]);
	}
	showfreelist("all blocks freed");

	exit(0);
}
