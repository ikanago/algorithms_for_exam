#include <stddef.h>
#include <stdlib.h>

#ifndef _HEAP_H
#define _HEAP_H

struct heap_t {
    int* buffer;
    size_t size;
    size_t tail;
};

struct heap_t* new_heap(size_t size);

void heap_insert(struct heap_t* heap, const int data);

int heap_min(const struct heap_t* heap);

void heap_delete(struct heap_t* heap);

#endif

