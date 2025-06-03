#ifndef INSTRUCTION_DECODER_HPP
#define INSTRUCTION_DECODER_HPP

#include <filesystem>


void decode_file(std::filesystem::path const &inputPath,
                 std::filesystem::path const &outputPath);

#endif

