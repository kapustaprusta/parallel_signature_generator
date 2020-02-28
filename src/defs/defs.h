#pragma once

#include <string>

namespace defs
{

    struct HashSum
    {
        HashSum() = default;

        uint32_t id;
        std::string payload;
    };

}