#pragma once
/**
 * @file array.h
 * @brief Dynamic sizing array implementation
 */

/**
 * @brief push value onto dynamic array
 * 
 * @param array The target array to add to
 * @param value The value to push onto array
 */
#define array_push(array, value)                                                         \
  do {                                                                                   \
    (array) = array_hold((array), 1, sizeof(*(array)));                                  \
    (array)[array_length(array) - 1] = (value);                                          \
  } while (0);

/**
 * @brief Dynamically allocate array memory to hold item
 * 
 * @param array Pointer to array
 * @param count Number of items to add
 * @param item_size Size of the item type being added
 */
void *array_hold(void *array, int count, int item_size);

/**
 * @brief Get length of array
 * 
 * @param array Pointer to array
 * @return length of array
 */
int array_length(void *array);

/**
 * @brief free an array
 * 
 * @param array Pointer to array
 */
void array_free(void *array);
