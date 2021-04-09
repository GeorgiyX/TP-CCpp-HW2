#include <glob.h>
#include "check_sum_private.h"
#include "check_sum.h"

int get_check_sum(const int *arr, size_t array_size, int *check_sum) {
    return get_check_sum_private(arr, array_size, check_sum);
}
