#pragma once

#include <gmock/gmock.h>

#include <curtis_core/ISegmentDetector.h>

namespace rp::curtis
{
    class SegmentDetectorMock : public ISegmentDetector {
    public:
        MOCK_METHOD(void, setSegmentMinLength, (float ms), (override));
        MOCK_METHOD(void, setSegmentMaxLength, (float ms), (override));
        MOCK_METHOD(void, process, (IBuffer& buffer), (override));
        MOCK_METHOD(void, addListener, (Listener* listener), (override));
        MOCK_METHOD(void, removeListener, (Listener* listener), (override));
    };
}
