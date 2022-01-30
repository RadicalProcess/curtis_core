#pragma once

#include <gmock/gmock.h>
#include <curtis_core/IFactory.h>

namespace rp::curtis {

    class FactoryMock : public IFactory {
    public:
        MOCK_METHOD(SegmentBankPtr, createSegmentBank, (size_t numCaches, size_t size), (const, override));
        MOCK_METHOD(SegmentDetectorPtr, createSegmentDetector, (float sampleRate, size_t maxBufferSize), (const, override));
        MOCK_METHOD(GranulatorPtr, createGranulator, (const ISegmentBank& segmentBank, size_t maxBufferSize, size_t cacheSize), (const, override));
        MOCK_METHOD(BufferPtr, createBuffer, (size_t capacity, bool fill), (const, override));
        MOCK_METHOD(BufferPtr, createBuffer, (float* buffer, size_t size), (const, override));
        MOCK_METHOD(PolarityPtr, createPolarity, (), (const, override));
        MOCK_METHOD(RandomRangePtr, createRandomRange, (float a, float b), (const, override));
        MOCK_METHOD(GlissonPtr, createGlisson, (), (const, override));
        MOCK_METHOD(RandomizerPtr, createRandomizer, (), (const, override));
        MOCK_METHOD(CounterPtr, createCounter, (), (const, override));
        MOCK_METHOD(ReadBufferPtr, createReadBuffer, (size_t maxBufferSize), (const, override));
        MOCK_METHOD(DensityPtr, createDensity, (), (const, override));
        MOCK_METHOD(InputMixPtr, createInputMix, (), (const, override));
        MOCK_METHOD(PannerPtr, createPanner, (), (const, override));
    };

}  // namespace rp::curtis
