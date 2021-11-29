cmake_minimum_required(VERSION 3.20)
project(senku)

set(CMAKE_CXX_STANDARD 11)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(senku main.cpp senku.h)
