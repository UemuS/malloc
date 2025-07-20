/* test_small.c */
#include <stdio.h>
#include <string.h>
#include "ft_malloc.h"

int main(void) {
    const size_t N = 512;  // between TINY_MAX (128) and SMALL_MAX (1024)

    printf("→ malloc(%zu) → alloc_small path\n", N);
    unsigned char *p = malloc(N);
    if (!p) {
        fprintf(stderr, "malloc small failed\n");
        return 1;
    }

    /* fill & verify */
    memset(p, 0x5A, N);
    for (size_t i = 0; i < N; i++) {
        if (p[i] != 0x5A) {
            fprintf(stderr, "Memory corruption at %zu\n", i);
            free(p);
            return 2;
        }
    }
    printf("  fill/read test passed\n");

    /* realloc grow within small */
    size_t M = N + 200;
    printf("→ realloc(p, %zu)\n", M);
    unsigned char *q = realloc(p, M);
    if (!q) {
        fprintf(stderr, "realloc small grow failed\n");
        free(p);
        return 3;
    }
    /* verify preserved data */
    for (size_t i = 0; i < N; i++) {
        if (q[i] != 0x5A) {
            fprintf(stderr, "realloc data mismatch at %zu\n", i);
            free(q);
            return 4;
        }
    }
    printf("  realloc grow test passed\n");

    /* realloc shrink */
    size_t K = N / 2;
    printf("→ realloc(q, %zu)\n", K);
    unsigned char *r = realloc(q, K);
    if (!r) {
        fprintf(stderr, "realloc small shrink failed\n");
        free(q);
        return 5;
    }
    printf("  realloc shrink test passed\n");

    free(r);
    printf("All small‑alloc tests succeeded.\n");
    return 0;
}
