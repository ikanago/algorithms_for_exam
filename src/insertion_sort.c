#include "insertion_sort.h"
#include <stddef.h>

// 最良計算量は O(n)，最悪/平均計算量は O(n^2)
void insertion_sort(int *array, const size_t length) {
    for (size_t i = 1; i < length; i++) {
        const int target = array[i];
        // array[i] を挿入すべき位置
        size_t j = i;
        // array[i] を挿入すべき位置を探しながら，
        // array[i] より大きい要素をずらしていく
        while (j > 0 && target < array[j - 1]) {
            array[j] = array[j - 1];
            j--;
        }

        array[j] = target;
    }
}

