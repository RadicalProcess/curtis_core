#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/SegmentBankMock.h>

#include <curtis_core/Curtis.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Curtis : public Test
    {
    protected:
        void SetUp() override
        {
            segmentBankMock_ = std::make_unique<NiceMock<SegmentBankMock>>();

            ON_CALL(factoryMock_, createSegmentBank(_))
                .WillByDefault(Return(ByMove(std::move(segmentBankMock_))));
        }

        void TearDown() override
        {
            segmentBankMock_ = nullptr;
        }

        NiceMock<FactoryMock> factoryMock_;
        std::unique_ptr<SegmentBankMock> segmentBankMock_;
    };

    TEST_F(UnitTest_Curtis, construction)
    {
        EXPECT_CALL(factoryMock_, createSegmentBank(_));
        EXPECT_CALL(factoryMock_, createSegmentDetector(48000.0f));
        EXPECT_CALL(factoryMock_, createGranulator(_));

        Curtis(48000.0f, factoryMock_);
    }
}

