#include "bubble_sort.h"

#include <stddef.h>

#include "util.h"

void bubble_sort(int *array, const size_t length) {
    for (size_t i = 0; i < length - 1; i++) {
        // 後ろから順に見ていき，より小さい値を前に持ってくる．
        // 外側のループが1回終わるごとに，最小値から小さい順に値が確定していく．
        // 計算量は O(n^2)
        for (size_t j = length - 1; j > i; j--) {
            if (array[j - 1] > array[j]) {
                swap(&array[j - 1], &array[j]);
            }
        }
    }
}
