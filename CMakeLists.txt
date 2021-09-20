cmake_minimum_required(VERSION 3.16)
project(gb_cl)

set(CMAKE_CXX_STANDARD 17)

add_library(lib_poly INTERFACE)

target_include_directories(lib_poly INTERFACE src)

add_executable(tests tests/tests.cpp tests/term_test.h)
target_compile_options(tests PRIVATE -Wall -Wextra -Werror -pedantic)

target_include_directories(tests PRIVATE tests)

target_link_libraries(tests PRIVATE lib_poly)
