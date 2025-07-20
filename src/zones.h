/*
 * src/zones.h
 * Prototypes and externs for tiny and small allocators.
 */

 #ifndef ZONES_H
 #define ZONES_H
 
 #include <stddef.h>
 
 /* Tiny allocator (≤ TINY_MAX) */
 void *alloc_tiny(size_t aligned_sz);
 void  free_tiny(void *ptr);
 
 /* Small allocator (TINY_MAX < size ≤ SMALL_MAX) */
 void *alloc_small(size_t aligned_sz);
 void  free_small(void *ptr);
 
 /* Zone base pointers and sizes for free() dispatch */
 extern void  *tiny_zone_base;
 extern size_t TINY_ZONE_SIZE;
 
 extern void  *small_zone_base;
 extern size_t SMALL_ZONE_SIZE;
 
 #endif // ZONES_H
 