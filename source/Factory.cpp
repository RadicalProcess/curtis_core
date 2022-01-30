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
#include "ReadBuffer.h"
#include "Density.h"
#include "InputMix.h"
#include "Panner.h"

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

    GranulatorPtr Factory::createGranulator(const ISegmentBank& segmentBank, size_t maxBufferSize, size_t cacheSize) const
    {
        return std::make_unique<Granulator>(segmentBank, maxBufferSize, cacheSize);
    }

    BufferPtr Factory::createBuffer(float* buffer, size_t size) const
    {
        return std::make_unique<Buffer>(buffer, size);
    }

    BufferPtr Factory::createBuffer(size_t capacity, bool fill) const
    {
        return std::make_unique<Buffer>(capacity, fill);
    }

    PolarityPtr Factory::createPolarity() const
    {
        return std::make_unique<Polarity>();
    }

    RandomRangePtr Factory::createRandomRange(float a, float b) const
    {
        return std::make_unique<RandomRange>(a, b);
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

    ReadBufferPtr Factory::createReadBuffer(size_t maxBufferSize) const
    {
        return std::make_unique<ReadBuffer>(maxBufferSize);
    }

    DensityPtr Factory::createDensity() const
    {
        return std::make_unique<Density>();
    }

    InputMixPtr Factory::createInputMix() const
    {
        return std::make_unique<InputMix>();
    }

    PannerPtr Factory::createPanner() const
    {
        return std::make_unique<Panner>();
    }
}
