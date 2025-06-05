#include "decoder.hpp"

#include <cstdio>
#include <filesystem>


int main()
{
    std::filesystem::path const single_mov_file{
        "../../../../"
        "computer_enhance/perfaware/part1/listing_0037_single_register_mov"
    };
    std::filesystem::path const many_mov_file{
        "../../../../"
        "computer_enhance/perfaware/part1/listing_0038_many_register_mov"
    };

    if (!std::filesystem::exists(single_mov_file))
    {
        std::puts("Single mov file does not exist.");
        return 1;
    }

    if (!std::filesystem::exists(many_mov_file))
    {
        std::puts("Many mov file does not exist.");
        return 1;
    }

    std::filesystem::path const single_mov_out{ "listing_0037.asm" };
    std::filesystem::path const many_mov_out{ "listing_0038.asm" };

    decode_file(single_mov_file, single_mov_out);
    decode_file(many_mov_file, many_mov_out);
}

