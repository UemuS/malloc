#ifndef GLOBAL_MALLOC_H
# define GLOBAL_MALLOC_H

#include <pthread.h>
#include <stddef.h>

// Chunk header for tiny/small zones
typedef struct s_chunk {
    struct s_chunk *next;
    size_t          size;
    int             free;
} t_chunk;

// Chunk header for large allocations
typedef struct s_large_chunk {
    size_t size;
    struct s_large_chunk *next;
} t_large_chunk;

// Single global structure to manage all allocations
typedef struct s_malloc_global {
    // Tiny zone
    t_chunk *tiny_free_list;
    void    *tiny_zone_base;
    size_t  tiny_zone_size;
    
    // Small zone
    t_chunk *small_free_list;
    void    *small_zone_base;
    size_t  small_zone_size;
    
    // Large allocations
    t_large_chunk *large_allocations_head;
    
    // Thread safety
    pthread_mutex_t mutex;
} t_malloc_global;

// Single global variable for all allocations
extern t_malloc_global g_malloc;


#endif
