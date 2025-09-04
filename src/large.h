#ifndef LARGE_H
# define LARGE_H

# include <stddef.h>

void *alloc_large(size_t aligned_sz);
void  free_large(void *ptr);
void *realloc_large(void *ptr, size_t new_sz);

// Global variable for tracking large allocations
extern void *large_allocations_head;

#endif