#pragma once

#include <curtis_core/ICounter.h>

namespace rp::curtis
{
    class RepeaterMock : public IRepeater {
    public:
        MOCK_METHOD(IRandomRange<size_t>&, getRepeatRandomRange, (), (override));
        MOCK_METHOD(void, count, (const std::function<void()>& onRepeatEnded), (override));
    };
}
