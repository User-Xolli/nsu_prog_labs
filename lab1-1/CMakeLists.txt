cmake_minimum_required(VERSION 3.5.1)
project(lab1-1 C)

set(CMAKE_C_STANDARD 99)

set(SRC src/main.c src/ring_buffer.h src/ring_buffer.c src/search_substring.c src/search_substring.h)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(enable_warnings)
include(cpp_check)
include(test_runner)
include(enable_sanitizers)
