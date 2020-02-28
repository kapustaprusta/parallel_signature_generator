#pragma once

#include <vector>

namespace writer
{

    class IWRiter
    {
        public:
            explicit IWRiter() = default;
            virtual ~IWRiter() = default;

            virtual uint64_t Write(std::vector<uint8_t>& buffer) = 0;
            virtual uint64_t GetProcessedBytes() const = 0;
    };

} // writer