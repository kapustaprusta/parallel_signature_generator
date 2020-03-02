#pragma once

#include <vector>

#include "../defs/defs.h"

namespace hash
{

    class IHashCalculator
    {
        public:
            explicit IHashCalculator() = default;
            virtual ~IHashCalculator() = default;

            virtual defs::Chunk Calculate(const defs::Chunk& chunk) = 0;
    };

} // hash