#include <gtest/gtest.h>

extern "C" {
#include "linked_list.h"
}

class LinkedListSearchTest : public testing::Test {
public:
    struct linked_list_t* list;

    LinkedListSearchTest() { this->list = new_linked_list(); }

    void SetUp() override {
        prepend_linked_list(this->list, 3);
        prepend_linked_list(this->list, 1);
        prepend_linked_list(this->list, 4);
        prepend_linked_list(this->list, 1);
        prepend_linked_list(this->list, 5);
        prepend_linked_list(this->list, 9);
    }
};

TEST(LinkedListTest, Prepend) {
    struct linked_list_t* list = new_linked_list();
    prepend_linked_list(list, 3);
    prepend_linked_list(list, 1);
    prepend_linked_list(list, 4);
    prepend_linked_list(list, 1);
    prepend_linked_list(list, 5);
    prepend_linked_list(list, 9);

    const int expected[6] = {9, 5, 1, 4, 1, 3};
    size_t i = 0;
    for (struct linked_list_cell_t* cell = list->head; cell != NULL;
         cell = cell->next) {
        ASSERT_EQ(cell->value, expected[i]);
        i++;
    }
}

TEST_F(LinkedListSearchTest, Search) {
    struct linked_list_cell_t* cell = search_linked_list(this->list, 4);
    ASSERT_NE(cell, nullptr);
}

TEST_F(LinkedListSearchTest, MatchFirst) {
    struct linked_list_cell_t* cell = search_linked_list(this->list, 1);
    ASSERT_NE(cell, nullptr);
    ASSERT_EQ(cell->next->value, 4);
}

TEST_F(LinkedListSearchTest, NotFount) {
    struct linked_list_cell_t* cell = search_linked_list(this->list, 42);
    ASSERT_EQ(cell, nullptr);
}
