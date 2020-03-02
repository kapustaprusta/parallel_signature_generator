#include <stdexcept>

#include "file_reader.h"

namespace reader {

    FileReader::FileReader(const std::string& file_path, const uint64_t chunk_size)
        : IReader(chunk_size)
    {
        file_stream_ = std::ifstream(file_path, std::ifstream::in | std::ifstream::binary);
        if (!file_stream_.is_open())
        {
            throw std::runtime_error("FileReader::FileReader(...) : invalid file path");
        }

        if (chunk_size == 0)
        {
            throw std::runtime_error("FileReader::FileReader(...) : invalid chunk size");
        }


        file_size_ = GetFileSize(file_stream_);
    }

    FileReader::~FileReader()
    {
        file_stream_.close();
    }

    uint64_t FileReader::Read(defs::Chunk& chunk)
    {
        std::lock_guard<std::mutex> lg(read_mutex_);

        uint64_t valid_chunk_size = 0;
        if (processed_bytes_ + chunk_size_ > file_size_)
        {
            valid_chunk_size = file_size_ - processed_bytes_;
        }
        else
        {
            valid_chunk_size = chunk_size_;
        }

        chunk.id = processed_chunks_.load();
        chunk.payload.resize(chunk_size_);

        file_stream_.read(reinterpret_cast<char*>(chunk.payload.data()), chunk_size_);

        processed_bytes_ += chunk.payload.size();
        processed_chunks_++;

        return chunk.payload.size();
    }

    bool FileReader::IsEOF()
    {
        std::lock_guard<std::mutex> lg(read_mutex_);

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