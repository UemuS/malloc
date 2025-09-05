/*
* Tiny and small zone allocators: fixed-size pools using mmap.
*/

#include "zones.h"
#include "util/util.h"
#include "global_malloc.h"
#include <sys/mman.h>
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>

// Initialize a tiny zone: carve TINY_COUNT blocks
static void init_tiny_zone(void) {
	const size_t count    = 100;
	size_t       block_sz = sizeof(t_chunk) + TINY_MAX;
	g_malloc.tiny_zone_size = zone_size(block_sz, count);

	void *zone = mmap(NULL, g_malloc.tiny_zone_size,
					PROT_READ | PROT_WRITE,
					MAP_ANON  | MAP_PRIVATE,
					-1, 0);
	if (zone == MAP_FAILED)
		return;

	g_malloc.tiny_zone_base = zone;
	char *p = zone;
	for (size_t i = 0; i < count; i++, p += block_sz) {
		t_chunk *c = (t_chunk *)p;
		c->size     = TINY_MAX;
		c->free     = 1;
		c->next     = g_malloc.tiny_free_list;
		g_malloc.tiny_free_list = c;
	}
}

void *alloc_tiny(size_t aligned_sz) {
	(void)aligned_sz;  // fixed slot size
	pthread_mutex_lock(&g_malloc.mutex);
	if (!g_malloc.tiny_free_list)
		init_tiny_zone();
	if (!g_malloc.tiny_free_list) {
		pthread_mutex_unlock(&g_malloc.mutex);
		return NULL;
	}
	t_chunk *c = g_malloc.tiny_free_list;
	g_malloc.tiny_free_list = c->next;
	c->free = 0;
	pthread_mutex_unlock(&g_malloc.mutex);
	return (void *)(c + 1);
}

void free_tiny(void *ptr) {
	if (!ptr) return;
	t_chunk *c = (t_chunk *)ptr - 1;
	pthread_mutex_lock(&g_malloc.mutex);
	c->free     = 1;
	c->next     = g_malloc.tiny_free_list;
	g_malloc.tiny_free_list = c;
	pthread_mutex_unlock(&g_malloc.mutex);
}

static void init_small_zone(void) {
	const size_t count    = 100;
	size_t       block_sz = sizeof(t_chunk) + SMALL_MAX;
	g_malloc.small_zone_size = zone_size(block_sz, count);

	void *zone = mmap(NULL, g_malloc.small_zone_size,
					PROT_READ | PROT_WRITE,
					MAP_ANON  | MAP_PRIVATE,
					-1, 0);
	if (zone == MAP_FAILED)
		return;

	g_malloc.small_zone_base = zone;
	char *p = zone;
	for (size_t i = 0; i < count; i++, p += block_sz) {
		t_chunk *c = (t_chunk *)p;
		c->size       = SMALL_MAX;
		c->free       = 1;
		c->next       = g_malloc.small_free_list;
		g_malloc.small_free_list = c;
	}
}

void *alloc_small(size_t aligned_sz) {
	(void)aligned_sz;
	pthread_mutex_lock(&g_malloc.mutex);
	if (!g_malloc.small_free_list)
		init_small_zone();
	if (!g_malloc.small_free_list) {
		pthread_mutex_unlock(&g_malloc.mutex);
		return NULL;
	}
	t_chunk *c = g_malloc.small_free_list;
	g_malloc.small_free_list = c->next;
	c->free = 0;
	pthread_mutex_unlock(&g_malloc.mutex);
	return (void *)(c + 1);
}

void free_small(void *ptr) {
	if (!ptr) return;
	t_chunk *c = (t_chunk *)ptr - 1;
	pthread_mutex_lock(&g_malloc.mutex);
	c->free        = 1;
	c->next        = g_malloc.small_free_list;
	g_malloc.small_free_list = c;
	pthread_mutex_unlock(&g_malloc.mutex);
}
