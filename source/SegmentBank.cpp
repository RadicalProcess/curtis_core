#include "SegmentBank.h"

namespace rp::curtis
{
    SegmentBank::SegmentBank(size_t numCaches)
    : latestCache_(std::nullopt)
    {
        cache_.resize(numCaches);
    }

    const IBuffer* SegmentBank::getCache(size_t fromNewest)
    {
        if(latestCache_ == std::nullopt)
            return nullptr;

        return &cache_[latestCache_.value()];
    }

    void SegmentBank::onSegmentDetected(const IBuffer& buffer)
    {
        if(!latestCache_.has_value())
            latestCache_ = 0;
        else
            latestCache_.value() = (latestCache_.value() + 1) % cache_.size();

        cache_[latestCache_.value()].copyFrom(buffer);
    }
}
