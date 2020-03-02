#pragma once

#include <string>
#include <boost/program_options.hpp> 

#include "../defs/defs.h"

namespace cli
{

    class CliParser
    {
        public:
            explicit CliParser(int argc, char* argv[]);
            ~CliParser() = default;

            defs::Config Exec();

        private:
            const uint32_t bytes_number_in_mbyte_{1024*1024};
            defs::Config config_;

            boost::program_options::variables_map variables_;
            boost::program_options::options_description description_;
    };

}