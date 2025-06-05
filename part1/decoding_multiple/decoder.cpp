#include "decoder.hpp"

#include <array>
#include <bitset>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>


static constexpr int bytesPerInstruction{ 2 };
static constexpr int bitsPerInstruction{ bytesPerInstruction * 8 };
static constexpr std::bitset<bitsPerInstruction> movOpcode = 0b10001000'00000000;
static constexpr std::bitset<bitsPerInstruction> regBits = 0b00000000'00111000;
static constexpr std::bitset<bitsPerInstruction> rmBits = 0b00000000'00000111;
static constexpr int dBit{ 9 };
static constexpr int wBit{ 8 };

static constexpr std::array registerFieldEncodingW0 = {
    "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh"
};

static constexpr std::array registerFieldEncodingW1 = {
    "ax", "cx", "dx", "bx", "sp", "bp", "si", "di"
};

static std::string decode_instruction(std::bitset<bitsPerInstruction> const &instruction);

void decode_file(std::filesystem::path const &inputPath, std::filesystem::path const &outputPath)
{
    std::ifstream file{ inputPath, std::ios::binary };

    if (!file.is_open())
    {
        std::puts("Failed to open input file.");
        return;
    }

    std::array<char, bytesPerInstruction> data;
    std::bitset<bitsPerInstruction> instruction;
    std::string result = "bits 16\n\n";

    while (file.good())
    {
        file.read(data.data(), bytesPerInstruction);

        if (!(file.gcount() == bytesPerInstruction))
        {
            break;
        }

        instruction = static_cast<unsigned int>(
            ((static_cast<unsigned char>(data[0]) << 8)
            | static_cast<unsigned char>(data[1]))
        );

        result += decode_instruction(instruction);
    }

    std::ofstream output{ outputPath, std::ios::trunc };
    output << result;
}

static std::string decode_opcode(std::bitset<bitsPerInstruction> const &instruction)
{
    std::string opcode;

    if ((instruction & movOpcode) == movOpcode)
    {
        opcode = "mov ";
    }
    else
    {
        opcode = "unknown";
    }

    return opcode;
}

static std::string decode_reg(std::bitset<bitsPerInstruction> const &instruction)
{
    std::string reg;

    auto const index = ((instruction & regBits) >> 3).to_ulong();

    if (instruction.test(wBit))
    {
        reg = registerFieldEncodingW1.at(index);
    }
    else
    {
        reg = registerFieldEncodingW0.at(index);
    }

    return reg;
}

static std::string decode_rm(std::bitset<bitsPerInstruction> const &instruction)
{
    std::string rm;

    auto const index = ((instruction & rmBits)).to_ulong();

    if (instruction.test(wBit))
    {
        rm = registerFieldEncodingW1.at(index);
    }
    else
    {
        rm = registerFieldEncodingW0.at(index);
    }

    return rm;
}

static std::string decode_targets(std::bitset<bitsPerInstruction> const &instruction)
{
    std::string targets;

    std::string reg = decode_reg(instruction);
    std::string rm = decode_rm(instruction);

    if (instruction.test(dBit))
    {
        targets = reg + ", " + rm;
    }
    else
    {
        targets = rm + ", " + reg;
    }

    return targets;
}

static std::string decode_instruction(std::bitset<bitsPerInstruction> const &instruction)
{
    std::string opcode = decode_opcode(instruction);
    std::string targets = decode_targets(instruction);

    return opcode + targets + '\n';
}
