cmake_minimum_required(VERSION 3.0)
project("algorithms_for_exam")
add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(thirdparty)

add_custom_target(test DEPENDS algos COMMAND test_algos)

file(GLOB_RECURSE ALL_SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.h
)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT}
        -style=file
        -i
        ${ALL_SOURCE_FILES}
    )
endif()
