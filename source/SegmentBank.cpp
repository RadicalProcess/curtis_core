#include "SegmentBank.h"

namespace rp::curtis
{
    SegmentBank::SegmentBank(size_t numCaches, const IFactory& factory)
    : latestCache_(std::nullopt)
    {
        for(auto i = static_cast<size_t>(0); i < numCaches; ++i)
            cache_.emplace_back(factory.createBuffer());
    }

    const IBuffer* SegmentBank::getCache(size_t fromNewest)
    {
        if(latestCache_ == std::nullopt)
            return nullptr;

        return cache_[latestCache_.value()].get();
    }

    void SegmentBank::onSegmentDetected(const IBuffer& buffer)
    {
        if(!latestCache_.has_value())
            latestCache_ = 0;
        else
            latestCache_.value() = (latestCache_.value() + 1) % cache_.size();

        cache_[latestCache_.value()]->copyFrom(buffer);
    }
}
