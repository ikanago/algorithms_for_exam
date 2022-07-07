#include <stddef.h>

#ifndef _UTIL_H
#define _UTIL_H

void swap(int *a, int *b);

int is_array_equal(const int *array, const int *other, const size_t length);

int is_sorted(const int *array, const size_t length);

void print_array(const int *array, const size_t length);

#endif
