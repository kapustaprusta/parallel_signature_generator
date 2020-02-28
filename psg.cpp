#include <iostream>
#include <memory>

#include "src/reader/file_reader/file_reader.h"
#include "src/writer/file_writer/file_writer.h"
#include "src/hash_calculator/md5_hash_calculator/md5_hash_calculator.h"

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

    auto chunk = std::vector<uint8_t>();
    auto hash_calculator = std::make_shared<hash::MD5HashCalculator>();

    while (!reader->IsEOF())
    {
        reader->Read (chunk);
        auto res = hash_calculator->Calculate(chunk);
    }

    return 0;
}