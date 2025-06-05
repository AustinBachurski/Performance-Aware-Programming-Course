cmake_minimum_required(VERSION 4.0)

add_executable(decoding_multiple)

target_sources(decoding_multiple PRIVATE
    main.cpp
    decoder.cpp
)

target_link_options(decoding_multiple PRIVATE
    -fsanitize=address
    -fsanitize=undefined
)

