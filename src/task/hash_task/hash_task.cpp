#include <stdexcept>

#include <string> 

#include "hash_task.h"
#include "../../hash_calculator/md5_hash_calculator/md5_hash_calculator.h"

namespace task
{

    HashTask::HashTask(const std::shared_ptr<reader::IReader>& p_reader, const std::shared_ptr<writer::IWRiter>& p_writer)
    {
        if (!p_reader)
        {
            throw std::runtime_error("HashTask::HashTask(...) : invalid pointer o reader");
        }

        if (!p_writer)
        {
            throw std::runtime_error("HashTask::HashTask(...) : invalid pointer to writer");
        }

        p_reader_ = p_reader;
        p_writer_ = p_writer;
        p_hash_calculator_ = std::make_unique<hash::MD5HashCalculator>();
    }

    void HashTask::Start()
    {
        while (!p_reader_->IsEOF() && !is_stopped_.load())
        {
            defs::Chunk chunk;
            p_reader_->Read(chunk);
            p_writer_->Write(p_hash_calculator_->Calculate(chunk));
        }
    }

    void HashTask::Stop()
    {
        is_stopped_.store(true);
    }

} // task

