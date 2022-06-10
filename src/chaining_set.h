#include "linked_list.h"
#include <stddef.h>

#ifndef _CHAINING_SET_H
#define _CHAINING_SET_H

typedef size_t (*hash_func_t)(int, size_t);

size_t mod_hash_func(const int value, const size_t bucket_size);

struct chaining_set_t {
    struct linked_list_t **buckets;
    size_t bucket_size;
    hash_func_t hash_func;
};

struct chaining_set_t *new_chaining_set(const size_t bucket_size, const hash_func_t hash);

int exists_chaining_set(struct chaining_set_t *set, const int value);

void insert_chaining_set(struct chaining_set_t *set, const int value);

void delete_chaining_set(struct chaining_set_t *set, const int value);

void print_chaining_set(struct chaining_set_t *set);

#endif

