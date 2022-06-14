#include <gtest/gtest.h>

extern "C" {
#include "queue.h"
#include "util.h"
}

TEST(QueueTest, Basic) {
    const size_t size = 4;
    struct queue_t *queue = new_queue(size);
    enqueue(queue, 3);
    enqueue(queue, 1);
    enqueue(queue, 4);
    enqueue(queue, 1);
    ASSERT_EQ(dequeue(queue), 3);
    enqueue(queue, 2);
    const int expected[5] = {3, 1, 4, 1, 2};
    ASSERT_TRUE(is_array_equal(queue->buffer, expected, size));
    ASSERT_EQ(queue->front, 1);
    ASSERT_EQ(queue->rear, 0);
}
