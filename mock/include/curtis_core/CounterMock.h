#pragma once

#include <curtis_core/ICounter.h>

namespace rp::curtis {

    class CounterMock : public ICounter {
    public:
        MOCK_METHOD(void, setMaxCount, (size_t), (override));
        MOCK_METHOD(bool, count, (), (override));
    };

}  // namespace rp::curtis
