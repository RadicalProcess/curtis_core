#pragma once

#include <memory>

namespace rp::curtis
{
    class ISegmentBank
    {
    public:
        virtual ~ISegmentBank() = default;

        virtual std::vector<float> getCache(size_t fromNewest) = 0;
    };

    using SegmentBankPtr = std::unique_ptr<ISegmentBank>;
}
