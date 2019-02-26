// Need stdlib.h #included before my #define, otherwise the preprocessor
// expands the malloc and calloc prototypes when they're #included later.
#include <stdlib.h>
#define malloc(n) ((++malloc_counter && (mallocs_until_fail == -1 || (mallocs_until_fail && mallocs_until_fail--)))? malloc(n) : NULL)
#define calloc(n,s) ((++malloc_counter && (mallocs_until_fail == -1 || (mallocs_until_fail && mallocs_until_fail--)))? calloc(n,s) : NULL)
#define realloc(n,s) ((++malloc_counter && (mallocs_until_fail == -1 || (mallocs_until_fail && mallocs_until_fail--)))? realloc(n,s) : NULL)

extern int mallocs_until_fail;
extern int malloc_counter;
