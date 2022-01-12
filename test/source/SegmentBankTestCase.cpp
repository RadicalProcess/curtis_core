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
    };

    TEST_F(UnitTest_SegmentBank, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer(10, true)).Times(1);
        SegmentBank(1, 10, factoryMock_);
    }

    TEST_F(UnitTest_SegmentBank, getLatestCacheIndex)
    {
        auto&& segmentBank = SegmentBank(1, 10, factoryMock_);
        EXPECT_EQ(0, segmentBank.getLatestCacheIndex());
    }

    TEST_F(UnitTest_SegmentBank, getCache)
    {
        auto&& segmentBank = SegmentBank(1, 10);
        auto&& cache = segmentBank.getCache(0);
        EXPECT_EQ(1, cache.size());
        auto* ptr = cache.getReadPtr();
        EXPECT_EQ(0.0f, ptr[0]);
    }

    TEST_F(UnitTest_SegmentBank, getSegmentDetected)
    {
        auto&& segmentBank = SegmentBank(2, 10);
        auto buffer = Buffer(10, true);
        buffer.getWritePtr()[0] = 3.0f;

        static_cast<ISegmentDetector::Listener*>(&segmentBank)->onSegmentDetected(buffer);
        EXPECT_EQ(3.0f, segmentBank.getCache(1).getReadPtr()[0]);
        EXPECT_EQ(0.0f, segmentBank.getCache(0).getReadPtr()[0]);
    }

    TEST_F(UnitTest_SegmentBank, size)
    {
        auto&& segmentBank = SegmentBank(1, 10);
        EXPECT_EQ(1, segmentBank.size());
    }
}
