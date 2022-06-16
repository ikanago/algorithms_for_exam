#include <gtest/gtest.h>

#include <random>
#include <vector>

extern "C" {
#include "union_find_tree.h"
#include "util.h"
}

TEST(UnionFindTreeTest, InitialRootIsSelf) {
    constexpr size_t size = 10;
    struct uf_tree_t *tree = new_uf_tree(size);

    for (size_t i = 0; i < size; i++) {
        ASSERT_EQ(root_uf_tree(tree, i), i);
    }
}

TEST(UnionFindTreeTest, InitializedSeparatedGroup) {
    constexpr size_t size = 10;
    struct uf_tree_t *tree = new_uf_tree(size);

    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (i == j) {
                ASSERT_TRUE(same_uf_tree(tree, i, j));
            } else {
                ASSERT_FALSE(same_uf_tree(tree, i, j));
            }
        }
    }
}

#include <iostream>
TEST(UnionFindTreeTest, RandomMerge) {
    constexpr size_t size = 1000;
    struct uf_tree_t *tree = new_uf_tree(size);

    auto merged_pair = std::vector<std::pair<size_t, size_t>>();
    for (size_t i = 0; i < size; i++) {
        // Every element belongs to the same group with itself.
        merged_pair.push_back({i, i});
    }

    auto seed_gen = std::random_device();
    auto engine = std::default_random_engine(seed_gen());
    auto element_dist = std::uniform_int_distribution<size_t>(0, size - 1);

    constexpr size_t num_merges = 100000;
    for (size_t i = 0; i < num_merges; i++) {
        const auto x = element_dist(engine);
        const auto y = element_dist(engine);
        merged_pair.push_back({x, y});
        merge_uf_tree(tree, x, y);
    }

    for (const auto &pair : merged_pair) {
        const auto [x, y] = pair;
        // Only tests merged elements are in the same group.
        // But there should be elements in the same group that is not merged
        // directly.
        ASSERT_TRUE(same_uf_tree(tree, x, y));
    }
}
