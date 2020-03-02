#pragma once

#include <atomic>
#include <vector>
#include <mutex>

#include "../defs/defs.h"

namespace writer
{

    class IWRiter
    {
        public:
            explicit IWRiter()
                : processed_bytes_(0){};
            virtual ~IWRiter() = default;

            virtual uint64_t Write(defs::Chunk& chunk) = 0;
            virtual uint64_t GetProcessedBytes() const = 0;

        protected:
            std::mutex write_mutex_;
            std::atomic_uint64_t processed_bytes_;
    };

} // writer