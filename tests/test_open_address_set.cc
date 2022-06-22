#include <gtest/gtest.h>

extern "C" {
#include "open_address_set.h"
}

TEST(OpenAddressSetInitTest, Insert) {
    struct open_address_set_t *set =
        new_open_address_set(10, mod_hash_func_open_address);
    ASSERT_NE(set, nullptr);

    const size_t n = 7;
    const int array[n] = {2, 12, -5, 33, -42, 33, 95};
    for (size_t i = 0; i < n; i++) {
        insert_open_address_set(set, array[i]);
    }

    ASSERT_EQ(size_open_address_set(set), 6);

    for (size_t i = 0; i < n; i++) {
        ASSERT_TRUE(exists_open_address_set(set, array[i]));
    }
}

TEST(OpenAddressSetInitTest, Delete) {
    struct open_address_set_t *set =
        new_open_address_set(10, mod_hash_func_open_address);
    ASSERT_NE(set, nullptr);

    const size_t n = 7;
    const int array[n] = {2, 12, -5, 33, -42, 33, 95};
    for (size_t i = 0; i < n; i++) {
        insert_open_address_set(set, array[i]);
    }

    delete_open_address_set(set, 12);

    ASSERT_EQ(size_open_address_set(set), 5);

    const int expected[n - 1] = {2, -5, 33, -42, 33, 95};
    for (size_t i = 0; i < n - 1; i++) {
        ASSERT_TRUE(exists_open_address_set(set, expected[i]));
    }
}
