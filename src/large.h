#ifndef LARGE_H
# define LARGE_H

# include <stddef.h>
# include "global_malloc.h"

void *alloc_large(size_t aligned_sz);
void  free_large(void *ptr);
void *realloc_large(void *ptr, size_t new_sz);

// Access to global malloc structure
extern t_malloc_global g_malloc;

#endif