#include <stdexcept>

#include "writer_task.h"

namespace task
{

    WriterTask::WriterTask(const std::shared_ptr<writer::IWRiter>& p_writer, const std::shared_ptr<data_structures::SharedQueue<data_structures::Buffer<uint8_t>>>& p_shared_queue)
    {
        if (!p_writer || !p_shared_queue)
        {
            throw std::runtime_error("invalid arguments");
        }

        p_writer_ = p_writer;
        p_shared_queue_ = p_shared_queue;
    }

    void WriterTask::Start()
    {
        while (!is_stopped_.load())
        {
            
        }
    }

    void WriterTask::Stop()
    {
        is_stopped_.store(true);
    }

} // task