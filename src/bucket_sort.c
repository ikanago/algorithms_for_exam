#include "bucket_sort.h"

#include <stddef.h>
#include <stdlib.h>

#include "queue.h"

static const size_t BUCKET_SIZE = 10;

static struct queue_t **new_buckets(const size_t bucket_size) {
    struct queue_t **buckets =
        (struct queue_t **)calloc(bucket_size, sizeof(struct queue_t *));
    if (buckets == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < bucket_size; i++) {
        struct queue_t *bucket = new_queue(BUCKET_SIZE);
        if (bucket == NULL) {
            return NULL;
        }
        buckets[i] = bucket;
    }
    return buckets;
}

// データは0以上であるとする．
// データの最大値を M-1 であるとすると，キューを M 個用意する．
// データ array[i]
// をインデックスとしてキューを選び，そのキューにデータをエンキューする．
// すべてのデータをエンキューしたら，前のキューから順にデータをデキューする．
// 時間計算量は O(n + M)．
void bucket_sort(int *array, const size_t length) {
    size_t max_element = 0;
    for (size_t i = 0; i < length; i++) {
        if ((size_t)array[i] > max_element) {
            max_element = array[i];
        }
    }

    const size_t bucket_size = max_element + 1;
    struct queue_t **buckets = new_buckets(bucket_size);
    for (size_t i = 0; i < length; i++) {
        enqueue(buckets[array[i]], array[i]);
    }

    size_t i = 0;
    for (size_t j = 0; j < bucket_size; j++) {
        while (!is_empty_queue(buckets[j])) {
            array[i] = dequeue(buckets[j]);
            i++;
        }
    }
}
