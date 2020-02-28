#pragma once

#include <atomic>

namespace task
{

    class ITask
    {
        public:
            explicit ITask()
                : is_stopped_(false){};
            virtual ~ITask() = default;

            virtual void Start() = 0;
            virtual void Stop() = 0;

        protected:
            std::atomic_bool is_stopped_;
    };

} // task