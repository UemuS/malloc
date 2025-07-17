#include "ft_malloc.h"
#include <stdio.h>    // for debugging output


void *malloc(size_t size){
	if (size == 0){
		return NULL;
	}

	size_t aligned = align_up(size);

	// Debug, remove-later
	printf("[ft_malloc] requested=%zu, aligned=%zu\n", size, aligned);


	// TODO: allocate 'aligned bytes from our allocator:
	// - This aligned size will determine how many bytes
	//   we actually allocate from our zones or via mmap.
	// - If aligned <= TINY_MAX, grab from tiny pool
	// - Else if aligned <= SMALL_MAX, grab from small pool
	// - else, mmap a large block

	return NULL;
}

void free(void *ptr) {
	(void)ptr;
}

void *realloc(void *ptr, size_t size) {
	(void)ptr;
	(void)size;
	return NULL;
}