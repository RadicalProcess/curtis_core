#pragma once

#include "IFactory.h"

namespace rp::curtis
{
    class Factory : public IFactory
    {
    public:
        ~Factory() override = default;

        SegmentBankPtr createSegmentBank(size_t numCaches) const override;

        SegmentDetectorPtr createSegmentDetector(float sampleRate) const override;

        GranulatorPtr createGranulator() const override;

        BufferPtr createBuffer(size_t capacity) const override;

        BufferPtr createBuffer(float* buffer, size_t size) const override;
    };
}
