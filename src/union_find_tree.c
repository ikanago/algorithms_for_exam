#include "union_find_tree.h"

#include <stddef.h>
#include <stdlib.h>

struct uf_tree_t *new_uf_tree(const size_t size) {
    size_t *roots = (size_t *)calloc(size, sizeof(size_t));
    if (roots == NULL) {
        return NULL;
    }

    size_t *sizes = (size_t *)calloc(size, sizeof(size_t));
    if (sizes == NULL) {
        free(roots);
        return NULL;
    }

    struct uf_tree_t *tree =
        (struct uf_tree_t *)malloc(sizeof(struct uf_tree_t));
    if (tree == NULL) {
        free(roots);
        free(sizes);
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        roots[i] = i;
        sizes[i] = 1;
    }
    tree->roots = roots;
    tree->sizes = sizes;
    return tree;
}

size_t root_uf_tree(const struct uf_tree_t *tree, const size_t x) {
    if (tree->roots[x] == x) {
        return x;
    } else {
        const size_t root = root_uf_tree(tree, tree->roots[x]);
        tree->roots[x] = root;
        return root;
    }
}

int same_uf_tree(struct uf_tree_t *tree, const size_t x, const size_t y) {
    return root_uf_tree(tree, x) == root_uf_tree(tree, y);
}

void merge_uf_tree(struct uf_tree_t *tree, const size_t x, const size_t y) {
    size_t x_root = root_uf_tree(tree, x);
    size_t y_root = root_uf_tree(tree, y);
    if (x_root == y_root) {
        return;
    }

    if (tree->sizes[x_root] < tree->sizes[y_root]) {
        size_t tmp = x_root;
        x_root = y_root;
        y_root = tmp;
    }

    tree->roots[y_root] = x_root;
    tree->sizes[x_root] += tree->sizes[y_root];
}
