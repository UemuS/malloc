/*
 * test_large.c
 * Smoke test for the "large" allocator path (> SMALL_MAX)
 */
#include <stdio.h>
#include <string.h>
#include "ft_malloc.h"  // custom malloc/free/realloc

int main(void) {
    /* Choose a size definitely > SMALL_MAX (e.g., 2000 bytes) */
    const size_t N = 2000;

    unsigned char *p = malloc(N);
    if (!p) {
        fprintf(stderr, "malloc failed");
        return 1;
    }

    /* Write and verify a pattern */
    memset(p, 0xAB, N);
    for (size_t i = 0; i < N; i++) {
        if (p[i] != 0xAB) {
            fprintf(stderr, "Memory corruption at %zu\n", i);
            free(p);
            return 2;
        }
    }

    /* Test realloc growing */
    size_t M = N + 4096;
    printf("→ realloc(p, %zu)\n", M);
    unsigned char *q = realloc(p, M);
    if (!q) {
        fprintf(stderr, "realloc failed\n");
        free(p);
        return 3;
    }
    for (size_t i = 0; i < N; i++) {
        if (q[i] != 0xAB) {
            fprintf(stderr, "realloc data mismatch at %zu\n", i);
            free(q);
            return 4;
        }
    }
    printf("  realloc grow test passed\n");

    /* Test realloc shrinking */
    size_t K = N / 2;
    printf("→ realloc(q, %zu)\n", K);
    unsigned char *r = realloc(q, K);
    if (!r) {
        fprintf(stderr, "realloc shrink failed\n");
        free(q);
        return 5;
    }
    printf("  realloc shrink test passed\n");

    free(r);
    printf("→ free(r) done\n");

    printf("All large‑alloc tests succeeded.\n");
    return 0;
}
