#include "SegmentBank.h"

namespace rp::curtis
{
    SegmentBank::SegmentBank(size_t numCaches)
    {
        data_.resize(numCaches);
    }

    std::vector<float> SegmentBank::getCache(size_t fromNewest)
    {
        return std::vector<float>();
    }
}
