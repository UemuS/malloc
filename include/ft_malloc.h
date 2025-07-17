#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stddef.h>

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void show_alloc_mem(void);

# define ALIGNEMENT 16

static inline size_t align_up(size_t sz) {
    size_t rem = sz % ALIGNEMENT;
    if (rem == 0)
        return sz;
    return sz + (ALIGNEMENT - rem);
}

#endif