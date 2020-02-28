#include <stdexcept>

#include "reader_task.h"

namespace task
{

    ReaderTask::ReaderTask(const std::shared_ptr<reader::IReader>& p_reader, const std::shared_ptr<data_structures::SharedQueue<data_structures::Buffer<uint8_t>>>& p_shared_queue)
        : buffers_counter_(0)
    {
        if (!p_reader || !p_shared_queue)
        {
            throw std::runtime_error("invalid arguments");
        }

        p_reader_ = p_reader;
        p_shared_queue_ = p_shared_queue;
    }

    void ReaderTask::Start()
    {
        std::vector<uint8_t> buffer;
        while (!p_reader_->IsEOF() && !is_stopped_.load())
        {
            p_reader_->Read(buffer);
            p_shared_queue_->Push({buffers_counter_ , buffer});
            buffers_counter_++;
        }
    }

    void ReaderTask::Stop()
    {
        is_stopped_.store(true);
        buffers_counter_.store(0);
    }

} // task