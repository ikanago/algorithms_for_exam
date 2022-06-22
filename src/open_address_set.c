#include "open_address_set.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t mod_hash_func_open_address(
    const int value, const int count, const size_t buffer_size) {
    return (value + count) % buffer_size;
}

struct open_address_set_t *new_open_address_set(
    const size_t buffer_size, hash_func_t hash_func) {
    struct entry_t *buffer =
        (struct entry_t *)calloc(buffer_size, sizeof(struct entry_t));
    if (buffer == NULL) {
        return NULL;
    }

    struct open_address_set_t *set =
        (struct open_address_set_t *)malloc(sizeof(struct open_address_set_t));
    if (set == NULL) {
        free(buffer);
        return NULL;
    }

    set->buffer = buffer;
    set->buffer_size = buffer_size;
    set->current_size = 0;
    set->hash_func = hash_func;
    return set;
}

size_t size_open_address_set(const struct open_address_set_t *set) {
    return set->current_size;
}

enum search_status_t {
    // Found in the set.
    EXIST,
    // Not found in the set, but found where to insert.
    NOT_FOUND,
    // Not found in the set and no extra space to insert.
    FULL,
};

struct search_result_t {
    enum search_status_t status;
    size_t hash;
};

static struct search_result_t search_open_address_set(
    const struct open_address_set_t *set, const int value) {
    int count = 0;
    size_t hash = set->hash_func(value, count, set->buffer_size);
    const size_t initial_hash = hash;

    while (1) {
        const struct entry_t entry = set->buffer[hash];
        if (entry.status == OCCUPIED && entry.value == value) {
            struct search_result_t res = {EXIST, hash};
            return res;
        }
        if (entry.status == EMPTY) {
            struct search_result_t res = {NOT_FOUND, hash};
            return res;
        }

        count++;
        hash = set->hash_func(value, count, set->buffer_size);
        if (hash == initial_hash) {
            break;
        }
    }

    struct search_result_t res = {FULL, 0};
    return res;
}

int exists_open_address_set(
    const struct open_address_set_t *set, const int value) {
    const struct search_result_t res = search_open_address_set(set, value);
    return res.status == EXIST;
}

void insert_open_address_set(struct open_address_set_t *set, const int value) {
    const struct search_result_t res = search_open_address_set(set, value);
    if (res.status == EXIST || res.status == FULL) {
        return;
    }

    const struct entry_t entry = {OCCUPIED, value};
    set->buffer[res.hash] = entry;
    set->current_size++;
}

void delete_open_address_set(struct open_address_set_t *set, const int value) {
    const struct search_result_t res = search_open_address_set(set, value);
    if (res.status == NOT_FOUND) {
        return;
    }

    const struct entry_t entry = {DELETED, 0};
    set->buffer[res.hash] = entry;
    set->current_size--;
}

void print_open_address_set(const struct open_address_set_t *set) {
    printf("status: ");
    for (size_t i = 0; i < set->buffer_size; i++) {
        printf("%d, ", set->buffer[i].status);
    }
    puts("");
    printf("value : ");
    for (size_t i = 0; i < set->buffer_size; i++) {
        printf("%d, ", set->buffer[i].value);
    }
    puts("");
}
