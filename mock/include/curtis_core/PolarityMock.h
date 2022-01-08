#pragma once

#include <gmock/gmock.h>

#include <curtis_core/IPolarity.h>

namespace rp::curtis
{
    class PolarityMock : public IPolarity {
    public:
        MOCK_METHOD(void, set, (float value, bool notification), (override));
        MOCK_METHOD(void, addListener, (Listener* listener), (override));
        MOCK_METHOD(void, removeListener, (Listener* listener), (override));
    };

    class PolarityListenerMock : public IPolarity::Listener {
    public:
        MOCK_METHOD(void, onPolarityChanged, (), (override));
    };
}
