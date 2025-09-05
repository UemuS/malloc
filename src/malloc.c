#include "ft_malloc.h"
#include "util/util.h"
#include "zones.h"    // alloc_tiny, free_tiny, alloc_small, free_small
#include "large.h"    // alloc_large, free_large, realloc_large
#include "libft.h"    // ft_memcpy for realloc
#include "global_malloc.h"
#include <stddef.h>

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

		if (cptr >= (char*)g_malloc.tiny_zone_base
		 && cptr <  (char*)g_malloc.tiny_zone_base + g_malloc.tiny_zone_size)
		{
			free_tiny(ptr);
		}
		else if (cptr >= (char*)g_malloc.small_zone_base
			  && cptr <  (char*)g_malloc.small_zone_base + g_malloc.small_zone_size)
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

    // For tiny and small, check if we can reuse the same block
    char *cptr = (char*)ptr;
    
    // Check if it's in tiny zone
    if (cptr >= (char*)g_malloc.tiny_zone_base && 
        cptr < (char*)g_malloc.tiny_zone_base + g_malloc.tiny_zone_size) {
        // If new size still fits in tiny zone, we can reuse the block
        if (aligned <= TINY_MAX) {
            return ptr;  // Same block can be reused
        }
    }
    
    // Check if it's in small zone
    else if (cptr >= (char*)g_malloc.small_zone_base && 
             cptr < (char*)g_malloc.small_zone_base + g_malloc.small_zone_size) {
        // If new size still fits in small zone, we can reuse the block
        if (aligned <= SMALL_MAX) {
            return ptr;  // Same block can be reused
        }
    }
    
    // Need to allocate new memory and copy
    void *newp = malloc(aligned);
    if (!newp)
        return NULL;
    ft_memcpy(newp, ptr, size);
    free(ptr);
    return newp;
}
