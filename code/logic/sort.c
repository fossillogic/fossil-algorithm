/**
 * -----------------------------------------------------------------------------
 * Project: Fossil Logic
 *
 * This file is part of the Fossil Logic project, which aims to develop
 * high-performance, cross-platform applications and libraries. The code
 * contained herein is licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License. You may obtain
 * a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * Author: Michael Gene Brockus (Dreamer)
 * Date: 04/05/2014
 *
 * Copyright (C) 2014-2025 Fossil Logic. All rights reserved.
 * -----------------------------------------------------------------------------
 */
#include "fossil/algorithm/sort.h"

/**
 * @brief Automatically selects and applies the optimal sorting algorithm.
 *
 * Chooses the best algorithm based on input size and options.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements in the array.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_auto(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1)
        return 0;

    if (!options)
        options = &(fossil_sort_options_t)FOSSIL_SORT_DEFAULT_OPTIONS;

    // Choose algorithm based on size and stability
    if (count < 32) {
        // Small arrays: insertion sort is fast
        return fossil_algorithm_sort_insertion(base, count, size, cmp, options);
    } else if (options->stable == FOSSIL_SORT_STABLE) {
        // Stable sort requested: use merge sort
        return fossil_algorithm_sort_merge(base, count, size, cmp, options);
    } else {
        // Default: quicksort for speed
        return fossil_algorithm_sort_quick(base, count, size, cmp, options);
    }
}

/**
 * @brief Sorts using the quicksort algorithm.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
static void fossil_swap_bytes(char *a, char *b, size_t size)
{
    while (size--) {
        char tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

static int fossil_quick_partition(
    char *base, size_t low, size_t high, size_t size,
    fossil_compare_fn cmp, const fossil_sort_options_t *options
)
{
    char *pivot = base + high * size;
    size_t i = low;
    for (size_t j = low; j < high; ++j) {
        int res = cmp(base + j * size, pivot);
        if (options && options->order == FOSSIL_SORT_DESCENDING)
            res = -res;
        if (res < 0) {
            fossil_swap_bytes(base + i * size, base + j * size, size);
            i++;
        }
    }
    fossil_swap_bytes(base + i * size, pivot, size);
    return i;
}

static void fossil_quick_sort(
    char *base, size_t low, size_t high, size_t size,
    fossil_compare_fn cmp, const fossil_sort_options_t *options
)
{
    if (low < high) {
        int pi = fossil_quick_partition(base, low, high, size, cmp, options);
        if (pi > 0)
            fossil_quick_sort(base, low, pi - 1, size, cmp, options);
        fossil_quick_sort(base, pi + 1, high, size, cmp, options);
    }
}

int fossil_algorithm_sort_quick(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base || !cmp)
        return 0;
    fossil_quick_sort((char *)base, 0, count - 1, size, cmp, options);
    return 0;
}

/**
 * @brief Sorts using the merge sort algorithm.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
static void fossil_merge(
    char *base, size_t left, size_t mid, size_t right, size_t size,
    fossil_compare_fn cmp, const fossil_sort_options_t *options, char *temp
)
{
    size_t i = left, j = mid, k = left;
    while (i < mid && j < right) {
        int res = cmp(base + i * size, base + j * size);
        if (options && options->order == FOSSIL_SORT_DESCENDING)
            res = -res;
        if (res <= 0) {
            memcpy(temp + k * size, base + i * size, size);
            i++;
        } else {
            memcpy(temp + k * size, base + j * size, size);
            j++;
        }
        k++;
    }
    while (i < mid) {
        memcpy(temp + k * size, base + i * size, size);
        i++; k++;
    }
    while (j < right) {
        memcpy(temp + k * size, base + j * size, size);
        j++; k++;
    }
    memcpy(base + left * size, temp + left * size, (right - left) * size);
}

static void fossil_merge_sort_recursive(
    char *base, size_t left, size_t right, size_t size,
    fossil_compare_fn cmp, const fossil_sort_options_t *options, char *temp
)
{
    if (right - left > 1) {
        size_t mid = left + (right - left) / 2;
        fossil_merge_sort_recursive(base, left, mid, size, cmp, options, temp);
        fossil_merge_sort_recursive(base, mid, right, size, cmp, options, temp);
        fossil_merge(base, left, mid, right, size, cmp, options, temp);
    }
}

int fossil_algorithm_sort_merge(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base || !cmp)
        return 0;
    char *temp = (char *)malloc(count * size);
    if (!temp)
        return -1;
    fossil_merge_sort_recursive((char *)base, 0, count, size, cmp, options, temp);
    free(temp);
    return 0;
}

/**
 * @brief Sorts using the heap sort algorithm.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
static void fossil_heapify(
    char *base, size_t count, size_t root, size_t size,
    fossil_compare_fn cmp, const fossil_sort_options_t *options
)
{
    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;

    if (left < count) {
        int res = cmp(base + left * size, base + largest * size);
        if (options && options->order == FOSSIL_SORT_DESCENDING)
            res = -res;
        if (res > 0)
            largest = left;
    }
    if (right < count) {
        int res = cmp(base + right * size, base + largest * size);
        if (options && options->order == FOSSIL_SORT_DESCENDING)
            res = -res;
        if (res > 0)
            largest = right;
    }
    if (largest != root) {
        fossil_swap_bytes(base + root * size, base + largest * size, size);
        fossil_heapify(base, count, largest, size, cmp, options);
    }
}

int fossil_algorithm_sort_heap(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base || !cmp)
        return 0;

    char *arr = (char *)base;

    // Build heap
    for (long i = (long)count / 2 - 1; i >= 0; --i)
        fossil_heapify(arr, count, (size_t)i, size, cmp, options);

    // Extract elements from heap
    for (size_t i = count - 1; i > 0; --i) {
        fossil_swap_bytes(arr, arr + i * size, size);
        fossil_heapify(arr, i, 0, size, cmp, options);
    }
    return 0;
}

/**
 * @brief Sorts using the insertion sort algorithm.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
int fossil_algorithm_sort_insertion(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base || !cmp)
        return 0;

    char *arr = (char *)base;
    char *temp = (char *)malloc(size);
    if (!temp)
        return -1;

    for (size_t i = 1; i < count; ++i) {
        memcpy(temp, arr + i * size, size);
        size_t j = i;
        while (j > 0) {
            int res = cmp(temp, arr + (j - 1) * size);
            if (options && options->order == FOSSIL_SORT_DESCENDING)
                res = -res;
            if (res < 0) {
                memcpy(arr + j * size, arr + (j - 1) * size, size);
                --j;
            } else {
                break;
            }
        }
        memcpy(arr + j * size, temp, size);
    }
    free(temp);
    return 0;
}

/**
 * @brief Sorts using the shell sort algorithm.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
int fossil_algorithm_sort_shell(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base || !cmp)
        return 0;

    char *arr = (char *)base;
    char *temp = (char *)malloc(size);
    if (!temp)
        return -1;

    // Using Shell's original gap sequence: n/2, n/4, ..., 1
    for (size_t gap = count / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < count; ++i) {
            memcpy(temp, arr + i * size, size);
            size_t j = i;
            while (j >= gap) {
                int res = cmp(temp, arr + (j - gap) * size);
                if (options && options->order == FOSSIL_SORT_DESCENDING)
                    res = -res;
                if (res < 0) {
                    memcpy(arr + j * size, arr + (j - gap) * size, size);
                    j -= gap;
                } else {
                    break;
                }
            }
            memcpy(arr + j * size, temp, size);
        }
    }
    free(temp);
    return 0;
}

/**
 * @brief Sorts using the radix sort algorithm.
 *
 * Only supports sorting arrays of unsigned integers (size == 1, 2, 4, or 8).
 * Ignores the cmp function; sorts in ascending or descending order based on options.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function (ignored).
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
int fossil_algorithm_sort_radix(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base)
        return 0;

    // Only support 1, 2, 4, or 8 byte unsigned types
    if (size != 1 && size != 2 && size != 4 && size != 8)
        return -1;

    unsigned char *arr = (unsigned char *)base;
    unsigned char *temp = (unsigned char *)malloc(count * size);
    if (!temp)
        return -1;

    size_t max_bits = size * 8;
    for (size_t byte = 0; byte < size; ++byte) {
        size_t count_bucket[256] = {0};

        // Count occurrences
        for (size_t i = 0; i < count; ++i)
            count_bucket[arr[i * size + byte]]++;

        // Compute prefix sums
        size_t pos[256];
        pos[0] = 0;
        for (size_t i = 1; i < 256; ++i)
            pos[i] = pos[i - 1] + count_bucket[i - 1];

        // Sort by current byte
        for (size_t i = 0; i < count; ++i) {
            unsigned char val = arr[i * size + byte];
            memcpy(temp + pos[val] * size, arr + i * size, size);
            pos[val]++;
        }

        // Copy back
        memcpy(arr, temp, count * size);
    }

    // If descending order requested, reverse array
    if (options && options->order == FOSSIL_SORT_DESCENDING) {
        for (size_t i = 0; i < count / 2; ++i) {
            fossil_swap_bytes((char *)arr + i * size, (char *)arr + (count - 1 - i) * size, size);
        }
    }

    free(temp);
    return 0;
}

/**
 * @brief Sorts using the counting sort algorithm.
 *
 * Only supports arrays of unsigned integers (size == 1, 2, or 4).
 * Ignores the cmp function; sorts in ascending or descending order based on options.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function (ignored).
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
int fossil_algorithm_sort_counting(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base)
        return 0;

    // Only support 1, 2, or 4 byte unsigned types
    if (size != 1 && size != 2 && size != 4)
        return -1;

    size_t max_value = 0;
    size_t i;

    // Find max value
    if (size == 1) {
        unsigned char *arr = (unsigned char *)base;
        for (i = 0; i < count; ++i)
            if (arr[i] > max_value) max_value = arr[i];
    } else if (size == 2) {
        unsigned short *arr = (unsigned short *)base;
        for (i = 0; i < count; ++i)
            if (arr[i] > max_value) max_value = arr[i];
    } else if (size == 4) {
        unsigned int *arr = (unsigned int *)base;
        for (i = 0; i < count; ++i)
            if (arr[i] > max_value) max_value = arr[i];
    }

    size_t *count_arr = (size_t *)calloc(max_value + 1, sizeof(size_t));
    if (!count_arr)
        return -1;

    // Count occurrences
    if (size == 1) {
        unsigned char *arr = (unsigned char *)base;
        for (i = 0; i < count; ++i)
            count_arr[arr[i]]++;
    } else if (size == 2) {
        unsigned short *arr = (unsigned short *)base;
        for (i = 0; i < count; ++i)
            count_arr[arr[i]]++;
    } else if (size == 4) {
        unsigned int *arr = (unsigned int *)base;
        for (i = 0; i < count; ++i)
            count_arr[arr[i]]++;
    }

    // Write sorted output
    size_t idx = 0;
    if (!options || options->order == FOSSIL_SORT_ASCENDING) {
        for (size_t val = 0; val <= max_value; ++val) {
            while (count_arr[val]--) {
                if (size == 1)
                    ((unsigned char *)base)[idx++] = (unsigned char)val;
                else if (size == 2)
                    ((unsigned short *)base)[idx++] = (unsigned short)val;
                else if (size == 4)
                    ((unsigned int *)base)[idx++] = (unsigned int)val;
            }
        }
    } else {
        for (long val = (long)max_value; val >= 0; --val) {
            while (count_arr[val]--) {
                if (size == 1)
                    ((unsigned char *)base)[idx++] = (unsigned char)val;
                else if (size == 2)
                    ((unsigned short *)base)[idx++] = (unsigned short)val;
                else if (size == 4)
                    ((unsigned int *)base)[idx++] = (unsigned int)val;
            }
        }
    }

    free(count_arr);
    return 0;
}

/**
 * @brief Sorts using the bubble sort algorithm (for educational/testing use).
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code.
 */
int fossil_algorithm_sort_bubble(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
)
{
    if (count <= 1 || !base || !cmp)
        return 0;

    char *arr = (char *)base;
    int swapped;
    for (size_t i = 0; i < count - 1; ++i) {
        swapped = 0;
        for (size_t j = 0; j < count - i - 1; ++j) {
            int res = cmp(arr + j * size, arr + (j + 1) * size);
            if (options && options->order == FOSSIL_SORT_DESCENDING)
                res = -res;
            if (res > 0) {
                fossil_swap_bytes(arr + j * size, arr + (j + 1) * size, size);
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
    return 0;
}

/**
 * @def FOSSIL_SORT_DEFAULT_OPTIONS
 * @brief Macro for default sorting options (ascending, unstable).
 */
#define FOSSIL_SORT_DEFAULT_OPTIONS \
    ((fossil_sort_options_t){ FOSSIL_SORT_ASCENDING, FOSSIL_SORT_UNSTABLE })