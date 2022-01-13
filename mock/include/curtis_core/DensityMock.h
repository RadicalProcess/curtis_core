#pragma once

#include <curtis_core/IDensity.h>

namespace rp::curtis
{

    class DensityMock : public IDensity {
    public:
        MOCK_METHOD(void, set, (int percentage), (override));
        MOCK_METHOD(void, roll, (), (override));
        MOCK_METHOD(bool, get, (), (const, override));
    };

}  // namespace rp::curtis
