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

TEST(UnionFindTreeTest, RandomMerge) {
    constexpr size_t size = 300;
    struct uf_tree_t *tree = new_uf_tree(size);

    auto is_merged = std::vector(size, std::vector(size, false));
    for (size_t i = 0; i < size; i++) {
        // Every element belongs to the same group with itself.
        is_merged[i][i] = true;
    }

    auto seed_gen = std::random_device();
    auto engine = std::default_random_engine(seed_gen());
    auto element_dist = std::uniform_int_distribution<size_t>(0, size - 1);

    constexpr size_t num_merges = 10000;
    for (size_t i = 0; i < num_merges; i++) {
        const auto x = element_dist(engine);
        const auto y = element_dist(engine);
        merge_uf_tree(tree, x, y);

        is_merged[x][y] = true;
        is_merged[y][x] = true;
        for (size_t k = 0; k < size; k++) {
            if (k == x || k == y) {
                // Already marked as true.
                continue;
            }

            if (is_merged[x][k]) {
                // x and k is in the same group, so do y and k.
                is_merged[y][k] = true;
                is_merged[k][y] = true;
            }
            if (is_merged[y][k]) {
                is_merged[x][k] = true;
                is_merged[k][x] = true;
            }
        }
    }

    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size; y++) {
            ASSERT_EQ(
                static_cast<bool>(same_uf_tree(tree, x, y)), is_merged[x][y]);
        }
    }
}
