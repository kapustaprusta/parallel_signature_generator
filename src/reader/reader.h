#pragma once

#include <atomic>
#include <vector>
#include <mutex>

#include "../defs/defs.h"

namespace reader
{

    class IReader
    {
        public:
            explicit IReader(const uint64_t chunk_size)
                : chunk_size_(chunk_size), processed_bytes_(0), processed_chunks_(0){}
            virtual ~IReader() = default;

            virtual uint64_t Read(defs::Chunk& chunk) = 0;
            virtual uint64_t GetProcessedBytes() const = 0;
            virtual bool IsEOF() = 0;

        protected:
            uint64_t chunk_size_;

            std::mutex read_mutex_;
            std::atomic_uint64_t processed_bytes_;
            std::atomic_uint64_t processed_chunks_;
    };

} // reader