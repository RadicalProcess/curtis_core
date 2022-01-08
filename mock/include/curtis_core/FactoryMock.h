#pragma once

#include <gmock/gmock.h>
#include <curtis_core/IFactory.h>

namespace rp::curtis {

    class FactoryMock : public IFactory {
    public:
        MOCK_METHOD(SegmentBankPtr, createSegmentBank, (size_t numCaches), (const, override));
        MOCK_METHOD(SegmentDetectorPtr, createSegmentDetector, (float sampleRate), (const, override));
        MOCK_METHOD(GranulatorPtr, createGranulator, (const ISegmentBank& segmentBank), (const, override));
        MOCK_METHOD(BufferPtr, createBuffer, (), (const, override));
        MOCK_METHOD(BufferPtr, createBuffer, (size_t capacity), (const, override));
        MOCK_METHOD(BufferPtr, createBuffer, (float* buffer, size_t size), (const, override));
        MOCK_METHOD(PolarityPtr, createPolarity, (), (const, override));
    };

}  // namespace rp::curtis
