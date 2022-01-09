#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/RandomRangeMock.h>

#include <curtis_core/Granulator.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Granulator : public Test
    {
    protected:
        void SetUp() override
        {
            playBufferMock_ = std::make_unique<BufferMock>();
            playBufferMockPtr_ = playBufferMock_.get();

            repeatRandomRangeMock_ = std::make_unique<NiceMock<RandomRangeMock<size_t>>>();
            repeatRandomRangeMockPtr_ = repeatRandomRangeMock_.get();

            startSpeedRandomRangeMock_ = std::make_unique<NiceMock<RandomRangeMock<float>>>();
            startSpeedRandomRangePtr_ = startSpeedRandomRangeMock_.get();

            endSpeedRandomRangeMock_ = std::make_unique<NiceMock<RandomRangeMock<float>>>();
            endSpeedRandomRangePtr_ = endSpeedRandomRangeMock_.get();

            ON_CALL(factoryMock_, createBuffer(_))
                .WillByDefault(Return(ByMove(std::move(playBufferMock_))));

            ON_CALL(factoryMock_, createRandomRangeSizeT(_, _))
                .WillByDefault(Return(ByMove(std::move(repeatRandomRangeMock_))));

            ON_CALL(factoryMock_, createRandomRangeFloat(_, _))
                .WillByDefault(Invoke([&](float min, float max){
                    if(count_++ == 0)
                        return std::move(startSpeedRandomRangeMock_);
                    else
                        return std::move(endSpeedRandomRangeMock_);
                }));
        }

        void TearDown() override
        {
            playBufferMock_ = nullptr;
            repeatRandomRangeMock_ = nullptr;
            startSpeedRandomRangeMock_ = nullptr;
            endSpeedRandomRangeMock_ = nullptr;
        }

    protected:
        NiceMock<SegmentBankMock> segmentBankMock_;
        NiceMock<FactoryMock> factoryMock_;
        NiceMock<BufferMock> bufferMock_;

        std::unique_ptr<BufferMock> playBufferMock_;
        std::unique_ptr<RandomRangeMock<size_t>> repeatRandomRangeMock_;
        std::unique_ptr<RandomRangeMock<float>> startSpeedRandomRangeMock_;
        std::unique_ptr<RandomRangeMock<float>> endSpeedRandomRangeMock_;

        BufferMock* playBufferMockPtr_;
        RandomRangeMock<size_t>* repeatRandomRangeMockPtr_;
        RandomRangeMock<float>* startSpeedRandomRangePtr_;
        RandomRangeMock<float>* endSpeedRandomRangePtr_;

        size_t count_ { 0 };
    };

    TEST_F(UnitTest_Granulator, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer(_));
        EXPECT_CALL(factoryMock_, createRandomRangeSizeT(_, _));
        EXPECT_CALL(factoryMock_, createRandomRangeFloat(_, _)).Times(2);

        Granulator(segmentBankMock_, 0, factoryMock_);
    }

    TEST_F(UnitTest_Granulator, setRepeatMin_Max)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_CALL(*repeatRandomRangeMockPtr_, setMin(1));
        EXPECT_CALL(*repeatRandomRangeMockPtr_, setMax(5));

        granulator.setRepeatMin(1);
        granulator.setRepeatMax(5);
    }

    TEST_F(UnitTest_Granulator, setStartMin_Max)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_CALL(*startSpeedRandomRangePtr_, setMin(0.5f));
        EXPECT_CALL(*startSpeedRandomRangePtr_, setMax(1.5f));

        granulator.setStartMinSpeed(0.5f);
        granulator.setStartMaxSpeed(1.5f);
    }

    TEST_F(UnitTest_Granulator, setEndMin_Max)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_CALL(*endSpeedRandomRangePtr_, setMin(0.5f));
        EXPECT_CALL(*endSpeedRandomRangePtr_, setMax(1.5f));

        granulator.setEndMinSpeed(0.5f);
        granulator.setEndMaxSpeed(1.5f);
    }

    TEST_F(UnitTest_Granulator, process)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);

        EXPECT_CALL(segmentBankMock_, getCache(_));
        granulator.process(bufferMock_);
    }

    TEST_F(UnitTest_Granulator, process_no_segment_ready)
    {
        ON_CALL(segmentBankMock_, getLatestCacheIndex()).WillByDefault(Return(std::nullopt));

        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);

        EXPECT_CALL(segmentBankMock_, getCache(_)).Times(0);
        granulator.process(bufferMock_);
    }
}
