#include <gtest/gtest.h>

extern "C" {
#include "heap.h"
#include "util.h"
}

TEST(HeapTest, Insertion) {
    const size_t num_data = 10;
    struct heap_t *heap = new_heap(num_data);
    const int data[10] = {14, 5, 3, 23, 27, 3, 15, 22, 9, 2};
    for (size_t i = 0; i < num_data; i++) {
        heap_insert(heap, data[i]);
    }

    const int expected[10] = {2, 3, 3, 14, 9, 5, 15, 23, 22, 27};
    ASSERT_TRUE(is_array_equal(heap->buffer, expected, num_data));
}

TEST(HeapTest, Min) {
    const size_t num_data = 10;
    struct heap_t *heap = new_heap(num_data);
    const int data[10] = {14, 5, 3, 23, 27, 3, 15, 22, 9, 2};
    for (size_t i = 0; i < num_data; i++) {
        heap_insert(heap, data[i]);
    }
    ASSERT_EQ(heap_min(heap), 2);
}

TEST(HeapTest, Deletion) {
    const size_t num_data = 10;
    struct heap_t *heap = new_heap(num_data);
    const int data[10] = {14, 5, 3, 23, 27, 3, 15, 22, 9, 2};
    for (size_t i = 0; i < num_data; i++) {
        heap_insert(heap, data[i]);
    }

    heap_delete(heap);

    {
        const int expected[9] = {3, 9, 3, 14, 27, 5, 15, 23, 22};
        ASSERT_TRUE(is_array_equal(heap->buffer, expected, num_data - 1));
    }

    heap_delete(heap);

    {
        const int expected[8] = {3, 9, 5, 14, 27, 22, 15, 23};
        ASSERT_TRUE(is_array_equal(heap->buffer, expected, num_data - 2));
    }
}
