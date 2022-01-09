#pragma once

#include <gmock/gmock.h>

#include <curtis_core/IRandomRange.h>

namespace rp::curtis {

    template <typename T>
    class RandomRangeMock : public IRandomRange<T> {
    public:
        MOCK_METHOD(void, setMin, (T value), (override));
        MOCK_METHOD(void, setMax, (T value), (override));
        MOCK_METHOD(T, getValue, (), (const, override));
    };

}  // namespace rp::curtis

