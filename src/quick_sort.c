#include "quick_sort.h"

#include <stddef.h>
#include <stdio.h>

#include "util.h"

static int partition(int *array, const int left, const int right) {
    const int pivot = right;
    int l = left;
    int r = right - 1;

    while (1) {
        // array[l] が array[pivot] 未満の間，l を1つ右に動かす．
        // l == pivot になっても，array[l] < array[pivot]
        // は0だからループは停止する．
        while (array[l] < array[pivot]) {
            l++;
        }
        // array[r] が array[pivot] 以上の間，r を1つ左に動かす．
        while (l <= r && array[r] >= array[pivot]) {
            r--;
        }

        if (l < r) {
            // l < r ならば，array[l] と array[r] を swap することで，
            // [left, l](閉区間) に array[pivot] 未満の要素が，
            // [r, pivot - 1] に array[pivot] 以上の要素が存在するようになる．
            swap(&array[l], &array[r]);
        } else {
            // l は array[pivot]
            // 以上の要素の位置で停止するから，上記の2つめのループ中に l == r
            // となった場合は，必ず r はもう1つ進んで r == l - 1 となる．
            break;
        }
    }

    // 上記の無限ループを break した時点では [left, r] に array[pivot]
    // 未満の要素が， [l, pivot - 1] に array[pivot] 以上の要素が存在する．
    // array[l] と array[pivot] を swap することで [left, pivot - 1] に
    // array[pivot] 未満の要素が， [pivot + 1, right] に array[pivot]
    // 以上の要素が存在するようになる．
    swap(&array[l], &array[pivot]);
    return l;
}

static void quick_sort_inner(int *array, const int left, const int right) {
    if (left < right) {
        // array[pivot] 未満の要素からなる領域と，array[pivot]
        // 以上の要素からなる領域に分割する．
        const int pivot = partition(array, left, right);
        // 分割した領域に対して，再帰的にソートする．
        quick_sort_inner(array, left, pivot - 1);
        quick_sort_inner(array, pivot + 1, right);
    }
}

// 平均計算量は O(n log n)．
// 最悪計算量は O(n^2)
// で，これはピボットがソート範囲の最大値あるいは最小値を取り続けた場合のものである．
// この実装では，ソート済みの配列に対して実行した場合がこれにあたる．
void quick_sort(int *array, const size_t length) {
    quick_sort_inner(array, 0, length - 1);
}
