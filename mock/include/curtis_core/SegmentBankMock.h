#pragma once

#include <curtis_core/ISegmentBank.h>

namespace rp::curtis
{
    class SegmentBankMock : public ISegmentBank {
    public:
        MOCK_METHOD(const IBuffer*, getCache, (size_t fromNewest), (const, override));
    };

}  // namespace rp::curtis
