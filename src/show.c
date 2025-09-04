/*
 * show_alloc_mem.c
 * Function to display the state of allocated memory zones
 */

#include "ft_malloc.h"
#include "zones.h"
#include "large.h"
#include "util/util.h"
#include <stdio.h>
#include <unistd.h>

// Chunk header structure (same as in zones.c)
typedef struct s_chunk {
    struct s_chunk *next;
    size_t          size;
    int             free;
} t_chunk;

// Large chunk header structure (same as in large.c)
typedef struct s_large_chunk {
    size_t size;
    struct s_large_chunk *next;
} t_large_chunk;

// Global variables for large allocations tracking
extern void *large_allocations_head;

void show_alloc_mem(void) {
    printf("TINY : %p\n", tiny_zone_base);
    
    if (tiny_zone_base) {
        char *zone_end = (char*)tiny_zone_base + TINY_ZONE_SIZE;
        char *p = tiny_zone_base;
        
        while (p < zone_end) {
            t_chunk *c = (t_chunk *)p;
            // Only show chunks that are allocated and have valid size
            if (c->free == 0 && c->size > 0 && c->size <= TINY_MAX) {
                printf("%p - %p : %zu bytes\n", 
                       (void*)(c + 1), 
                       (void*)((char*)(c + 1) + c->size - 1),
                       c->size);
            }
            p += sizeof(t_chunk) + TINY_MAX;
        }
    }
    
    printf("SMALL : %p\n", small_zone_base);
    
    if (small_zone_base) {
        char *zone_end = (char*)small_zone_base + SMALL_ZONE_SIZE;
        char *p = small_zone_base;
        
        while (p < zone_end) {
            t_chunk *c = (t_chunk *)p;
            // Only show chunks that are allocated and have valid size
            if (c->free == 0 && c->size > 0 && c->size <= SMALL_MAX) {
                printf("%p - %p : %zu bytes\n", 
                       (void*)(c + 1), 
                       (void*)(c + 1) + c->size - 1,
                       c->size);
            }
            p += sizeof(t_chunk) + SMALL_MAX;
        }
    }
    
    printf("LARGE : %p\n", large_allocations_head);
    
    // Display large allocations
    t_large_chunk *current = large_allocations_head;
    while (current) {
        printf("%p - %p : %zu bytes\n",
               (void*)(current + 1),
               (void*)((char*)(current + 1) + current->size - 1),
               current->size);
        current = current->next;
    }
}
