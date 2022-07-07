#include "heap_sort.h"

#include <stddef.h>

#include "util.h"

static size_t _parent_index(const size_t i) { return (i - 1) / 2; }

static size_t _left_child_index(const size_t i) { return 2 * i + 1; }

static size_t _right_child_index(const size_t i) { return 2 * i + 2; }

// x が左右のノードの大きいほう(y)より小さければ，x と y
// を交換するという操作を， x
// が子を持たなくなるかこの条件を満たさなくなるまで繰り返す．
static void _shift_down(int *array, const size_t length, const size_t index) {
    size_t i = index;
    while (_left_child_index(i) < length) {
        size_t child_index;
        int child_value;
        const size_t left = _left_child_index(i);
        const size_t right = _right_child_index(i);

        if (left == length - 1) {
            child_index = left;
            child_value = array[left];
        } else if (array[left] >= array[right]) {
            child_index = left;
            child_value = array[left];
        } else {
            child_index = right;
            child_value = array[right];
        }

        if (array[i] < child_value) {
            array[child_index] = array[i];
            array[i] = child_value;
            i = child_index;
        } else {
            return;
        }
    }
}

// 二分木において，葉以外のノード x に対して _shift_down()
// を行うことでヒープを構築する． 根に最大値をもつヒープを構築する．
static void _build_heap(int *array, const size_t length) {
    size_t i = _parent_index(length - 1);
    while (i--) {
        _shift_down(array, length, (size_t)i);
    }
}

// ヒープの根と最後尾の要素を交換して _shift_down によりヒープを回復する．
// ヒープの大きさをひとつずつ小さくしながら，後ろの要素から順に確定させる．
// 時間計算量は O(n log n)．
void heap_sort(int *array, const size_t length) {
    _build_heap(array, length);

    for (size_t i = length - 1; i > 0; i--) {
        swap(array, array + i);
        _shift_down(array, i, 0);
    }
}
