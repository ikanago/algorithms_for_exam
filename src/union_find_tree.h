#include <stddef.h>

#ifndef _UNION_FIND_TREE_H
#define _UNION_FIND_TREE_H

struct uf_tree_t {
    size_t *roots;
    size_t *sizes;
};

struct uf_tree_t *new_uf_tree(const size_t size);

size_t root_uf_tree(const struct uf_tree_t *tree, const size_t x);

int same_uf_tree(struct uf_tree_t *tree, const size_t x, const size_t y);

void merge_uf_tree(struct uf_tree_t *tree, const size_t x, const size_t y);

#endif
