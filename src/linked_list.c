#include "linked_list.h"

static struct linked_list_cell_t *new_cell(const int value) {
    struct linked_list_cell_t *cell =
        (struct linked_list_cell_t *)malloc(sizeof(struct linked_list_cell_t));
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

void delete_linked_list(struct linked_list_t *list, const int value) {
    struct linked_list_cell_t *prev = NULL;
    struct linked_list_cell_t *target = list->head;
    while (target != NULL) {
        if (target->value == value) {
            if (target == list->head) {
                list->head = target->next;
            } else {
                prev->next = target->next;
            }
            free(target);
            return;
        }
        prev = target;
        target = target->next;
    }
}

void delete_front_linked_list(struct linked_list_t *list) {
    if (list->head == NULL) {
        return;
    }

    struct linked_list_cell_t *head = list->head;
    list->head = head->next;
    free(head);
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
