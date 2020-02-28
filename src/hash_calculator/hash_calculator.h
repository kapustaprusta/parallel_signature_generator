#pragma once

#include <vector>

namespace hash
{

    class IHashCalculator
    {
        public:
            explicit IHashCalculator() = default;
            virtual ~IHashCalculator() = default;

            virtual std::vector<uint8_t> Calculate(const std::vector<uint8_t>& chunk) = 0;
    };

}