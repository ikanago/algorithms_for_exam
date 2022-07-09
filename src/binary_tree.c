#include "binary_tree.h"

#include <stdlib.h>

struct binary_tree_t *new_binary_tree(const int value) {
    struct binary_tree_t *root =
        (struct binary_tree_t *)malloc(sizeof(struct binary_tree_t));
    if (root == NULL) {
        return NULL;
    }

    root->value = value;
    root->lhs = NULL;
    root->rhs = NULL;
    return root;
}

void insert_binary_tree(struct binary_tree_t *tree, const int value) {
    if (tree == NULL) {
        tree = new_binary_tree(value);
        return;
    }

    struct binary_tree_t *current = tree;
    while (1) {
        if (value <= current->value) {
            if (current->lhs == NULL) {
                current->lhs = new_binary_tree(value);
                return;
            }
            current = current->lhs;
        } else {
            if (current->rhs == NULL) {
                current->rhs = new_binary_tree(value);
                return;
            }
            current = current->rhs;
        }
    }
}

void traverse_preorder(struct binary_tree_t *tree, traverse_handler_t handler) {
    if (tree == NULL) {
        return;
    }

    handler(tree);
    traverse_preorder(tree->lhs, handler);
    traverse_preorder(tree->rhs, handler);
}
