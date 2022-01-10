#pragma once

#include <curtis_core/IRandomizer.h>

namespace rp::curtis {

    class RandomizerMock : public IRandomizer {
    public:
        MOCK_METHOD(void, setRange, (size_t range), (override));
        MOCK_METHOD(size_t, getValue, (), (const, override));
    };

}  // namespace rp::curtis
