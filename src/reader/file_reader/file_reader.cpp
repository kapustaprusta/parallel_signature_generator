#include <stdexcept>
#include <iostream>

#include "file_reader.h"

namespace reader {

    FileReader::FileReader(const std::string& file_path, const uint64_t chunk_size)
        : chunk_size_(chunk_size), processed_bytes_(0), size_multiplier_(0x100000) // number of bytes in one megabyte
    {
        file_stream_ = std::ifstream(file_path, std::ifstream::in | std::ifstream::binary);
        if (!file_stream_.is_open())
        {
            throw std::runtime_error("invalid file path");
        }

        file_size_ = GetFileSize(file_stream_);
    }

    FileReader::~FileReader()
    {
        if (file_stream_.is_open())
        {
            file_stream_.close();
        }
    }

    uint64_t FileReader::Read(std::vector<uint8_t>& chunk)
    {
        auto valid_chunk_size = 0;
        if (processed_bytes_ + chunk_size_*size_multiplier_ > file_size_)
        {
            valid_chunk_size = file_size_ - processed_bytes_;
        }
        else
        {
            valid_chunk_size = chunk_size_*size_multiplier_;
        }

        chunk.resize(valid_chunk_size);
        file_stream_.read(reinterpret_cast<char*>(chunk.data()), chunk_size_*size_multiplier_);
        processed_bytes_ += chunk.size();

        return chunk.size();
    }

    bool FileReader::IsEOF() const
    {
        return file_stream_.eof();
    }

    uint64_t FileReader::GetProcessedBytes() const
    {
        return processed_bytes_.load();
    }

    uint64_t FileReader::GetFileSize(const std::ifstream& file_stream)
    {
        file_stream_.seekg(0, file_stream_.end);
        const uint64_t file_size = file_stream_.tellg();
        file_stream_.seekg(0, file_stream_.beg);

        return file_size;
    }
}