#include "linked_list.h"

static struct linked_list_cell_t *new_cell(const int value) {
    struct linked_list_cell_t *cell = (struct linked_list_cell_t *)malloc(sizeof(struct linked_list_cell_t));
    if (cell == NULL) {
        return NULL;
    }

    cell->value = value;
    cell->next = NULL;
    return cell;
}

struct linked_list_t *new_linked_list() {
    struct linked_list_t *list =
        (struct linked_list_t *)malloc(sizeof(struct linked_list_t));
    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    return list;
}

void prepend_linked_list(struct linked_list_t *list, const int value) {
    struct linked_list_cell_t *cell = new_cell(value);
    if (cell == NULL) {
        return;
    }

    cell->next = list->head;
    list->head = cell;
}

struct linked_list_cell_t *search_linked_list(
    struct linked_list_t *list, const int value) {
    struct linked_list_cell_t *cell = list->head;
    while (cell != NULL) {
        if (cell->value == value) {
            return cell;
        }
        cell = cell->next;
    }

    return NULL;
}
