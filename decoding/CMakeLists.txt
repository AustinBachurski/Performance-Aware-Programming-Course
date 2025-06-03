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
    -g3
)

add_executable(decode)

target_sources(decode PRIVATE
    main.cpp
    decoder.cpp
)

target_link_options(decode PRIVATE -fsanitize=address)

