#ifndef TP_HW2_CHECK_SUM_H
#define TP_HW2_CHECK_SUM_H

/** Public API */

/**
 * Create an array on the heap with the size of "count".
 * The values in the array are not initialize.
 * @param count - size of array
 * @return array ptr or NULL
 */
int *create_array(size_t count);

/**
 * Frees up the memory allocated to the array.
 * @param arr - pointer to array. If it is null, then the function does nothing.
 */
void free_array(int *arr);

/**
 * Set the values in the arr array at each intervals of length "step",
 * using a random number generator seeded with seed.
 * @param arr - array ptr
 * @param array_size - size of array
 * @param seed - initial value of random number generator
 * @param step - length of intervals, if equal 0 the array is not initialized
 * @return EXIT_SUCCESS if everything is fine, or EXIT_FAILURE otherwise
 */
int set_values(int *arr, size_t array_size, size_t seed, size_t step);

/**
 * Calculate the check sum of array
 * @param arr - array ptr
 * @param array_size - size of array
 * @param check_sum
 * @return checksum
 */
int get_check_sum(int *arr, size_t array_size, int *check_sum);

#endif //TP_HW2_CHECK_SUM_H
