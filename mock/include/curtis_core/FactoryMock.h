#pragma once

#include <gmock/gmock.h>
#include <curtis_core/IFactory.h>

namespace rp::curtis {

    class FactoryMock : public IFactory {
    public:
        MOCK_METHOD(SegmentBankPtr, createSegmentBank, (size_t numCaches), (const, override));
        MOCK_METHOD(SegmentDetectorPtr, createSegmentDetector, (float sampleRate), (const, override));
        MOCK_METHOD(GranulatorPtr, createGranulator, (), (const, override));
    };

}  // namespace rp::curtis
