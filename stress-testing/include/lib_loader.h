#ifndef TP_HW2_LIB_LOADER_H
#define TP_HW2_LIB_LOADER_H

extern int *(*create_array)(size_t count);
extern void (*free_array)(int *arr);
extern int (*set_values)(int *arr, size_t array_size, size_t seed, size_t step);
extern int (*get_check_sum)(int *arr, size_t array_size, int *check_sum);

int load_dynamic_symbols(const char *lib_path);
int unload_dynamic_symbols();

#endif //TP_HW2_LIB_LOADER_H
