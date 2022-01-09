#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>

#include <curtis_core/Granulator.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Granulator : public Test
    {

    protected:
        NiceMock<SegmentBankMock> segmentBankMock_;
        NiceMock<FactoryMock> factoryMock_;
        NiceMock<BufferMock> bufferMock_;
    };

    TEST_F(UnitTest_Granulator, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer());

        Granulator(segmentBankMock_, factoryMock_);
    }

    TEST_F(UnitTest_Granulator, process)
    {
        auto&& granulator = Granulator(segmentBankMock_, factoryMock_);

        EXPECT_CALL(segmentBankMock_, getCache(_));
        granulator.process(bufferMock_);
    }

    TEST_F(UnitTest_Granulator, process_no_segment_ready)
    {
        ON_CALL(segmentBankMock_, getCache(_)).WillByDefault(Return(nullptr));

        auto&& granulator = Granulator(segmentBankMock_, factoryMock_);

        EXPECT_CALL(segmentBankMock_, getCache(_));
        granulator.process(bufferMock_);
    }
}
