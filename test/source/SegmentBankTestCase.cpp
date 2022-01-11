#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/SegmentBank.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_SegmentBank : public Test
    {
    protected:
        void SetUp() override
        {
            bufferMock_ = std::make_unique<NiceMock<BufferMock>>();

            ON_CALL(factoryMock_, createBuffer(10, true))
                .WillByDefault(Return(ByMove(std::move(bufferMock_))));
        }

        void TearDown() override
        {
            bufferMock_ = nullptr;
        }

    protected:
        NiceMock<FactoryMock> factoryMock_;

        std::unique_ptr<BufferMock> bufferMock_;
        NiceMock<BufferMock> detectedSegmentMock_;
    };

    TEST_F(UnitTest_SegmentBank, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer(10, true)).Times(1);
        SegmentBank(1, 10, factoryMock_);
    }

}
