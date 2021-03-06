#pragma once

#include <boost/uuid/detail/md5.hpp>

#include "../hash_calculator.h"

namespace hash
{

    class MD5HashCalculator final : public IHashCalculator
    {
        public:
            explicit MD5HashCalculator() = default;
            ~MD5HashCalculator() final = default;

            defs::Chunk Calculate(const defs::Chunk& chunk) override;

        private:
            boost::uuids::detail::md5::digest_type digest_;

            std::vector<uint8_t> ConvertDigestToStdVector(const boost::uuids::detail::md5::digest_type& digest);
    };

} // hash