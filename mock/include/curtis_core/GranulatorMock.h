#pragma once

#include "IGranulator.h"

namespace rp::curtis {

    class GranularMock : public IGranulator {
    public:
        MOCK_METHOD(void, setRepeatMin, (size_t count), (override));
        MOCK_METHOD(void, setRepeatMax, (size_t count), (override));
        MOCK_METHOD(void, setRandomRange, (size_t range), (override));
        MOCK_METHOD(void, setGlissonEnabled, (bool enabled), (override));
        MOCK_METHOD(void, setStartMinSpeed, (float speed), (override));
        MOCK_METHOD(void, setStartMaxSpeed, (float speed), (override));
        MOCK_METHOD(void, setEndMinSpeed, (float speed), (override));
        MOCK_METHOD(void, setEndMaxSpeed, (float speed), (override));
    };

}  // namespace rp::curtis
