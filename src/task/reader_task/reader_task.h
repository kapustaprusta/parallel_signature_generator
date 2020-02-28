#pragma once

#include <memory>

#include "../task.h"
#include "../../reader/reader.h"
#include "../../data_structures/buffer/buffer.h"
#include "../../data_structures/shared_queue/shared_queue.h"

namespace task
{

    class ReaderTask final : public ITask
    {
        public:
            explicit ReaderTask(const std::shared_ptr<reader::IReader>& p_reader, const std::shared_ptr<data_structures::SharedQueue<data_structures::Buffer<uint8_t>>>& p_shared_queue);
            ~ReaderTask() final = default;

            void Start() override;
            void Stop() override;

        private:
            std::atomic_uint64_t buffers_counter_;

            std::shared_ptr<reader::IReader> p_reader_;
            std::shared_ptr<data_structures::SharedQueue<data_structures::Buffer<uint8_t>>> p_shared_queue_;
    };

} // task