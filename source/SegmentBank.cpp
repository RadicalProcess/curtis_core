#include "SegmentBank.h"

namespace rp::curtis
{
    SegmentBank::SegmentBank(size_t numCaches, size_t size, const IFactory& factory)
    : latestCache_(std::nullopt)
    {
        for(auto i = static_cast<size_t>(0); i < numCaches; ++i)
            cache_.emplace_back(factory.createBuffer(size));
    }

    const IBuffer* SegmentBank::getCache(size_t fromNewest) const
    {
        if(latestCache_ == std::nullopt)
            return nullptr;

        auto index = static_cast<int>(latestCache_.value())-static_cast<int>(fromNewest);
        if (index < 0)
            index += static_cast<int>(cache_.size());
        return cache_[index].get();
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
