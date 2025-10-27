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
#ifndef FOSSIL_ALGORITHM_SORT_H
#define FOSSIL_ALGORITHM_SORT_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// ======================================================
// Fossil Algorithm Sort — Framework
// ======================================================

/**
 * @typedef fossil_compare_fn
 * @brief Function pointer type for comparison functions used in sorting.
 *
 * The comparison function should return:
 *   - Negative value if a < b
 *   - Zero if a == b
 *   - Positive value if a > b
 *
 * @param a Pointer to the first element.
 * @param b Pointer to the second element.
 * @return int Comparison result.
 */
typedef int (*fossil_compare_fn)(const void *a, const void *b);

/**
 * @enum fossil_sort_order
 * @brief Specifies the desired sort order.
 *
 * - FOSSIL_SORT_ASCENDING: Sort in ascending order.
 * - FOSSIL_SORT_DESCENDING: Sort in descending order.
 */
typedef enum fossil_sort_order {
    FOSSIL_SORT_ASCENDING,   /**< Ascending order */
    FOSSIL_SORT_DESCENDING   /**< Descending order */
} fossil_sort_order_t;

/**
 * @enum fossil_sort_stability
 * @brief Indicates whether the sorting algorithm should be stable.
 *
 * - FOSSIL_SORT_UNSTABLE: Unstable sort (may reorder equal elements).
 * - FOSSIL_SORT_STABLE: Stable sort (preserves order of equal elements).
 */
typedef enum fossil_sort_stability {
    FOSSIL_SORT_UNSTABLE,    /**< Unstable sort */
    FOSSIL_SORT_STABLE       /**< Stable sort */
} fossil_sort_stability_t;

/**
 * @struct fossil_sort_options
 * @brief Options for configuring sorting behavior.
 *
 * Contains fields for specifying sort order and stability.
 */
typedef struct fossil_sort_options {
    fossil_sort_order_t order;      /**< Desired sort order */
    fossil_sort_stability_t stable; /**< Stability requirement */
} fossil_sort_options_t;

/**
 * @brief Automatically selects and applies the optimal sorting algorithm.
 *
 * Chooses the best algorithm based on input size and options.
 * Uses insertion sort for small arrays, merge sort for stable sort,
 * and quicksort otherwise.
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
);

/**
 * @brief Sorts using the quicksort algorithm.
 *
 * Performs an in-place quicksort. Supports ascending/descending order.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_quick(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

/**
 * @brief Sorts using the merge sort algorithm.
 *
 * Performs a stable merge sort. Supports ascending/descending order.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_merge(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

/**
 * @brief Sorts using the heap sort algorithm.
 *
 * Performs an in-place heap sort. Supports ascending/descending order.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_heap(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

/**
 * @brief Sorts using the insertion sort algorithm.
 *
 * Performs an in-place insertion sort. Supports ascending/descending order.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_insertion(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

/**
 * @brief Sorts using the shell sort algorithm.
 *
 * Performs an in-place shell sort. Supports ascending/descending order.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_shell(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

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
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_radix(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

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
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_counting(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

/**
 * @brief Sorts using the bubble sort algorithm (for educational/testing use).
 *
 * Performs an in-place bubble sort. Supports ascending/descending order.
 *
 * @param base Pointer to the array to sort.
 * @param count Number of elements.
 * @param size Size of each element.
 * @param cmp Comparison function.
 * @param options Pointer to sorting options.
 * @return int Status code (0 for success).
 */
int fossil_algorithm_sort_bubble(
    void *base,
    size_t count,
    size_t size,
    fossil_compare_fn cmp,
    const fossil_sort_options_t *options
);

/**
 * @def FOSSIL_SORT_DEFAULT_OPTIONS
 * @brief Macro for default sorting options (ascending, unstable).
 */
#define FOSSIL_SORT_DEFAULT_OPTIONS \
    ((fossil_sort_options_t){ FOSSIL_SORT_ASCENDING, FOSSIL_SORT_UNSTABLE })

#ifdef __cplusplus
}

namespace fossil {

    namespace algorithm {

        /**
         * @brief RAII-friendly C++ wrapper for Fossil sorting algorithms.
         *
         * Provides static methods to sort arrays using various algorithms.
         * All methods are thin wrappers around the C API, accepting raw pointers
         * and sorting options. Default options are used if none are provided.
         *
         * Usage:
         *   - Pass a pointer to the array, element count, element size, comparator, and options.
         *   - Sorting is performed in-place.
         *   - Returns 0 on success, non-zero on error.
         */
        class Sort
        {
        public:
            /**
             * @brief Automatically selects and applies the optimal sorting algorithm.
             *
             * Chooses the best algorithm based on input size and options.
             * Uses insertion sort for small arrays, merge sort for stable sort,
             * and quicksort otherwise.
             *
             * @param base Pointer to the array to sort.
             * @param count Number of elements in the array.
             * @param size Size of each element.
             * @param cmp Comparison function.
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int auto_sort(void* base, size_t count, size_t size,
             fossil_compare_fn cmp,
             const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_auto(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
            }

            /**
             * @brief Sorts using the quicksort algorithm.
             *
             * Performs an in-place quicksort. Supports ascending/descending order.
             *
             * @param base Pointer to the array to sort.
             * @param count Number of elements.
             * @param size Size of each element.
             * @param cmp Comparison function.
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int quick_sort(void* base, size_t count, size_t size,
              fossil_compare_fn cmp,
              const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_quick(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
            }

            /**
             * @brief Sorts using the merge sort algorithm.
             *
             * Performs a stable merge sort. Supports ascending/descending order.
             *
             * @param base Pointer to the array to sort.
             * @param count Number of elements.
             * @param size Size of each element.
             * @param cmp Comparison function.
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int merge_sort(void* base, size_t count, size_t size,
              fossil_compare_fn cmp,
              const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_merge(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
            }

            /**
             * @brief Sorts using the heap sort algorithm.
             *
             * Performs an in-place heap sort. Supports ascending/descending order.
             *
             * @param base Pointer to the array to sort.
             * @param count Number of elements.
             * @param size Size of each element.
             * @param cmp Comparison function.
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int heap_sort(void* base, size_t count, size_t size,
             fossil_compare_fn cmp,
             const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_heap(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
            }

            /**
             * @brief Sorts using the insertion sort algorithm.
             *
             * Performs an in-place insertion sort. Supports ascending/descending order.
             *
             * @param base Pointer to the array to sort.
             * @param count Number of elements.
             * @param size Size of each element.
             * @param cmp Comparison function.
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int insertion_sort(void* base, size_t count, size_t size,
              fossil_compare_fn cmp,
              const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_insertion(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
            }

            /**
             * @brief Sorts using the shell sort algorithm.
             *
             * Performs an in-place shell sort. Supports ascending/descending order.
             *
             * @param base Pointer to the array to sort.
             * @param count Number of elements.
             * @param size Size of each element.
             * @param cmp Comparison function.
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int shell_sort(void* base, size_t count, size_t size,
              fossil_compare_fn cmp,
              const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_shell(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
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
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int radix_sort(void* base, size_t count, size_t size,
              fossil_compare_fn cmp,
              const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_radix(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
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
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int counting_sort(void* base, size_t count, size_t size,
             fossil_compare_fn cmp,
             const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_counting(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
            }

            /**
             * @brief Sorts using the bubble sort algorithm (for educational/testing use).
             *
             * Performs an in-place bubble sort. Supports ascending/descending order.
             *
             * @param base Pointer to the array to sort.
             * @param count Number of elements.
             * @param size Size of each element.
             * @param cmp Comparison function.
             * @param options Pointer to sorting options (optional).
             * @return int Status code (0 for success).
             */
            static int bubble_sort(void* base, size_t count, size_t size,
               fossil_compare_fn cmp,
               const fossil_sort_options_t* options = nullptr)
            {
                return fossil_algorithm_sort_bubble(
                base,
                count,
                size,
                cmp,
                options ? options : &FOSSIL_SORT_DEFAULT_OPTIONS
                );
            }
        };

    } // namespace bluecrab

} // namespace fossil

#endif

#endif /* FOSSIL_CRABDB_FRAMEWORK_H */
