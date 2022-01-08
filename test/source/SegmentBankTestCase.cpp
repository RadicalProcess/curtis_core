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
            bufferMockPtr_ = bufferMock_.get();

            ON_CALL(factoryMock_, createBuffer())
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
        BufferMock* bufferMockPtr_;
    };

    TEST_F(UnitTest_SegmentBank, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer()).Times(1);
        SegmentBank(1, factoryMock_);
    }

    TEST_F(UnitTest_SegmentBank, getCache)
    {
        auto&& segmentBank = SegmentBank(1, factoryMock_);
        EXPECT_EQ(nullptr, segmentBank.getCache(0));
    }

    TEST_F(UnitTest_SegmentBank, getCache_segment_detected)
    {
        auto&& segmentBank = SegmentBank(1, factoryMock_);
        static_cast<ISegmentDetector::Listener*>(&segmentBank)->onSegmentDetected(detectedSegmentMock_);

        EXPECT_NE(nullptr, segmentBank.getCache(0));
    }
}
