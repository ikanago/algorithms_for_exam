#include "util.h"

void swap(int *a, int *b) {
    if (*a == *b) {
        return;
    }

    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int is_array_equal(const int *array, const int *other, const size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (array[i] != other[i]) {
            return 0;
        }
    }
    return 1;
}

int is_sorted(const int *array, const size_t length) {
    if (length < 1) {
        return 1;
    }

    for (size_t i = 1; i < length; i++) {
        if (array[i - 1] > array[i]) {
            return 0;
        }
    }
    return 1;
}
