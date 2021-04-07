#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "check_sum.h"

#include <stdio.h>

int *create_array(size_t count) {
    long l1d_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (l1d_size == -1) {
        l1d_size = sizeof (void*);
    }
    void *mem_ptr = NULL;
    if (posix_memalign(&mem_ptr, l1d_size, count)) {
        return NULL;
    }
    memset(mem_ptr, 0, count);
    return  mem_ptr;
}

void free_array(int *arr) {
    if (!arr) { return; }
    free(arr);
}

int set_values(int *arr, const size_t array_size, const size_t seed, const size_t step) {
    if (!arr) {
        return EXIT_FAILURE;
    }
    if (!array_size || !step) {
        return EXIT_SUCCESS;
    }

    srandom(seed);
    size_t remaining_elements = 0;

    for (size_t i = 0; i < array_size; i += step) {
        remaining_elements = array_size - i;
        memset(arr + i, random() % INT_MAX, remaining_elements > step ? step : remaining_elements);
    }

    return EXIT_SUCCESS;
}
