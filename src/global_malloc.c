#include "global_malloc.h"

// Single global variable to manage all allocations
t_malloc_global g_malloc = {
    .tiny_free_list = NULL,
    .tiny_zone_base = NULL,
    .tiny_zone_size = 0,
    .small_free_list = NULL,
    .small_zone_base = NULL,
    .small_zone_size = 0,
    .large_allocations_head = NULL,
    .mutex = PTHREAD_MUTEX_INITIALIZER
};
