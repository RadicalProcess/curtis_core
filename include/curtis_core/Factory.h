#pragma once

#include "IFactory.h"

namespace rp::curtis
{
    class Factory : public IFactory
    {
    public:
        SegmentBankPtr createSegmentBank(size_t numCaches) const override;

        SegmentDetectorPtr createSegmentDetector(float sampleRate) const override;

        GranulatorPtr createGranulator() const override;
    };
}
