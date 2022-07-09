#include <gtest/gtest.h>
#include <stddef.h>

extern "C" {
#include "binary_tree.h"
#include "quick_sort.h"
#include "util.h"
}

#include <iostream>
void assert_keeps_order(struct binary_tree_t *tree) {
    std::cout << tree->value << " lhs: " << tree->lhs << " rhs: " << tree->rhs
              << std::endl;
    if (tree->lhs != NULL) {
        std::cout << "lhs: " << tree->lhs->value << std::endl;
        const int is_lhs_ok = tree->lhs->value <= tree->value;
        ASSERT_TRUE(is_lhs_ok);
    }
    if (tree->rhs != NULL) {
        std::cout << "rhs: " << tree->rhs->value << std::endl;
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
