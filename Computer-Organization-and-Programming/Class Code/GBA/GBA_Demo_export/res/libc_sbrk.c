#include <stdlib.h>
#include <errno.h>
#include <reent.h>

char *fake_heap_end = (char*)0;
char *fake_heap_start = (char*)0;

void *_sbrk(int incr) {
	register char *stack_ptr __asm__("sp");
	struct _reent *ptr = _REENT;
	extern char end __asm__("__end__"); /* Linker gives us this. */
	static char * heap_start = NULL;

	char *prev_heap_start;
	char *heap_end;

	if (heap_start == NULL)
		heap_start = fake_heap_start ? fake_heap_start : &end;

	prev_heap_start = heap_start;
	heap_end = fake_heap_end ? fake_heap_end : stack_ptr;

	if (heap_start + incr > heap_end) {
		ptr->_errno = ENOMEM;
		return (void *)-1;
	}

	heap_start += incr;
	return (void*)prev_heap_start;
}
