#pragma once
/**
 * @file array.h
 * @brief Dynamic sizing array implementation
 *
 * @details Unlike C++ vector<>, the stretchy_buffer has the same
 * semantics as an object that you manually malloc and realloc.
 * The pointer may relocate every time you add a new object
 * to it, so you:
 *
 *   1. can't take long-term pointers to elements of the array
 *   2. have to return the pointer from functions which might expand it
 *      (either as a return value or by storing it to a ptr-to-ptr)
 *
 * Inspired by: https://github.com/nothings/stb/blob/master/deprecated/stretchy_buffer.h
 *
 * A long-standing tradition in things like malloc implementations
 * is to store extra data before the beginning of the block returned
 * to the user. The dynamic array implementation here uses the
 * same trick; the current-count and current-allocation-size are
 * stored before the beginning of the array returned to the user.
 * (This means you can't directly free() the pointer, because the
 * allocated pointer is different from the type-safe pointer provided
 * to the user.)
 *
 * The details are trivial and implementation is straightforward;
 * the main trick is in realizing in the first place that it's
 * possible to do this in a generic, type-safe way in C.
 * 
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
 * 
 * @return void pointer to potentially relocated array start
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
