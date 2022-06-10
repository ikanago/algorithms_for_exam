#include <gtest/gtest.h>

#include <climits>
#include <random>

extern "C" {
#include "bubble_sort.h"
#include "insertion_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "util.h"
}

class RandomSortTest : public testing::Test {
    std::random_device _seed_gen;
    std::default_random_engine _engine;
    std::uniform_int_distribution<int> _dist;

public:
    static constexpr size_t length = 1000;
    int array[length];

    RandomSortTest() : _seed_gen(std::random_device()) {
        this->_engine = std::default_random_engine(this->_seed_gen());
        this->_dist = std::uniform_int_distribution<int>(-INT_MIN, INT_MAX);
    }

    void SetUp() override {
        for (size_t i = 0; i < this->length; i++) {
            array[i] = this->_dist(this->_engine);
        }
    }
};

TEST(SortTest, BubbleSort) {
    const size_t length = 10;
    int array[length] = {14, 5, 3, 23, 27, 3, 15, 22, 9, 2};
    bubble_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}

TEST_F(RandomSortTest, BubbleSort) {
    ASSERT_FALSE(is_sorted(array, length));
    bubble_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}

TEST(SortTest, InsertionSort) {
    const size_t length = 10;
    int array[length] = {14, 5, 3, 23, 27, 3, 15, 22, 9, 2};
    insertion_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}

TEST_F(RandomSortTest, InsertionSort) {
    ASSERT_FALSE(is_sorted(array, length));
    insertion_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}

TEST(SortTest, QuickSort) {
    const size_t length = 10;
    int array[length] = {14, 5, 3, 23, 27, 3, 15, 22, 9, 2};
    quick_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}

TEST_F(RandomSortTest, QuickSort) {
    ASSERT_FALSE(is_sorted(array, length));
    quick_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}

TEST(SortTest, MergeSort) {
    const size_t length = 10;
    int array[length] = {14, 5, 3, 23, 27, 3, 15, 22, 9, 2};
    merge_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}

TEST_F(RandomSortTest, MergeSort) {
    ASSERT_FALSE(is_sorted(array, length));
    merge_sort(array, length);
    ASSERT_TRUE(is_sorted(array, length));
}
