#pragma once

#include <curtis_core/ISegmentBank.h>

namespace rp::curtis
{
    class SegmentBankMock : public ISegmentBank {
    public:
        MOCK_METHOD(std::optional<size_t>, getLatestCacheIndex, (), (const, override));
        MOCK_METHOD(const IBuffer&, getCache, (size_t index), (const, override));
        MOCK_METHOD(size_t, size, (), (const, override));
    };

}  // namespace rp::curtis
