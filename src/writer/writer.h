#pragma once

#include <atomic>
#include <vector>

namespace writer
{

    class IWRiter
    {
        public:
            explicit IWRiter()
                : processed_bytes_(0){};
            virtual ~IWRiter() = default;

            virtual uint64_t Write(std::vector<uint8_t>& buffer) = 0;
            virtual uint64_t GetProcessedBytes() const = 0;

        protected:
            std::atomic_uint64_t processed_bytes_;
    };

} // writer