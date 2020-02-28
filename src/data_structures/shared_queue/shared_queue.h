#pragma once

#include <queue>
#include <mutex>
#include <memory>

namespace data_structures
{

    template<typename T>
    class SharedQueue final
    {
        public:
            explicit SharedQueue() = default;
            ~SharedQueue() = default;

            void Push(const T& value)
            {
                std::lock_guard<std::mutex> lg(mutex_);
                values_.push(value);
            }

            T Front()
            {
                std::lock_guard<std::mutex> lg(mutex_);
                return values_.front();
            }

            T Back()
            {
                std::lock_guard<std::mutex> lg(mutex_);
                return values_.back();
            }

            void Pop()
            {
                std::lock_guard<std::mutex> lg(mutex_);
                values_.pop();
            }

            bool Empty()
            {
                std::lock_guard<std::mutex> lg(mutex_);
                return values_.empty();
            }

        private:
            std::mutex mutex_;
            std::queue<T> values_;
    };

} // data_structures