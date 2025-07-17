#include "ft_malloc.h"
#include "util/util.h"
#include <sys/mman.h>
#include <pthread.h>


// Chunk header
struct s_chunk {
    struct s_chunk *next;
    size_t          size;
    int             free;
};

// free‑lists and bases
static t_chunk	*tiny_free = NULL, *small_free = NULL;
static void 	*tiny_base = NULL, *small_base = NULL;
static pthread_mutex_t	tiny_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t	small_lock = PTHREAD_MUTEX_INITIALIZER;


static void init_zone(t_chunk **freep, void **basep, size_t block_size, size_t count, pthread_mutex_t *lock){
	size_t	zs = zone_size(block_size, count);
	void	*zone = mmap(NULL, zs, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);

	if (zone == MAP_FAILED) return;
	*basep = zone;
	char *p = zone;
	
	for (size_t i = 0; i < count; i++, p+= block_size) {
		t_chunk *c = (t_chunk*)p;
		c->size = block_size - sizeof(t_chunk);
		c->free = 1;
		c->next = *freep;
		*freep = c;
	}
}

// here alloc_zone() and free_zone() parameterized for tiny vs small