#pragma once

#include <curtis_core/IReadBuffer.h>

namespace rp::curtis {

    class ReadBufferMock : public IReadBuffer {
    public:
        MOCK_METHOD(void, updateBuffer, (const IBuffer& buffer), (override));
        MOCK_METHOD(bool, advancePlayHead, (float advancement), (override));
        MOCK_METHOD(float, getSample, (), (const, override));
        MOCK_METHOD(float, getPhase, (), (const, override));
    };

}  // namespace rp::curtis
