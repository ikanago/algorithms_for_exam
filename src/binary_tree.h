#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

struct binary_tree_t {
    int value;
    struct binary_tree_t *lhs;
    struct binary_tree_t *rhs;
};

typedef void (*traverse_handler_t)(struct binary_tree_t *);

struct binary_tree_t *new_binary_tree(const int value);

void insert_binary_tree(struct binary_tree_t *tree, const int value);

int search_binary_tree(const struct binary_tree_t *tree, const int value);

struct binary_tree_t *remove_binary_tree(
    struct binary_tree_t *tree, const int value);

void print_binary_tree(const struct binary_tree_t *tree);

void traverse_preorder(struct binary_tree_t *tree, traverse_handler_t handler);

void traverse_inorder(struct binary_tree_t *tree, traverse_handler_t handler);

void traverse_postorder(struct binary_tree_t *tree, traverse_handler_t handler);

#endif
