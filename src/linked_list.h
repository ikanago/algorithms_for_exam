#include <stdlib.h>

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

struct linked_list_cell_t {
    int value;
    struct linked_list_cell_t *next;
};

struct linked_list_t {
    struct linked_list_cell_t *head;
};

struct linked_list_t *new_linked_list();

void prepend_linked_list(struct linked_list_t *list, const int value);

void delete_front_linked_list(struct linked_list_t *list);

struct linked_list_cell_t *search_linked_list(
    struct linked_list_t *list, const int value);

#endif
