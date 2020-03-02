#include <boost/algorithm/hex.hpp>

#include <iostream>

#include "md5_hash_calculator.h"

namespace hash
{

    defs::Chunk MD5HashCalculator::Calculate(const defs::Chunk& chunk)
    {
        boost::uuids::detail::md5 hash;

        hash.process_bytes(chunk.payload.data(), chunk.payload.size());
        hash.get_digest(digest_);

        return {chunk.id, ConvertDigestToStdVector(digest_)};
    }

    std::vector<uint8_t> MD5HashCalculator::ConvertDigestToStdVector(const boost::uuids::detail::md5::digest_type& digest)
    {
        const auto char_digest = reinterpret_cast<const uint8_t*>(&digest);
        std::vector<uint8_t> result;
        boost::algorithm::hex(char_digest, char_digest + sizeof(boost::uuids::detail::md5::digest_type), std::back_inserter(result));

        return result;
    }

} // hash