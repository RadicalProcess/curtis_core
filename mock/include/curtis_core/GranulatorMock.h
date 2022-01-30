#pragma once

#include <gmock/gmock.h>

#include <curtis_core/IGranulator.h>

namespace rp::curtis {

    class GranulatorMock : public IGranulator {
    public:
        ~GranulatorMock() = default;
        MOCK_METHOD(void, setDensity, (int percentage), (override));
        MOCK_METHOD(void, setRandomRange, (size_t range), (override));
        MOCK_METHOD(ICounter&, getCounter, (), (override));
        MOCK_METHOD(IGlisson&, getGlisson, (), (override));
        MOCK_METHOD(IPanner&, getPanner, (), (override));
        MOCK_METHOD(void, process, (IBuffer& leftBuffer, IBuffer& rightBuffer), (override));
        MOCK_METHOD(void, addListener, (Listener* listener), (override));
        MOCK_METHOD(void, removeListener, (Listener* listener), (override));
    };

}  // namespace rp::curtis
