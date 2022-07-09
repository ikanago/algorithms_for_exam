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

void traverse_preorder(struct binary_tree_t *tree, traverse_handler_t handler);

#endif
