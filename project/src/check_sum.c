#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "check_sum.h"

const int ERROR_CODE = -1;
const int SUCCESS_CODE = 0;

int *create_array(size_t count) {
    return malloc(count);
}

void free_array(int *arr) {
    if (!arr) {
        return;
    }
    free(arr);
}

int set_values(int *arr, const size_t array_size, const size_t seed, const size_t step) {
    if (!arr) {
        return ERROR_CODE;
    }
    if (!array_size || !step) {
        return SUCCESS_CODE;
    }

    srandom(seed);
    size_t remaining_elements = 0;

    for (size_t i = 0; i < array_size; i += step) {
        remaining_elements = array_size - i;
        memset(arr + i, random() % INT_MAX, remaining_elements > step ? step : remaining_elements);
    }

    return SUCCESS_CODE;
}
