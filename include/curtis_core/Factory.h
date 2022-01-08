#pragma once

#include "IFactory.h"

namespace rp::curtis
{
    class Factory : public IFactory
    {
    public:
        SegmentBankPtr createSegmentBank(size_t numCaches) override;

        SegmentDetectorPtr createSegmentDetector(float sampleRate) override;

        GranulatorPtr createGranulator() override;


    };
}
