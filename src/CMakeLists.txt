cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 11)

set(LIB_SRC
    bubble_sort.c
    bucket_sort.c
    chaining_set.c
    heap.c
    heap_sort.c
    insertion_sort.c
    linked_list.c
    merge_sort.c
    open_address_set.c
    queue.c
    quick_sort.c
    union_find_tree.c
    util.c
)

add_library(algos STATIC ${LIB_SRC})
target_include_directories(algos PRIVATE ${PROJECT_SOURCE_DIR}/src)
