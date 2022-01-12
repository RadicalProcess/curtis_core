#include "SegmentBank.h"

namespace rp::curtis
{
    SegmentBank::SegmentBank(size_t numCaches, size_t size, const IFactory& factory)
    : latestCache_(0)
    {
        for(auto i = static_cast<size_t>(0); i < numCaches; ++i)
            cache_.emplace_back(factory.createBuffer(size, true));
    }

    size_t SegmentBank::getLatestCacheIndex() const
    {
        return latestCache_;
    }

    const IBuffer& SegmentBank::getCache(size_t index) const
    {
        return *cache_[index];
    }

    void SegmentBank::onSegmentDetected(const IBuffer& buffer)
    {
        latestCache_ = (latestCache_ + 1) % cache_.size();
        cache_[latestCache_]->copyFrom(buffer);
    }

    size_t SegmentBank::size() const
    {
        return cache_.size();
    }
}
