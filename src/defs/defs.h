#pragma once

#include <string>
#include <vector>

namespace defs
{

    struct Config
    {
        Config() = default;

        std::string input_file_path;
        std::string output_file_path;
        int64_t block_size;
    };

    struct Chunk
    {
        Chunk() = default;

        uint64_t id;
        std::vector<uint8_t> payload;
    };

    enum class HashCalculatorType
    {
        UNKNOWN = 0,
        MD5,
        CRC32,
    };

} // defs