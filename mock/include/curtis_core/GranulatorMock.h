#pragma once

#include <curtis_core/IGranulator.h>

namespace rp::curtis {

    class GranulatorMock : public IGranulator {
    public:
        MOCK_METHOD(void, setRepeatMin, (size_t count), (override));
        MOCK_METHOD(void, setRepeatMax, (size_t count), (override));
        MOCK_METHOD(void, setRandomRange, (size_t range), (override));
        MOCK_METHOD(void, setGlissonEnabled, (bool enabled), (override));
        MOCK_METHOD(void, setStartMinSpeed, (float speed), (override));
        MOCK_METHOD(void, setStartMaxSpeed, (float speed), (override));
        MOCK_METHOD(void, setEndMinSpeed, (float speed), (override));
        MOCK_METHOD(void, setEndMaxSpeed, (float speed), (override));
        MOCK_METHOD(void, process, (IBuffer& buffer), (override));
    };

}  // namespace rp::curtis
