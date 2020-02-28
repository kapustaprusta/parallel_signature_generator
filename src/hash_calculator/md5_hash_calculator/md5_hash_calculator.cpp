#include <boost/algorithm/hex.hpp>

#include "md5_hash_calculator.h"

namespace hash
{

    std::vector<uint8_t> MD5HashCalculator::Calculate(const std::vector<uint8_t>& chunk)
    {
        hash_.process_bytes(chunk.data(), chunk.size());
        hash_.get_digest(digest_);

        return ConvertDigestToStdVector(digest_);
    }

    std::vector<uint8_t> MD5HashCalculator::ConvertDigestToStdVector(const boost::uuids::detail::md5::digest_type& digest)
    {
        const auto char_digest = reinterpret_cast<const uint8_t*>(&digest);
        std::vector<uint8_t> result;
        boost::algorithm::hex(char_digest, char_digest + sizeof(boost::uuids::detail::md5::digest_type), std::back_inserter(result));

        return result;
    }

} // hash