#include <gtest/gtest.h>

extern "C" {
#include "heap.h"
}

TEST(HeapTest, Test) { ASSERT_EQ(f(), 42); }
