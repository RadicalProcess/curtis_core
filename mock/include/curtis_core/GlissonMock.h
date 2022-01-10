#pragma once

#include <curtis_core/IGlisson.h>

namespace rp::curtis
{
    class GlissonMock : public IGlisson {
    public:
        MOCK_METHOD(void, update, (), (override));
        MOCK_METHOD(float, getSpeedAt, (float phase), (override));
        MOCK_METHOD(void, setGlissonEnabled, (bool enabled), (override));
        MOCK_METHOD(IRandomRange<float>&, getStartRandomRange, (), (override));
        MOCK_METHOD(IRandomRange<float>&, getEndRandomRange, (), (override));
    };
}
