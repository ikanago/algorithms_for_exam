#include "merge_sort.h"

#include <stddef.h>
#include <stdlib.h>

static void merge(int *array, const size_t left, const size_t mid,
    const size_t right, int *working) {
    size_t i = left;
    size_t j = mid + 1;
    size_t k = 0;

    while (i <= mid && j <= right) {
        if (array[i] <= array[j]) {
            // 左側の配列の先頭のほうが小さいならば working に追加する．
            working[k] = array[i];
            // 左側の配列の先頭のインデックスを1つ進める．
            i++;
        } else {
            // 右側の配列の先頭のほうが小さいならば working に追加する．
            working[k] = array[j];
            // 右側の配列の先頭のインデックスを1つ進める．
            j++;
        }
        k++;
    }

    if (i == mid + 1) {
        // 左側が空ならば
        while (j <= right) {
            // 右側を空になるまで working に追加する．
            working[k] = array[j];
            j++;
            k++;
        }
    } else {
        // 右側が空ならば
        while (i <= mid) {
            // 左側を空になるまで working に追加する．
            working[k] = array[i];
            i++;
            k++;
        }
    }

    for (size_t l = left; l <= right; l++) {
        array[l] = working[l];
    }
}

static void merge_sort_inner(
    int *array, const size_t left, const size_t right, int *working) {
    if (left == right) {
        return;
    }

    const size_t mid = (left + right) / 2;
    // 配列を中央で分割し，それぞれについて再帰的にソートする．
    // 部分配列の大きさが1になったら再帰を停止する．
    merge_sort_inner(array, left, mid, working);
    merge_sort_inner(array, mid + 1, right, working);
    // 部分配列をマージする．
    merge(array, left, mid, right, working);
}

// 平均/最悪計算量は O(n log n)．
// 分割処理の計算量:
//   i 回め(1-indexed)の分割では 2^{i - 1} 回の分割を行う．
//   分割処理の合計回数は
//    ceil(log(n))
//        Σ  2^{i - 1} = n - 1
//       i=1
//   となる．1回の分割処理は分割位置を計算するだけなので O(1) であるから，
//   分割処理全体の計算量は O(n)．
// マージ処理の計算量:
//   各段階のマージは n 個のデータをコピーするから O(n)．
//   マージは ceil(log(n)) 段階行われるから，マージ処理全体の計算量は O(n log n)
void merge_sort(int *array, const size_t length) {
    int *working = (int *)calloc(length, sizeof(int));
    merge_sort_inner(array, 0, length - 1, working);
    free(working);
}
