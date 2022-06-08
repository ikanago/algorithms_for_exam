cmake_minimum_required(VERSION 3.0)

add_executable(
    test_algos
    EXCLUDE_FROM_ALL
    test_heap.cc
    test_sort.cc
)
target_compile_features(test_algos PUBLIC cxx_std_17)

target_link_libraries(
    test_algos
    algos
    gtest
    gtest_main
)

target_include_directories(test_algos PUBLIC ${PROJECT_SOURCE_DIR}/src)
