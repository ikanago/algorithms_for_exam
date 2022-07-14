#include "binary_tree.h"

#include <stdio.h>
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

// 平均時間計算量は O(log n)．
// 最悪時間計算量は，これまでにデータが昇順または降順に挿入されていた場合で，O(n)．
void insert_binary_tree(struct binary_tree_t *tree, const int value) {
    if (tree == NULL) {
        tree = new_binary_tree(value);
        return;
    }

    struct binary_tree_t *current = tree;
    while (1) {
        if (value <= current->value) {
            // 左の部分木に挿入する．
            if (current->lhs == NULL) {
                // 左の子ノードが存在しなければ，そこに挿入する．
                current->lhs = new_binary_tree(value);
                return;
            }
            current = current->lhs;
        } else {
            // 右の部分木に挿入する．
            if (current->rhs == NULL) {
                // 右の子ノードが存在しなければ，そこに挿入する．
                current->rhs = new_binary_tree(value);
                return;
            }
            current = current->rhs;
        }
    }
}

int search_binary_tree(const struct binary_tree_t *tree, const int value) {
    const struct binary_tree_t *current = tree;
    while (current != NULL) {
        if (current->value == value) {
            return 1;
        }
        if (value < current->value) {
            current = current->lhs;
        } else {
            current = current->rhs;
        }
    }
    return 0;
}

static int is_leaf(const struct binary_tree_t *node) {
    return node->lhs == NULL && node->rhs == NULL;
}

static int has_two_children(const struct binary_tree_t *node) {
    return node->lhs != NULL && node->rhs != NULL;
}

enum direction_t {
    LEFT,
    RIGHT,
    NONE,
};

// `tree` において，高々1つの子をもつ `node` を削除する．
// `parent` は `node` の親へのポインタである．
static void remove_node_with_0_or_1_child(struct binary_tree_t **tree,
    struct binary_tree_t *node, struct binary_tree_t *parent,
    enum direction_t direction) {
    if (has_two_children(node)) {
        // この関数は子を2つ以上もつノードを対象にしていない．
        return;
    }

    // `node` を削除した位置へ移動させるノード．
    struct binary_tree_t *filling;
    if (is_leaf(node)) {
        filling = NULL;
    } else if (node->lhs == NULL) {
        filling = node->rhs;
    } else {
        filling = node->lhs;
    }

    if (parent == NULL) {
        *tree = filling;
    } else {
        if (direction == LEFT) {
            parent->lhs = filling;
        } else {
            parent->rhs = filling;
        }
    }

    free(node);
    return;
}

// `tree` から `value` を値としてもつノードを探索し，削除する．
// 処理後の二分探索木の根のポインタを返す．
// 平均時間計算量は O(log n)．
// 最悪時間計算量は O(n)．
struct binary_tree_t *remove_binary_tree(
    struct binary_tree_t *tree, const int value) {
    struct binary_tree_t *parent = NULL;
    struct binary_tree_t *node = tree;
    // `node` が `parent` の左右どちらの子であるかを指定する．
    enum direction_t direction = NONE;
    while (node != NULL) {
        if (value < node->value) {
            parent = node;
            node = node->lhs;
            direction = LEFT;
            continue;
        } else if (node->value < value) {
            parent = node;
            node = node->rhs;
            direction = RIGHT;
            continue;
        }

        // 以下は削除すべきノードを発見した場合の処理である．
        if (!has_two_children(node)) {
            remove_node_with_0_or_1_child(&tree, node, parent, direction);
            return tree;
        }

        // 削除すべきノードが子を2つもつときは，右部分木からその中で最小値をもつノードを探索し，削除するノードの位置に移動する．
        struct binary_tree_t *rhs_minimum = node->rhs;
        parent = node;
        direction = RIGHT;
        while (rhs_minimum->lhs != NULL) {
            parent = rhs_minimum;
            rhs_minimum = rhs_minimum->lhs;
            direction = LEFT;
        }
        // `node` が指す位置に `rhs_minimum` を移動する．
        // `rhs_minimum` が指すノードは削除するため，`rhs_minimum` がもつ値を
        // `node` に移動するだけでよい．
        node->value = rhs_minimum->value;
        remove_node_with_0_or_1_child(&tree, rhs_minimum, parent, direction);
        break;
    }
    return tree;
}

static void print_binary_tree_inner(
    const struct binary_tree_t *tree, const int depth) {
    if (tree == NULL) {
        return;
    }

    print_binary_tree_inner(tree->rhs, depth + 1);
    printf("%*s%d\n", depth * 2, "", tree->value);
    print_binary_tree_inner(tree->lhs, depth + 1);
}

void print_binary_tree(const struct binary_tree_t *tree) {
    print_binary_tree_inner(tree, 0);
}

// 行きがけ順で再帰的に `handler()` を各ノードに対して実行する．
void traverse_preorder(struct binary_tree_t *tree, traverse_handler_t handler) {
    if (tree == NULL) {
        return;
    }

    handler(tree);
    traverse_preorder(tree->lhs, handler);
    traverse_preorder(tree->rhs, handler);
}

// 通りがけ順で再帰的に `handler()` を各ノードに対して実行する．
void traverse_inorder(struct binary_tree_t *tree, traverse_handler_t handler) {
    if (tree == NULL) {
        return;
    }

    traverse_preorder(tree->lhs, handler);
    handler(tree);
    traverse_preorder(tree->rhs, handler);
}

// 帰りがけ順で再帰的に `handler()` を各ノードに対して実行する．
void traverse_postorder(
    struct binary_tree_t *tree, traverse_handler_t handler) {
    if (tree == NULL) {
        return;
    }

    traverse_preorder(tree->lhs, handler);
    traverse_preorder(tree->rhs, handler);
    handler(tree);
}
