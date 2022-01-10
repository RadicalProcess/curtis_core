#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/RandomRangeMock.h>
#include <curtis_core/GlissonMock.h>

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

            glissonMock_ = std::make_unique<NiceMock<GlissonMock>>();
            glissonMockPtr_ = glissonMock_.get();

            ON_CALL(factoryMock_, createBuffer(_))
                .WillByDefault(Return(ByMove(std::move(playBufferMock_))));

            ON_CALL(factoryMock_, createRandomRangeSizeT(_, _))
                .WillByDefault(Return(ByMove(std::move(repeatRandomRangeMock_))));

            ON_CALL(factoryMock_, createGlisson())
                .WillByDefault(Return(ByMove(std::move(glissonMock_))));

            ON_CALL(*glissonMockPtr_, getStartRandomRange())
                .WillByDefault(ReturnRef(startRandomRangeMock_));

            ON_CALL(*glissonMockPtr_, getEndRandomRange())
                    .WillByDefault(ReturnRef(endRandomRangeMock_));
        }

        void TearDown() override
        {
            playBufferMock_ = nullptr;
            repeatRandomRangeMock_ = nullptr;
            glissonMock_ = nullptr;
        }

    protected:
        NiceMock<SegmentBankMock> segmentBankMock_;
        NiceMock<FactoryMock> factoryMock_;
        NiceMock<BufferMock> bufferMock_;
        NiceMock<RandomRangeMock<float>> startRandomRangeMock_;
        NiceMock<RandomRangeMock<float>> endRandomRangeMock_;

        std::unique_ptr<BufferMock> playBufferMock_;
        std::unique_ptr<RandomRangeMock<size_t>> repeatRandomRangeMock_;
        std::unique_ptr<GlissonMock> glissonMock_;

        BufferMock* playBufferMockPtr_;
        RandomRangeMock<size_t>* repeatRandomRangeMockPtr_;
        GlissonMock* glissonMockPtr_;
    };

    TEST_F(UnitTest_Granulator, construction)
    {
        EXPECT_CALL(factoryMock_, createBuffer(_));
        EXPECT_CALL(factoryMock_, createRandomRangeSizeT(_, _));
        EXPECT_CALL(factoryMock_, createGlisson());
        EXPECT_CALL(factoryMock_, createRandomizer());

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
        EXPECT_CALL(*glissonMockPtr_, getStartRandomRange()).Times(2);
        EXPECT_CALL(startRandomRangeMock_, setMin(0.5f));
        EXPECT_CALL(startRandomRangeMock_, setMax(1.5f));

        granulator.setStartMinSpeed(0.5f);
        granulator.setStartMaxSpeed(1.5f);
    }

    TEST_F(UnitTest_Granulator, setEndMin_Max)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_CALL(*glissonMockPtr_, getEndRandomRange()).Times(2);
        EXPECT_CALL(endRandomRangeMock_, setMin(0.5f));
        EXPECT_CALL(endRandomRangeMock_, setMax(1.5f));

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
