cmake_minimum_required(VERSION 3.5.1)
project(lab2 C)

set(CMAKE_C_STANDARD 99)

set(SRC src/main.c src/next_permutation.h src/next_permutation.c src/number_string.h src/number_string.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(enable_warnings)
include(cpp_check)
include(test_runner)
include(enable_sanitizers)
