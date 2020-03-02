#include <list>
#include <memory>
#include <iostream>

#include "src/task/task.h"
#include "src/reader/reader.h"
#include "src/writer/writer.h"
#include "src/cli_parser/cli_parser.h"
#include "src/threadpool/threadpool.h"
#include "src/task/hash_task/hash_task.h"
#include "src/reader/file_reader/file_reader.h"
#include "src/writer/file_writer/file_writer.h"

int main(int argc, char* argv[])
{
    //
    defs::Config config;

    try
    {
        const auto cli_parser = std::make_unique<cli::CliParser>(argc, argv);
        config = cli_parser->Exec();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        return 0;
    }

    //
    std::shared_ptr<reader::IReader> p_reader;
    std::shared_ptr<writer::IWRiter> p_writer;

    try
    {
        p_reader = std::make_shared<reader::FileReader>(config.input_file_path, config.block_size);
        p_writer = std::make_shared<writer::FileWriter>(config.output_file_path);
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
        return 0;
    }

    //
    std::list<std::shared_ptr<task::ITask>> tasks;
    auto p_thread_pool = std::make_unique<threadpool::ThreadPool>();

    for (uint32_t thread_number = 0; thread_number < p_thread_pool->GetWorkersNumber(); thread_number++)
    {
        tasks.emplace_back(std::make_shared<task::HashTask>(p_reader, p_writer));
    }

    for (const auto& task : tasks)
    {
        p_thread_pool->Schedule([task]() -> void
        {
            task->Start();
        });
    }

    return 0;
}