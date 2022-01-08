#pragma once

#include <gmock/gmock.h>
#include <curtis_core/IFactory.h>

namespace rp::curtis {

    class BufferMock : public IBuffer {
    public:
        MOCK_METHOD(size_t, size, (), (const, override));
        MOCK_METHOD(const float*, get, (), (const, override));
        MOCK_METHOD(bool, owned, (), (const, override));
        MOCK_METHOD(void, clean, (), (override));
        MOCK_METHOD(void, append, (const IBuffer& buffer), (override));
        MOCK_METHOD(void, push, (float value), (override));
        MOCK_METHOD(float, getLast, (), (const, override));
    };

}  // namespace rp::curtis
