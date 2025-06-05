cmake_minimum_required(VERSION 4.0)

project(Decoding LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

add_compile_options(
    -Werror
    -Wall
    -Wcast-align
    -Wdouble-promotion
    -Wduplicated-branches
    -Wduplicated-cond
    -Wextra
    -Wconversion
    -Wimplicit-fallthrough
    -Wlogical-op
    -Wmisleading-indentation
    -Wnull-dereference
    -Wpedantic
    -Wshadow
    -Wsign-conversion
    -Wunused
    -fsanitize=address
    -fsanitize=undefined
    -g3
)

add_subdirectory(
    part1/instruction_decoding
)

add_subdirectory(
    part1/decoding_multiple
)

