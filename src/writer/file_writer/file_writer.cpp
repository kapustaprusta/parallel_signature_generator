#include <stdexcept>

#include "file_writer.h"

namespace writer
{

    FileWriter::FileWriter(const std::string& file_path)
    {
        file_stream_ = std::ofstream(file_path, std::ofstream::out | std::ofstream::binary);
        if (!file_stream_.is_open())
        {
            throw std::runtime_error("FileWriter::FileWriter(...) : invalid file path");
        }
    }

    FileWriter::~FileWriter()
    {
        file_stream_.close();
    }

    uint64_t FileWriter::Write(defs::Chunk& chunk)
    {
        std::lock_guard<std::mutex> lg(write_mutex_);

        file_stream_.seekp(chunk.payload.size()*chunk.id, std::ios::beg);
        file_stream_.write(reinterpret_cast<char*>(chunk.payload.data()), chunk.payload.size());
        processed_bytes_ += chunk.payload.size();

        return chunk.payload.size();
    }

    uint64_t FileWriter::GetProcessedBytes() const
    {
        return processed_bytes_.load();
    }

} // writer