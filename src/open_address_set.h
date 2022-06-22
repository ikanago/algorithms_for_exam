#include <stddef.h>

#ifndef _OPEN_ADDRESS_SET_H
#define _OPEN_ADDRESS_SET_H

typedef size_t (*hash_func_t)(int, int, size_t);

size_t mod_hash_func_open_address(
    const int value, const int count, const size_t buffer_size);

enum status_t {
    EMPTY,
    OCCUPIED,
    DELETED,
};

struct entry_t {
    enum status_t status;
    int value;
};

struct open_address_set_t {
    struct entry_t *buffer;
    size_t buffer_size;
    size_t current_size;
    hash_func_t hash_func;
};

struct open_address_set_t *new_open_address_set(
    const size_t buffer_size, hash_func_t hash_func);

size_t size_open_address_set(const struct open_address_set_t *set);

int exists_open_address_set(
    const struct open_address_set_t *set, const int value);

void insert_open_address_set(struct open_address_set_t *set, const int value);

void delete_open_address_set(struct open_address_set_t *set, const int value);

void print_open_address_set(const struct open_address_set_t *set);

#endif
