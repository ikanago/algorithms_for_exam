#include "queue.h"

#include <stddef.h>
#include <stdlib.h>

struct queue_t *new_queue(const size_t size) {
    const size_t actual_size = size + 1;
    int *buffer = (int *)calloc(actual_size, sizeof(int));
    if (buffer == NULL) {
        return NULL;
    }

    struct queue_t *queue = (struct queue_t *)malloc(sizeof(struct queue_t));
    if (queue == NULL) {
        free(buffer);
        return NULL;
    }

    queue->buffer = buffer;
    queue->size = actual_size;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

int is_full_queue(const struct queue_t *queue) {
    return ((queue->rear + 1) % queue->size) == queue->front;
}

int is_empty_queue(const struct queue_t *queue) {
    return queue->front == queue->rear;
}

void enqueue(struct queue_t *queue, const int value) {
    if (is_full_queue(queue)) {
        return;
    }

    queue->buffer[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->size;
}

int dequeue(struct queue_t *queue) {
    if (is_empty_queue(queue)) {
        return 0;
    }

    const int value = queue->buffer[queue->front];
    queue->front = (queue->front + 1) % queue->size;
    return value;
}
