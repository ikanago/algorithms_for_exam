cmake_minimum_required(VERSION 3.0)

add_executable(
    test_algos
    EXCLUDE_FROM_ALL
    test_binary_tree.cc
    test_chaining_set.cc
    test_heap.cc
    test_linked_list.cc
    test_open_address_set.cc
    test_queue.cc
    test_sort.cc
    test_union_find_tree.cc
)
target_compile_features(test_algos PUBLIC cxx_std_17)

target_link_libraries(
    test_algos
    algos
    gtest
    gtest_main
)

target_include_directories(test_algos PUBLIC ${PROJECT_SOURCE_DIR}/src)
