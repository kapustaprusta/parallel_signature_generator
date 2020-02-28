#pragma once

#include <atomic>
#include <fstream>

#include "../writer.h"

namespace writer
{

    class FileWriter final : public IWRiter
    {
        public:
            explicit FileWriter(const std::string& file_path);
            ~FileWriter() final;

            uint64_t Write(std::vector<uint8_t>& buffer) override;
            uint64_t GetProcessedBytes() const;

        private:
            std::atomic_uint64_t processed_bytes_;

            std::ofstream file_stream_;
    };

} // writer