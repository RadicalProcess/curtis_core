#pragma once

#include <gmock/gmock.h>
#include <curtis_core/IFactory.h>

namespace rp::curtis {

    class FactoryMock : public IFactory {
    public:
        MOCK_METHOD(SegmentBankPtr, createSegmentBank, (size_t numCaches, size_t size), (const, override));
        MOCK_METHOD(SegmentDetectorPtr, createSegmentDetector, (float sampleRate, size_t maxBufferSize), (const, override));
        MOCK_METHOD(GranulatorPtr, createGranulator, (const ISegmentBank& segmentBank, size_t maxBufferSize), (const, override));
        MOCK_METHOD(BufferPtr, createBuffer, (size_t capacity), (const, override));
        MOCK_METHOD(BufferPtr, createBuffer, (float* buffer, size_t size), (const, override));
        MOCK_METHOD(PolarityPtr, createPolarity, (), (const, override));
        MOCK_METHOD(RandomRangeFloatPtr, createRandomRangeFloat, (float min, float max), (const, override));
        MOCK_METHOD(RandomRangeSizeTPtr, createRandomRangeSizeT, (size_t min, size_t max), (const, override));
    };

}  // namespace rp::curtis
