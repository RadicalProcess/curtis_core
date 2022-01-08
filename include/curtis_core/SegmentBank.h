#pragma once

#include <vector>
#include <optional>

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
        SegmentBank(size_t numCaches, const IFactory& factory = Factory());

        ~SegmentBank() override = default;

        const IBuffer* getCache(size_t fromLatest) override;

    private:
        void onSegmentDetected(const IBuffer& buffer) override;

        std::vector<BufferPtr> cache_;
        std::optional<size_t> latestCache_;
    };
}
