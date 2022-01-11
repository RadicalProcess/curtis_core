#pragma once

#include <memory>

#include "ISegmentBank.h"
#include "ISegmentDetector.h"
#include "IGranulator.h"
#include "IPolarity.h"
#include "IRandomRange.h"
#include "IGlisson.h"
#include "IRandomizer.h"
#include "ICounter.h"
#include "IReadBuffer.h"

namespace rp::curtis
{
    class IFactory
    {
    public:
        virtual ~IFactory() = default;

        virtual SegmentBankPtr createSegmentBank(size_t numCaches, size_t size) const = 0;

        virtual SegmentDetectorPtr createSegmentDetector(float sampleRate, size_t maxBufferSize) const = 0;

        virtual GranulatorPtr createGranulator(const ISegmentBank& segmentBank, size_t maxBufferSize) const = 0;

        virtual BufferPtr createBuffer(size_t capacity, bool fill) const = 0;

        virtual BufferPtr createBuffer(float* buffer, size_t size) const = 0;

        virtual PolarityPtr createPolarity() const = 0;

        virtual RandomRangeFloatPtr createRandomRangeFloat(float min, float max) const = 0;

        virtual RandomRangeSizeTPtr createRandomRangeSizeT(size_t min, size_t max) const = 0;

        virtual GlissonPtr createGlisson() const = 0;

        virtual RandomizerPtr createRandomizer() const = 0;

        virtual CounterPtr createCounter() const = 0;

        virtual ReadBufferPtr createReadBuffer(size_t maxBufferSize) const = 0;
    };

    using FactoryPtr = std::unique_ptr<IFactory>;
}
