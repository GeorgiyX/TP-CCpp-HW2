#ifndef TP_HW2_CHECK_SUM_PRIVATE_H
#define TP_HW2_CHECK_SUM_PRIVATE_H

/**
 * Simple checksum calculation function
 * @param arr - pointer to array
 * @param array_size - size of array
 * @param check_sum - pointer to the variable to write the checksum to
 * @return EXIT_SUCCESS if everything is fine, or EXIT_FAILURE otherwise
 */
int get_check_sum_private(const int *arr, size_t array_size, int *check_sum);

#endif  // TP_HW2_CHECK_SUM_PRIVATE_H
