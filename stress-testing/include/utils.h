#ifndef TP_HW2_UTILS_H
#define TP_HW2_UTILS_H

int read_params(int argc, const char **argv, size_t *seed, size_t *arr_size, const char **lib_path);
int get_elapsed_time(const struct timeval *start, const struct timeval *end, double *result);
int test_work(int *array, size_t array_size, int *check_sum, double *elapsed);

#endif //TP_HW2_UTILS_H
