cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_STANDARD 11)

set(LIB_SRC
    bubble_sort.c
    heap.c
    util.c
)

add_library(algos STATIC ${LIB_SRC})
target_include_directories(algos PRIVATE ${PROJECT_SOURCE_DIR}/src)
