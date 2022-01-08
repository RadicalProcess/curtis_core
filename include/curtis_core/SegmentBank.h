#pragma once

#include <vector>

#include "ISegmentBank.h"

namespace rp::curtis
{
    class SegmentBank : public ISegmentBank
    {
    public:
        SegmentBank(size_t numCaches, size_t maxSegmentSize);

    private:
        std::vector<std::vector<float>> data_;
    };
}
