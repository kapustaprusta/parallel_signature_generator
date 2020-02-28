#include <stdexcept>

#include "file_writer.h"

namespace writer
{

    FileWriter::FileWriter(const std::string& file_path)
    {
        file_stream_ = std::ofstream(file_path, std::ofstream::out | std::ofstream::binary);
        if (!file_stream_.is_open())
        {
            throw std::runtime_error("invalid file path");
        }
    }

    FileWriter::~FileWriter()
    {
        file_stream_.close();
    }

    uint64_t FileWriter::Write(std::vector<uint8_t>& buffer)
    {
        file_stream_.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
        processed_bytes_ += buffer.size();

        return buffer.size();
    }

    uint64_t FileWriter::GetProcessedBytes() const
    {
        return processed_bytes_.load();
    }

} // writer