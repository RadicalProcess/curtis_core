#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/PolarityMock.h>

#include <curtis_core/SegmentDetector.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_SegmentDetector : public Test
    {
    protected:
        void SetUp() override
        {
            bufferMock_ = std::make_unique<NiceMock<BufferMock>>();
            bufferMockPtr_ = bufferMock_.get();

            polarityMock_ = std::make_unique<NiceMock<PolarityMock>>();
            polarityMockPtr_ = polarityMock_.get();

            ON_CALL(factoryMock_, createBuffer(_)).WillByDefault(Return(ByMove(std::move(bufferMock_))));
            ON_CALL(factoryMock_, createPolarity()).WillByDefault(Return(ByMove(std::move(polarityMock_))));
        }

        void TearDown() override
        {
            bufferMock_ = nullptr;
            polarityMock_ = nullptr;
        }

        std::unique_ptr<BufferMock> bufferMock_;
        BufferMock* bufferMockPtr_;

        std::unique_ptr<PolarityMock> polarityMock_;
        PolarityMock* polarityMockPtr_;

        NiceMock<BufferMock> processBufferMock_;
        NiceMock<FactoryMock> factoryMock_;
    };

    TEST_F(UnitTest_SegmentDetector, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer(4800));
        EXPECT_CALL(factoryMock_, createPolarity());

        SegmentDetector(48000.0f, factoryMock_);
    }

    TEST_F(UnitTest_SegmentDetector, process_less_than_min)
    {
        auto&& segmentDetector = SegmentDetector(48000.0f, factoryMock_);
        segmentDetector.setSegmentMinLength(1); // 48 samples
        ON_CALL(*bufferMockPtr_, size()).WillByDefault(Return(24));
        ON_CALL(processBufferMock_, size()).WillByDefault(Return(23));

        EXPECT_CALL(*bufferMockPtr_, append(_));
        segmentDetector.process(processBufferMock_);
    }
}

