#pragma once

#include "IFactory.h"

namespace rp::curtis
{
    class Factory : public IFactory
    {
    public:
        ~Factory() override = default;

        SegmentBankPtr createSegmentBank(size_t numCaches, size_t size) const override;

        SegmentDetectorPtr createSegmentDetector(float sampleRate, size_t maxBufferSize) const override;

        GranulatorPtr createGranulator(const ISegmentBank& segmentBank, size_t maxBufferSize, size_t cacheSize) const override;

        BufferPtr createBuffer(size_t capacity, bool fill = false) const override;

        BufferPtr createBuffer(float* buffer, size_t size) const override;

        PolarityPtr createPolarity() const override;

        RandomRangePtr createRandomRange(float a, float b) const override;

        GlissonPtr createGlisson() const override;

        RandomizerPtr createRandomizer() const override;

        CounterPtr createCounter() const override;

        ReadBufferPtr createReadBuffer(size_t maxBufferSize) const override;

        DensityPtr createDensity() const override;

        InputMixPtr createInputMix() const override;

        PannerPtr createPanner() const override;
    };
}
