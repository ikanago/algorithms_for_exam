#include "chaining_set.h"

#include <stdlib.h>

#include "linked_list.h"

size_t mod_hash_func_chaining(const int value, const size_t bucket_size) {
    return value % bucket_size;
}

// チェイニング法(外部ハッシュ法，オープンハッシュ法)．
// 同じハッシュ値を持つデータを連結リストに格納する．
// 保持する連結リストの個数を B とすると，挿入，探索，削除の平均計算量は O(n /
// B) となり， B が十分に大きいときは O(1) とみなせる．
struct chaining_set_t *new_chaining_set(
    const size_t bucket_size, const hash_func_t hash_func) {
    struct linked_list_t **buckets = (struct linked_list_t **)calloc(
        bucket_size, sizeof(struct linked_list_t *));
    if (buckets == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < bucket_size; i++) {
        struct linked_list_t *bucket = new_linked_list();
        if (bucket == NULL) {
            return NULL;
        }
        buckets[i] = bucket;
    }

    struct chaining_set_t *set =
        (struct chaining_set_t *)malloc(sizeof(struct chaining_set_t));
    if (set == NULL) {
        return NULL;
    }

    set->buckets = buckets;
    set->bucket_size = bucket_size;
    set->current_size = 0;
    set->hash_func = hash_func;
    return set;
}

size_t size_chaining_set(const struct chaining_set_t *set) {
    return set->current_size;
}

static int exists_chaining_set_by_hash(
    const struct chaining_set_t *set, const int value, const int hash) {
    if (search_linked_list(set->buckets[hash], value) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int exists_chaining_set(const struct chaining_set_t *set, const int value) {
    const size_t bucket = set->hash_func(value, set->bucket_size);
    return exists_chaining_set_by_hash(set, value, bucket);
}

void insert_chaining_set(struct chaining_set_t *set, const int value) {
    const size_t bucket = set->hash_func(value, set->bucket_size);
    if (!exists_chaining_set_by_hash(set, value, bucket)) {
        prepend_linked_list(set->buckets[bucket], value);
        set->current_size++;
    }
}

void delete_chaining_set(struct chaining_set_t *set, const int value) {
    const size_t bucket = set->hash_func(value, set->bucket_size);
    if (exists_chaining_set_by_hash(set, value, bucket)) {
        delete_linked_list(set->buckets[bucket], value);
        set->current_size--;
    }
}
