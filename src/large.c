/*
 * "Large" allocator: one mmap() per allocation for requests > SMALL_MAX.
 */

#include "ft_malloc.h"
#include "util/util.h"    // for getpagesize()
#include <sys/mman.h>
#include <string.h>        // memcpy
#include <errno.h>
#include "large.h"

// Chunk header for large allocations
typedef struct s_large_chunk {
    size_t size;
    struct s_large_chunk *next;
} t_large_chunk;

// Global linked list head for large allocations
void *large_allocations_head = NULL;

void *alloc_large(size_t aligned_sz) {
    size_t total = aligned_sz + sizeof(t_large_chunk);
    size_t pg = (size_t)getpagesize();
    size_t rem = total % pg;
    if (rem) total += pg - rem;

    void *mem = mmap(NULL, total,
                     PROT_READ | PROT_WRITE,
                     MAP_ANON | MAP_PRIVATE,
                     -1, 0);
    if (mem == MAP_FAILED) {
        return NULL;
    }

    t_large_chunk *chunk = (t_large_chunk *)mem;
    chunk->size = aligned_sz;
    
    // Add to global linked list for tracking
    chunk->next = large_allocations_head;
    large_allocations_head = chunk;
    
    // Return pointer to payload region after header
    return (void *)(chunk + 1);
}


void free_large(void *ptr) {
    if (!ptr) return;
    t_large_chunk *chunk = (t_large_chunk *)ptr - 1;
    
    // Remove from global linked list
    if (large_allocations_head == chunk) {
        large_allocations_head = chunk->next;
    } else {
        t_large_chunk *current = large_allocations_head;
        while (current && current->next != chunk) {
            current = current->next;
        }
        if (current) {
            current->next = chunk->next;
        }
    }
    
    size_t total = chunk->size + sizeof(t_large_chunk);
    size_t pg = (size_t)getpagesize();
    size_t rem = total % pg;
    if (rem) total += pg - rem;

    munmap((void *)chunk, total);
}


void *realloc_large(void *ptr, size_t new_sz) {
    if (!ptr) return alloc_large(new_sz);
    t_large_chunk *chunk = (t_large_chunk *)ptr - 1;
    size_t old_sz = chunk->size;
    size_t aligned_new = align_up(new_sz);
    if (aligned_new <= old_sz) {
        // can reuse the same block in-place
        chunk->size = aligned_new;
        return ptr;
    }
    // Need a new block
    void *newp = alloc_large(aligned_new);
    if (!newp) return NULL;
    memcpy(newp, ptr, old_sz);
    free_large(ptr);
    return newp;
}
