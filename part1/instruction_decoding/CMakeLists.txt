cmake_minimum_required(VERSION 4.0)

add_executable(instruction_decoding)

target_sources(instruction_decoding PRIVATE
    main.cpp
    decoder.cpp
)

target_link_options(instruction_decoding PRIVATE
    -fsanitize=address
    -fsanitize=undefined
)

