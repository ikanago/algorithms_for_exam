#include <gtest/gtest.h>
#include <stddef.h>

#include <climits>
#include <random>

extern "C" {
#include "binary_tree.h"
#include "quick_sort.h"
#include "util.h"
}

class RandomBinaryTreeTest : public testing::Test {
    std::random_device _seed_gen;
    std::default_random_engine _engine;
    std::uniform_int_distribution<int> _dist;

public:
    static constexpr size_t length = 1000;
    int array[length];

    RandomBinaryTreeTest() : _seed_gen(std::random_device()) {
        this->_engine = std::default_random_engine(this->_seed_gen());
        this->_dist = std::uniform_int_distribution<int>(INT_MIN, INT_MAX);
    }

    void SetUp() override {
        for (size_t i = 0; i < length; i++) {
            this->array[i] = this->_dist(this->_engine);
        }
    }
};

void assert_keeps_order(struct binary_tree_t *tree) {
    if (tree->lhs != NULL) {
        const int is_lhs_ok = tree->lhs->value <= tree->value;
        ASSERT_TRUE(is_lhs_ok);
    }
    if (tree->rhs != NULL) {
        const int is_rhs_ok = tree->value < tree->rhs->value;
        ASSERT_TRUE(is_rhs_ok);
    }
}

int is_sorted_traverse_inorder(
    struct binary_tree_t *tree, const int *data, size_t *has_checked) {
    if (tree == NULL) {
        return 1;
    }

    const int is_lhs_ok =
        is_sorted_traverse_inorder(tree->lhs, data, has_checked);
    const int is_current_ok = tree->value == data[*has_checked];
    *has_checked += 1;
    const int is_rhs_ok =
        is_sorted_traverse_inorder(tree->rhs, data, has_checked);

    return is_lhs_ok && is_current_ok && is_rhs_ok;
}

TEST(BinaryTreeTest, InsertKeepsOrdering) {
    const size_t length = 10;
    const int data[length] = {2, 5, -4, 0, 7, 8, -5, 7, -4, 1};
    struct binary_tree_t *tree = new_binary_tree(data[0]);

    for (size_t i = 1; i < length; i++) {
        insert_binary_tree(tree, data[i]);
    }

    traverse_preorder(tree, assert_keeps_order);
}

TEST(BinaryTreeTest, SortedByInorder) {
    const size_t length = 10;
    int data[length] = {2, 5, -4, 0, 7, 8, -5, 7, -4, 1};
    struct binary_tree_t *tree = new_binary_tree(data[0]);

    for (size_t i = 1; i < length; i++) {
        insert_binary_tree(tree, data[i]);
    }

    quick_sort(data, length);
    size_t has_checked = 0;
    ASSERT_TRUE(is_sorted_traverse_inorder(tree, data, &has_checked));
}

TEST_F(RandomBinaryTreeTest, SortedByInorder) {
    struct binary_tree_t *tree = new_binary_tree(this->array[0]);

    for (size_t i = 1; i < this->length; i++) {
        insert_binary_tree(tree, this->array[i]);
    }

    quick_sort(this->array, this->length);
    size_t has_checked = 0;
    ASSERT_TRUE(is_sorted_traverse_inorder(tree, this->array, &has_checked));
}

TEST_F(RandomBinaryTreeTest, InsertedItemExists) {
    struct binary_tree_t *tree = new_binary_tree(this->array[0]);

    for (size_t i = 1; i < this->length; i++) {
        insert_binary_tree(tree, this->array[i]);
    }

    for (size_t i = 0; i < this->length; i++) {
        ASSERT_TRUE(search_binary_tree(tree, this->array[i]));
    }
}

TEST(BinaryTreeTest, RemoveLeaf) {
    const size_t length = 10;
    int data[length] = {2, 5, -4, 0, 7, 8, -5, 7, -4, 1};
    struct binary_tree_t *tree = new_binary_tree(data[0]);

    for (size_t i = 1; i < length; i++) {
        insert_binary_tree(tree, data[i]);
    }
    tree = remove_binary_tree(tree, 1);

    traverse_preorder(tree, assert_keeps_order);
}

TEST(BinaryTreeTest, RemoveRoot) {
    const size_t length = 10;
    int data[length] = {2, 5, -4, 0, 7, 8, -5, 7, -4, 1};
    struct binary_tree_t *tree = new_binary_tree(data[0]);

    for (size_t i = 1; i < length; i++) {
        insert_binary_tree(tree, data[i]);
    }
    tree = remove_binary_tree(tree, 2);

    traverse_preorder(tree, assert_keeps_order);
}

TEST(BinaryTreeTest, RemoveMiddleNode) {
    const size_t length = 10;
    int data[length] = {2, 5, -4, 0, 7, 8, -5, 7, -4, 1};
    struct binary_tree_t *tree = new_binary_tree(data[0]);

    for (size_t i = 1; i < length; i++) {
        insert_binary_tree(tree, data[i]);
    }
    tree = remove_binary_tree(tree, 5);

    traverse_preorder(tree, assert_keeps_order);
}

TEST(BinaryTreeTest, RemoveRootOnlyTree) {
    const size_t length = 10;
    int data[length] = {2};
    struct binary_tree_t *tree = new_binary_tree(data[0]);

    tree = remove_binary_tree(tree, 2);
    ASSERT_EQ(tree, nullptr);
}
