#pragma once

#include <fstream>

#include "../reader.h"

namespace reader
{

    class FileReader final : public IReader
    {
        public:
            explicit FileReader(const std::string& file_path, uint64_t chunk_size);
            ~FileReader() final;

            uint64_t Read(std::vector<uint8_t>& chunk) override;
            uint64_t GetProcessedBytes() const override;
            bool IsEOF() const override;

        private:
            uint64_t file_size_;

            std::ifstream file_stream_;

            uint64_t GetFileSize(const std::ifstream& file_stream_);
    };

}