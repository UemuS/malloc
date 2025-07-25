#include "ft_malloc.h"
#include "util/util.h"
#include "zones.h"    // alloc_tiny, free_tiny, alloc_small, free_small
#include "large.h"    // alloc_large, free_large, realloc_large
#include <stddef.h>
#include <string.h>    // memcpy for realloc

void *malloc(size_t size) {
    if (size == 0)
        return NULL;

    size_t aligned = align_up(size);

    // Dispatch based on size
    if (aligned <= TINY_MAX)
        return alloc_tiny(aligned);
    else if (aligned <= SMALL_MAX)
        return alloc_small(aligned);
    else
        return alloc_large(aligned);
}

void free(void *ptr) {
    if (!ptr)
        return;

		char *cptr = (char*)ptr;

		if (cptr >= (char*)tiny_zone_base
		 && cptr <  (char*)tiny_zone_base + TINY_ZONE_SIZE)
		{
			free_tiny(ptr);
		}
		else if (cptr >= (char*)small_zone_base
			  && cptr <  (char*)small_zone_base + SMALL_ZONE_SIZE)
		{
			free_small(ptr);
		}
		else {
			free_large(ptr);
		}
}

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    size_t aligned = align_up(size);
    // Large path
    if (aligned > SMALL_MAX)
        return realloc_large(ptr, size);

    // Tiny/small path: simple alloc+copy+free
    void *newp = malloc(size);
    if (!newp)
        return NULL;
    memcpy(newp, ptr, size);
    free(ptr);
    return newp;
}
