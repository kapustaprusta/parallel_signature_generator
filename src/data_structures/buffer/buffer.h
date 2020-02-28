#pragma once

#include <atomic>
#include <vector>

namespace data_structures
{

    template <typename T>
    class Buffer final
    {
        public:
            Buffer(uint64_t id, const std::vector< T>& payload)
                : id_(id), payload_(payload){}
            ~Buffer() = default;

            Buffer(const Buffer& buffer)
            {
                id_.store(buffer.id_.load());
                payload_ = buffer.payload_;
            }

            uint64_t GetId() const
            {
                return id_;
            }

        private:
            std::atomic_uint64_t id_;
            std::vector<T> payload_;
    };

} // data_structures