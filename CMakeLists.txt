cmake_minimum_required(VERSION 3.17.5)
project(cont)

set(CMAKE_CXX_STANDARD 98)

add_library(testlib INTERFACE)

add_subdirectory(tests)