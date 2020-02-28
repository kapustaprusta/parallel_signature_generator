#pragma once

#include <atomic>
#include <vector>

namespace reader
{

    class IReader
    {
        public:
            explicit IReader(uint64_t chunk_size)
                : chunk_size_(chunk_size), size_multiplier_(0x100000), processed_bytes_(0){}
            virtual ~IReader() = default;

            virtual uint64_t Read(std::vector<uint8_t>& buffer) = 0;
            virtual uint64_t GetProcessedBytes() const = 0;
            virtual bool IsEOF() const = 0;

        protected:
            uint64_t chunk_size_;
            const uint64_t size_multiplier_;
            std::atomic_uint64_t processed_bytes_;
    };

} // reader