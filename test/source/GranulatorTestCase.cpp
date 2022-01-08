#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>

#include <curtis_core/Granulator.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Granulator : public Test
    {

    protected:
        NiceMock<SegmentBankMock> segmentBankMock_;
    };

    TEST_F(UnitTest_Granulator, process)
    {

    }
}
