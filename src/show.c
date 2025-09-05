/*
 * show_alloc_mem.c
 * Function to display the state of allocated memory zones
 */

#include "ft_malloc.h"
#include "zones.h"
#include "large.h"
#include "util/util.h"
#include "libft.h"
#include "ft_printf/includes/libftprintf.h"
#include "global_malloc.h"
#include <unistd.h>

void show_alloc_mem(void) {
    ft_printf("TINY : %p\n", g_malloc.tiny_zone_base);
    
    if (g_malloc.tiny_zone_base) {
        char *zone_end = (char*)g_malloc.tiny_zone_base + g_malloc.tiny_zone_size;
        char *p = g_malloc.tiny_zone_base;
        
        while (p < zone_end) {
            t_chunk *c = (t_chunk *)p;
            // Only show chunks that are allocated and have valid size
            if (c->free == 0 && c->size > 0 && c->size <= TINY_MAX) {
                ft_printf("%p - %p : %zu bytes\n", 
                       (void*)(c + 1), 
                       (void*)((char*)(c + 1) + c->size - 1),
                       c->size);
            }
            p += sizeof(t_chunk) + TINY_MAX;
        }
    }
    
    ft_printf("SMALL : %p\n", g_malloc.small_zone_base);
    
    if (g_malloc.small_zone_base) {
        char *zone_end = (char*)g_malloc.small_zone_base + g_malloc.small_zone_size;
        char *p = g_malloc.small_zone_base;
        
        while (p < zone_end) {
            t_chunk *c = (t_chunk *)p;
            // Only show chunks that are allocated and have valid size
            if (c->free == 0 && c->size > 0 && c->size <= SMALL_MAX) {
                ft_printf("%p - %p : %zu bytes\n", 
                       (void*)(c + 1), 
                       (void*)(c + 1) + c->size - 1,
                       c->size);
            }
            p += sizeof(t_chunk) + SMALL_MAX;
        }
    }
    
    ft_printf("LARGE : %p\n", g_malloc.large_allocations_head);
    
    // Display large allocations
    t_large_chunk *current = g_malloc.large_allocations_head;
    while (current) {
        ft_printf("%p - %p : %zu bytes\n",
               (void*)(current + 1),
               (void*)((char*)(current + 1) + current->size - 1),
               current->size);
        current = current->next;
    }
}
