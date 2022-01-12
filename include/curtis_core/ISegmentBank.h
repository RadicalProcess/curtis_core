#pragma once

#include <memory>

#include "IBuffer.h"

namespace rp::curtis
{
    class ISegmentBank
    {
    public:
        virtual ~ISegmentBank() = default;

        virtual size_t getLatestCacheIndex() const = 0;

        virtual const IBuffer& getCache(size_t index) const = 0;

        virtual size_t size() const = 0;
    };

    using SegmentBankPtr = std::unique_ptr<ISegmentBank>;
}
