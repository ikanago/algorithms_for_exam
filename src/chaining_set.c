#include "chaining_set.h"
#include <stdlib.h>
#include "linked_list.h"

size_t mod_hash_func(const int value, const size_t bucket_size) {
    return value % bucket_size;
}

struct chaining_set_t *new_chaining_set(const size_t bucket_size,  const hash_func_t hash_func) {
    struct linked_list_t **buckets = (struct linked_list_t **)calloc(bucket_size, sizeof(struct linked_list_t *));
    if (buckets == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < bucket_size; i++) {
        struct linked_list_t *bucket = (struct linked_list_t *)malloc(sizeof(struct linked_list_t));
        if (bucket == NULL) {
            return NULL;
        }
        buckets[i] = bucket;
    }

    struct chaining_set_t *set = (struct chaining_set_t *)malloc(sizeof(struct chaining_set_t));
    if (set == NULL) {
        return NULL;
    }

    set->buckets = buckets;
    set->bucket_size = bucket_size;
    set->hash_func = hash_func;
    return set;
}

static int exists_chaining_set_by_hash(struct chaining_set_t *set, const int value, const int hash) {
    if (search_linked_list(set->buckets[hash], value) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int exists_chaining_set(struct chaining_set_t *set, const int value) {
    const size_t bucket = set->hash_func(value, set->bucket_size);
    return exists_chaining_set_by_hash(set, value, bucket);
}

void insert_chaining_set(struct chaining_set_t *set, const int value) {
    const size_t bucket = set->hash_func(value, set->bucket_size);
    if (!exists_chaining_set_by_hash(set, value, bucket)) {
        prepend_linked_list(set->buckets[bucket], value);
    }
}

void delete_chaininng_set(struct chaining_set_t *set, const int value);

#include <stdio.h>
void print_chaining_set(struct chaining_set_t *set) {
    for (size_t b = 0; b < set->bucket_size; b++) {
        struct linked_list_t *list = set->buckets[b];
        printf("%lu: ", b);
        for (struct linked_list_cell_t *cell = list->head; cell != NULL; cell = cell->next) {
            printf("%d, ", cell->value);
        }
        puts("");
    }
}

