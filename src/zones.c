/*
 * Tiny and small zone allocators: fixed-size pools using mmap.
 */

 #include "zones.h"
 #include "util/util.h"
 #include <sys/mman.h>
 #include <pthread.h>
 #include <stddef.h>
 #include <unistd.h>
 
 // Chunk header shared by tiny and small
 typedef struct s_chunk {
	 struct s_chunk *next;
	 size_t          size;
	 int             free;
 } t_chunk;
 
 // --- Tiny zone globals ---
 static t_chunk       *tiny_free_list = NULL;
 void                  *tiny_zone_base = NULL;
 size_t                TINY_ZONE_SIZE   = 0;
 static pthread_mutex_t tiny_lock       = PTHREAD_MUTEX_INITIALIZER;
 
 // Initialize a tiny zone: carve TINY_COUNT blocks
 static void init_tiny_zone(void) {
	 const size_t count    = 100;
	 size_t       block_sz = sizeof(t_chunk) + TINY_MAX;
	 TINY_ZONE_SIZE        = zone_size(block_sz, count);
 
	 void *zone = mmap(NULL, TINY_ZONE_SIZE,
					   PROT_READ | PROT_WRITE,
					   MAP_ANON  | MAP_PRIVATE,
					   -1, 0);
	 if (zone == MAP_FAILED)
		 return;
 
	 tiny_zone_base = zone;
	 char *p = zone;
	 for (size_t i = 0; i < count; i++, p += block_sz) {
		 t_chunk *c = (t_chunk *)p;
		 c->size     = TINY_MAX;
		 c->free     = 1;
		 c->next     = tiny_free_list;
		 tiny_free_list = c;
	 }
 }
 
 void *alloc_tiny(size_t aligned_sz) {
	 (void)aligned_sz;  // fixed slot size
	 pthread_mutex_lock(&tiny_lock);
	 if (!tiny_free_list)
		 init_tiny_zone();
	 if (!tiny_free_list) {
		 pthread_mutex_unlock(&tiny_lock);
		 return NULL;
	 }
	 t_chunk *c = tiny_free_list;
	 tiny_free_list = c->next;
	 c->free = 0;
	 pthread_mutex_unlock(&tiny_lock);
	 return (void *)(c + 1);
 }
 
 void free_tiny(void *ptr) {
	 if (!ptr) return;
	 t_chunk *c = (t_chunk *)ptr - 1;
	 pthread_mutex_lock(&tiny_lock);
	 c->free     = 1;
	 c->next     = tiny_free_list;
	 tiny_free_list = c;
	 pthread_mutex_unlock(&tiny_lock);
 }
 
 // --- Small zone globals ---
 static t_chunk       *small_free_list = NULL;
 void                  *small_zone_base = NULL;
 size_t                SMALL_ZONE_SIZE  = 0;
 static pthread_mutex_t small_lock      = PTHREAD_MUTEX_INITIALIZER;
 
 static void init_small_zone(void) {
	 const size_t count    = 100;
	 size_t       block_sz = sizeof(t_chunk) + SMALL_MAX;
	 SMALL_ZONE_SIZE       = zone_size(block_sz, count);
 
	 void *zone = mmap(NULL, SMALL_ZONE_SIZE,
					   PROT_READ | PROT_WRITE,
					   MAP_ANON  | MAP_PRIVATE,
					   -1, 0);
	 if (zone == MAP_FAILED)
		 return;
 
	 small_zone_base = zone;
	 char *p = zone;
	 for (size_t i = 0; i < count; i++, p += block_sz) {
		 t_chunk *c = (t_chunk *)p;
		 c->size       = SMALL_MAX;
		 c->free       = 1;
		 c->next       = small_free_list;
		 small_free_list = c;
	 }
 }
 
 void *alloc_small(size_t aligned_sz) {
	 (void)aligned_sz;
	 pthread_mutex_lock(&small_lock);
	 if (!small_free_list)
		 init_small_zone();
	 if (!small_free_list) {
		 pthread_mutex_unlock(&small_lock);
		 return NULL;
	 }
	 t_chunk *c = small_free_list;
	 small_free_list = c->next;
	 c->free = 0;
	 pthread_mutex_unlock(&small_lock);
	 return (void *)(c + 1);
 }
 
 void free_small(void *ptr) {
	 if (!ptr) return;
	 t_chunk *c = (t_chunk *)ptr - 1;
	 pthread_mutex_lock(&small_lock);
	 c->free        = 1;
	 c->next        = small_free_list;
	 small_free_list = c;
	 pthread_mutex_unlock(&small_lock);
 }
 