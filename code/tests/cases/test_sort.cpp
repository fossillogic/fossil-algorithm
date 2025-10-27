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
#include <fossil/pizza/framework.h>

#include "fossil/algorithm/framework.h"

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Utilities
// * * * * * * * * * * * * * * * * * * * * * * * *
// Setup steps for things like test fixtures and
// mock objects are set here.
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_SUITE(cpp_algorithm_fixture);

FOSSIL_SETUP(cpp_algorithm_fixture) {
    // Setup the test fixture
}

FOSSIL_TEARDOWN(cpp_algorithm_fixture) {
    // Teardown the test fixture
}

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Sort
// * * * * * * * * * * * * * * * * * * * * * * * *

static int cpp_cmp_int_asc(const void *a, const void *b) {
    int ai = *(const int *)a;
    int bi = *(const int *)b;
    return (ai > bi) - (ai < bi);
}

static int cpp_cmp_int_desc(const void *a, const void *b) {
    int ai = *(const int *)a;
    int bi = *(const int *)b;
    return (bi > ai) - (bi < ai);
}

FOSSIL_TEST(cpp_test_sort_auto_basic) {
    int arr[] = {5, 2, 9, 1, 5, 6};
    int expected[] = {1, 2, 5, 5, 6, 9};
    int status = fossil::algorithm::Sort::auto_sort(arr, 6, sizeof(int), cpp_cmp_int_asc);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}

FOSSIL_TEST(cpp_test_sort_quick_descending) {
    int arr[] = {3, 1, 4, 1, 5, 9};
    int expected[] = {9, 5, 4, 3, 1, 1};
    fossil_sort_options_t opts = { FOSSIL_SORT_DESCENDING, FOSSIL_SORT_UNSTABLE };
    int status = fossil::algorithm::Sort::quick_sort(arr, 6, sizeof(int), cpp_cmp_int_desc, &opts);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}

FOSSIL_TEST(cpp_test_sort_heap) {
    int arr[] = {8, 4, 6, 2, 7};
    int expected[] = {2, 4, 6, 7, 8};
    int status = fossil::algorithm::Sort::heap_sort(arr, 5, sizeof(int), cpp_cmp_int_asc);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}

FOSSIL_TEST(cpp_test_sort_insertion) {
    int arr[] = {10, 5, 3, 8};
    int expected[] = {3, 5, 8, 10};
    int status = fossil::algorithm::Sort::insertion_sort(arr, 4, sizeof(int), cpp_cmp_int_asc);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}

FOSSIL_TEST(cpp_test_sort_shell) {
    int arr[] = {9, 7, 5, 3, 1};
    int expected[] = {1, 3, 5, 7, 9};
    int status = fossil::algorithm::Sort::shell_sort(arr, 5, sizeof(int), cpp_cmp_int_asc);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}

FOSSIL_TEST(cpp_test_sort_radix_u32) {
    uint32_t arr[] = {100, 2, 50, 25, 75};
    uint32_t expected[] = {2, 25, 50, 75, 100};
    fossil_sort_options_t opts = { FOSSIL_SORT_ASCENDING, FOSSIL_SORT_UNSTABLE };
    int status = fossil::algorithm::Sort::radix_sort(arr, 5, sizeof(uint32_t), nullptr, &opts);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}

FOSSIL_TEST(cpp_test_sort_counting_u8) {
    uint8_t arr[] = {5, 1, 3, 2, 4};
    uint8_t expected[] = {1, 2, 3, 4, 5};
    fossil_sort_options_t opts = { FOSSIL_SORT_ASCENDING, FOSSIL_SORT_UNSTABLE };
    int status = fossil::algorithm::Sort::counting_sort(arr, 5, sizeof(uint8_t), nullptr, &opts);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}

FOSSIL_TEST(cpp_test_sort_bubble) {
    int arr[] = {4, 2, 3, 1};
    int expected[] = {1, 2, 3, 4};
    int status = fossil::algorithm::Sort::bubble_sort(arr, 4, sizeof(int), cpp_cmp_int_asc);
    ASSUME_ITS_TRUE(status == 0);
    ASSUME_ITS_TRUE(memcmp(arr, expected, sizeof(arr)) == 0);
}


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Pool
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_GROUP(cpp_sort_tests) {
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_auto_basic);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_quick_descending);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_heap);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_insertion);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_shell);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_radix_u32);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_counting_u8);
    FOSSIL_TEST_ADD(cpp_algorithm_fixture, cpp_test_sort_bubble);

    FOSSIL_TEST_REGISTER(cpp_algorithm_fixture);
} // end of tests
