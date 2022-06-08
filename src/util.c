#include "util.h"

int is_array_equal(const int *arr, const int *other, const size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (arr[i] != other[i]) {
            return 0;
        }
    }
    return 1;
}

int is_sorted(const int *arr, const size_t length) {
    if (length < 1) {
        return 1;
    }

    for (size_t i = 1; i < length; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }
    return 1;
}
