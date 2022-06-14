#include <stddef.h>

#ifndef _QUEUE_H
#define _QUEUE_H

struct queue_t {
    int *buffer;
    size_t size;
    size_t front;
    size_t rear;
};

struct queue_t *new_queue(const size_t size);

int is_full_queue(const struct queue_t *queue);

int is_empty_queue(const struct queue_t *queue);

void enqueue(struct queue_t *queue, const int value);

int dequeue(struct queue_t *queue);

#endif
