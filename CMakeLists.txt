cmake_minimum_required(VERSION 3.17.5)
project(cont)

set(CMAKE_CXX_STANDARD 98)

add_library(testlib INTERFACE)

add_subdirectory(unit_tests)

add_executable(jalvaro_one_love
        unit_tests/main.cpp
        unit_tests/list.cpp)