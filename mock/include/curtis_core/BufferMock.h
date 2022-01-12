#pragma once

#include <gmock/gmock.h>
#include <curtis_core/IFactory.h>

namespace rp::curtis {

    class BufferMock : public IBuffer {
    public:
        MOCK_METHOD(size_t, size, (), (const, override));
        MOCK_METHOD(void, copyFrom, (const IBuffer& buffer), (override));
        MOCK_METHOD(const float*, getReadPtr, (), (const, override));
        MOCK_METHOD(float*, getWritePtr, (), (override));
        MOCK_METHOD(bool, owned, (), (const, override));
        MOCK_METHOD(void, clear, (), (override));
        MOCK_METHOD(void, push, (float value), (override));
        MOCK_METHOD(float, getLast, (), (const, override));
        MOCK_METHOD(bool, full, (), (const, override));
    };

}  // namespace rp::curtis
