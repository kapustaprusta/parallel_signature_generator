#pragma once

#include <fstream>

#include "../writer.h"

namespace writer
{

    class FileWriter final : public IWRiter
    {
        public:
            explicit FileWriter(const std::string& file_path);
            ~FileWriter() final;

            uint64_t Write(defs::Chunk& chunk) override;
            uint64_t GetProcessedBytes() const;

        private:
            std::ofstream file_stream_;
    };

} // writer