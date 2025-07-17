#ifndef UTIL_H
# define UTIL_H

#include <stddef.h>
#include <unistd.h>

typedef struct s_chunk t_chunk;

#define TINY_MAX    128
#define SMALL_MAX   1024
#define COUNT 100

#define TINY_ZONE_BLOCK_SIZE   (sizeof(t_chunk) + TINY_MAX)
#define SMALL_ZONE_BLOCK_SIZE  (sizeof(t_chunk) + SMALL_MAX)

static inline size_t zone_size(size_t block_size, size_t count) {
	size_t total = block_size * count;
	size_t pg = (size_t)getpagesize();
	size_t rem = total % pg;
	return rem == 0 ? total : total + (pg - rem);
}



#endif