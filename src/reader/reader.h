#pragma once

#include <vector>

namespace reader
{

    class IReader
    {
        public:
            explicit IReader() = default;
            virtual ~IReader() = default;

            virtual uint64_t Read(std::vector<uint8_t>& buffer) = 0;
            virtual uint64_t GetProcessedBytes() const = 0;
            virtual bool IsEOF() const = 0;
    };

} // reader