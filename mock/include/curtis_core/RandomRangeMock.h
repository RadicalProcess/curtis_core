#pragma once

#include <gmock/gmock.h>

#include <curtis_core/IRandomRange.h>

namespace rp::curtis {

    template <typename T>
    class RandomRangeMock : public IRandomRange {
    public:
        MOCK_METHOD(void, setA, (float value), (override));
        MOCK_METHOD(void, setB, (float value), (override));
        MOCK_METHOD(float, getValue, (), (const, override));
    };

}  // namespace rp::curtis

