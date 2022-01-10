#include "Factory.h"
#include "SegmentBank.h"
#include "SegmentDetector.h"
#include "Granulator.h"
#include "Buffer.h"
#include "Polarity.h"
#include "RandomRange.h"
#include "Glisson.h"
#include "Randomizer.h"
#include "Counter.h"

namespace rp::curtis
{
    SegmentBankPtr Factory::createSegmentBank(size_t numCaches, size_t size) const
    {
        return std::make_unique<SegmentBank>(numCaches, size);
    }

    SegmentDetectorPtr Factory::createSegmentDetector(float sampleRate, size_t maxBufferSize) const
    {
        return std::make_unique<SegmentDetector>(sampleRate, maxBufferSize);
    }

    GranulatorPtr Factory::createGranulator(const ISegmentBank& segmentBank, size_t maxBufferSize) const
    {
        return std::make_unique<Granulator>(segmentBank, maxBufferSize);
    }

    BufferPtr Factory::createBuffer(float* buffer, size_t size) const
    {
        return std::make_unique<Buffer>(buffer, size);
    }

    BufferPtr Factory::createBuffer(size_t capacity) const
    {
        return std::make_unique<Buffer>(capacity);
    }

    PolarityPtr Factory::createPolarity() const
    {
        return std::make_unique<Polarity>();
    }

    RandomRangeFloatPtr Factory::createRandomRangeFloat(float min, float max) const
    {
        return std::make_unique<RandomRangeFloat>(min, max);
    }

    RandomRangeSizeTPtr Factory::createRandomRangeSizeT(size_t min, size_t max) const
    {
        return std::make_unique<RandomRangeSizeT>(min, max);
    }

    GlissonPtr Factory::createGlisson() const
    {
        return std::make_unique<Glisson>();
    }

    RandomizerPtr Factory::createRandomizer() const
    {
        return std::make_unique<Randomizer>();
    }

    CounterPtr Factory::createCounter() const
    {
        return std::make_unique<Counter>();
    }
}
