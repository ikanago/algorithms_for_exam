cmake_minimum_required(VERSION 3.0)

set(LIB_SRC
    heap.c
)

add_library(algos STATIC ${LIB_SRC})
target_compile_features(algos PUBLIC c_std_11)
target_include_directories(algos PRIVATE ${PROJECT_SOURCE_DIR}/src)
