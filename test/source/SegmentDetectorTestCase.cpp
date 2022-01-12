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

            ON_CALL(factoryMock_, createBuffer(4800, false)).WillByDefault(Return(ByMove(std::move(bufferMock_))));
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

        NiceMock<FactoryMock> factoryMock_;
    };

    TEST_F(UnitTest_SegmentDetector, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer(4800, false));
        EXPECT_CALL(factoryMock_, createPolarity());

        SegmentDetector(48000.0f, 4800, factoryMock_);
    }

    TEST_F(UnitTest_SegmentDetector, subscription)
    {
        EXPECT_CALL(*polarityMockPtr_, addListener(_));
        EXPECT_CALL(*polarityMockPtr_, removeListener(_));

        SegmentDetector(48000.0f, 4800, factoryMock_);
    }

    TEST_F(UnitTest_SegmentDetector, process_append_sample)
    {
        auto&& segmentDetector = SegmentDetector(48000.0f, 4800, factoryMock_);
        auto&& buffer = Buffer(1);
        buffer.push(1);

        EXPECT_CALL(*polarityMockPtr_, set(_, true)).Times(0);
        EXPECT_CALL(*bufferMockPtr_, full()).Times(1).WillOnce(Return(false));
        EXPECT_CALL(*bufferMockPtr_, clear()).Times(0);
        EXPECT_CALL(*bufferMockPtr_, push(_)).Times(1);

        segmentDetector.process(buffer);
    }

    TEST_F(UnitTest_SegmentDetector, process_append_sample_porality_check)
    {
        auto&& segmentDetector = SegmentDetector(48000.0f, 4800, factoryMock_);
        auto&& buffer = Buffer(1);
        buffer.push(1);

        segmentDetector.setSegmentMinLength(0);
        EXPECT_CALL(*polarityMockPtr_, set(_, true)).Times(1);
        EXPECT_CALL(*bufferMockPtr_, full()).Times(1).WillOnce(Return(false));
        EXPECT_CALL(*bufferMockPtr_, clear()).Times(0);
        EXPECT_CALL(*bufferMockPtr_, push(_)).Times(1);

        segmentDetector.process(buffer);
    }

    TEST_F(UnitTest_SegmentDetector, process_append_sample_clear)
    {
        auto&& segmentDetector = SegmentDetector(48000.0f, 4800, factoryMock_);
        auto&& buffer = Buffer(1);
        buffer.push(1);

        EXPECT_CALL(*polarityMockPtr_, set(_, true)).Times(0);
        EXPECT_CALL(*bufferMockPtr_, full()).Times(1).WillOnce(Return(true));
        EXPECT_CALL(*bufferMockPtr_, clear()).Times(1);
        EXPECT_CALL(*bufferMockPtr_, push(_)).Times(1);

        segmentDetector.process(buffer);
    }
}

