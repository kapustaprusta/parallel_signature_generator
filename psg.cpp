#include <iostream>
#include <memory>
#include <future>
#include <thread>

#include "src/reader/file_reader/file_reader.h"
#include "src/writer/file_writer/file_writer.h"
#include "src/task/reader_task/reader_task.h"

int main(int argc, char* argv[])
{
    std::shared_ptr<reader::IReader> reader;
    std::shared_ptr<writer::IWRiter> writer;

    try
    {
        reader = std::make_shared<reader::FileReader>("D://files//test_signals//ethernet.sig", 1);
        writer = std::make_shared<writer::FileWriter>("C://Users//vladislav//Desktop//test_out.bin");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return 0;
    }

    auto shared_queue = std::make_shared<data_structures::SharedQueue<data_structures::Buffer<uint8_t>>>();
    auto reader_task = std::make_shared<task::ReaderTask>(reader, shared_queue);

    reader_task->Start();

    while (!shared_queue->Empty())
    {
        const auto buffer = shared_queue->Front();
        shared_queue->Pop();
        std::cout << buffer.GetId() << '\n';
    }

    return 0;
}