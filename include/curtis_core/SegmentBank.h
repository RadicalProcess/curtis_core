#pragma once

#include <vector>

#include "ISegmentBank.h"

namespace rp::curtis
{
    class SegmentBank : public ISegmentBank
    {
    public:
        SegmentBank(size_t numCaches);

        ~SegmentBank() override = default;

        std::vector<float> getCache(size_t fromNewest) override;

    private:
        std::vector<std::vector<float>> data_;
    };
}
