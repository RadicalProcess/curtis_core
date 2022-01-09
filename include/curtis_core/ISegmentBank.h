#pragma once

#include <memory>

#include "IBuffer.h"

namespace rp::curtis
{
    class ISegmentBank
    {
    public:
        virtual ~ISegmentBank() = default;

        virtual const IBuffer* getCache(size_t fromNewest) const = 0;
    };

    using SegmentBankPtr = std::unique_ptr<ISegmentBank>;
}
