#include <stdio.h>
#include "include/ft_malloc.h"

int main(void) {
    size_t tests[] = {1, 16, 17, 30, 32, 33, 100, 1023, 1024, 1025};
    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        size_t in  = tests[i];
        size_t out = align_up(in);
        printf("align_up(%4zu) -> %4zu\n", in, out);
    }
    return 0;
}