/*
* src/zones.h
* Prototypes and externs for tiny and small allocators.
*/

#ifndef ZONES_H
#define ZONES_H

#include <stddef.h>
#include "global_malloc.h"

/* Tiny allocator (≤ TINY_MAX) */
void *alloc_tiny(size_t aligned_sz);
void  free_tiny(void *ptr);

/* Small allocator (TINY_MAX < size ≤ SMALL_MAX) */
void *alloc_small(size_t aligned_sz);
void  free_small(void *ptr);

/* Access to global malloc structure */
extern t_malloc_global g_malloc;

#endif // ZONES_H
