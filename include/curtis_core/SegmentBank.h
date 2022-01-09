#pragma once

#include <vector>

#include "ISegmentBank.h"
#include "ISegmentDetector.h"
#include "IBuffer.h"
#include "Factory.h"

namespace rp::curtis
{
    class SegmentBank : public ISegmentBank
                      , public ISegmentDetector::Listener
    {
    public:
        SegmentBank(size_t numCaches, size_t size, const IFactory& factory = Factory());

        ~SegmentBank() override = default;

        std::optional<size_t> getLatestCacheIndex() const override;

        const IBuffer& getCache(size_t index) const override;

        size_t size() const override;

    private:
        void onSegmentDetected(const IBuffer& buffer) override;

        std::vector<BufferPtr> cache_;
        std::optional<size_t> latestCache_;
    };
}
