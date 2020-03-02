#include <sstream>

#include "cli_parser.h"

namespace cli
{

    CliParser::CliParser(int argc, char* argv[])
    {
        description_.add_options()
            ("help", "show help")
            ("input-file-path,i" , boost::program_options::value<std::string>(&config_.input_file_path )->composing(), "set input file path"     )
            ("output-file-path,o", boost::program_options::value<std::string>(&config_.output_file_path)->composing(), "set output file path"    )
            ("block-size,b"      , boost::program_options::value<int64_t>    (&config_.block_size      )->composing(), "set block size in MBytes")
        ;

        try
        {
            boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description_), variables_);
            boost::program_options::notify(variables_);
        }
        catch (std::exception& e)
        {
            throw e;
        }
    }

    defs::Config CliParser::Exec()
    {
        if (variables_.count("help"))
        {
            std::stringstream description_stream;
            std::string description_string;
            description_.print(description_stream);

            while (!description_stream.eof())
            {
                std::string tmp_string;
                std::getline(description_stream, tmp_string);
                description_string.append(tmp_string + '\n');
            }

            throw std::runtime_error(description_string);
        }

        if (!variables_.count("input-file-path") || !variables_.count("output-file-path"))
        {
            throw std::runtime_error("please, use --help option for information");
        }

        if (variables_.count("block-size") && variables_["block-size"].as<int64_t>() <= 0)
        {
            throw std::runtime_error("invalid block size");
        }

        variables_.count("block-size") ? config_.block_size *= bytes_number_in_mbyte_ : config_.block_size = bytes_number_in_mbyte_;

        return config_;
    }
}