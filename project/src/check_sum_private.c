#include <stdlib.h>
#include "check_sum_private.h"

const int CHECK_SUM_MODULE = 1024;

int get_check_sum_private(const int *arr, size_t array_size, int *check_sum) {
    if (!arr || !check_sum) { return EXIT_FAILURE; }

    *check_sum = 0;
    for (size_t i = 0; i < array_size; ++i) {
        *check_sum = (*check_sum + arr[i]) % CHECK_SUM_MODULE;
    }

    return EXIT_SUCCESS;
}
