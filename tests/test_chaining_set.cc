#include <gtest/gtest.h>

extern "C" {
#include "chaining_set.h"
}

TEST(ChainingSetInitTest, Insert) {
    struct chaining_set_t *set = new_chaining_set(10, mod_hash_func);
    ASSERT_NE(set, nullptr);

    const size_t n = 7;
    const int array[n] = {2, 12, -5, 33, -42, 33, 95};
    for (size_t i = 0; i < n; i++) {
        insert_chaining_set(set, array[i]);
    }

    for (size_t i = 0; i < n; i++) {
        ASSERT_TRUE(exists_chaining_set(set, array[i]));
    }
}
