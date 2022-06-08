#include "heap.h"

#include <limits.h>

static size_t _parent_index(const size_t i) { return (i - 1) / 2; }

static size_t _left_child_index(const size_t i) { return 2 * i + 1; }

static size_t _right_child_index(const size_t i) { return 2 * i + 2; }

struct heap_t *new_heap(size_t size) {
    struct heap_t *heap = (struct heap_t *)malloc(sizeof(struct heap_t));
    if (heap == NULL) {
        return NULL;
    }

    int *buffer = (int *)calloc(size, sizeof(int));
    if (buffer == NULL) {
        return NULL;
    }

    heap->buffer = buffer;
    heap->size = size;
    heap->tail = 0;
    return heap;
}

void heap_insert(struct heap_t *heap, const int data) {
    if (heap->tail == heap->size) {
        return;
    }

    heap->tail += 1;
    heap->buffer[heap->tail - 1] = data;
    size_t i = heap->tail - 1;
    while (i != 0) {
        if (heap->buffer[i] < heap->buffer[_parent_index(i)]) {
            const size_t p = _parent_index(i);
            heap->buffer[i] = heap->buffer[p];
            heap->buffer[p] = data;
            i = p;
        } else {
            return;
        }
    }
}

int heap_min(const struct heap_t *heap) {
    if (heap->tail == 0) {
        return INT_MIN;
    }
    return heap->buffer[0];
}

void heap_delete(struct heap_t *heap) {
    if (heap->tail == 0) {
        return;
    }

    if (heap->tail == 1) {
        heap->tail = 0;
        return;
    }

    heap->buffer[0] = heap->buffer[heap->tail - 1];
    heap->tail -= 1;

    size_t i = 0;
    while (_left_child_index(i) < heap->tail) {
        size_t child_index;
        int child_value;
        const size_t left = _left_child_index(i);
        const size_t right = _right_child_index(i);
        if (left == heap->tail - 1) {
            child_index = left;
            child_value = heap->buffer[child_index];
        } else if (heap->buffer[left] <= heap->buffer[right]) {
            child_index = left;
            child_value = heap->buffer[child_index];
        } else {
            child_index = right;
            child_value = heap->buffer[child_index];
        }

        if (heap->buffer[i] > child_value) {
            heap->buffer[child_index] = heap->buffer[i];
            heap->buffer[i] = child_value;
            i = child_index;
        } else {
            return;
        }
    }
}
