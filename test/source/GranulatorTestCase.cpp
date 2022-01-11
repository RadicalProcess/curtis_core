#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/RandomRangeMock.h>
#include <curtis_core/GlissonMock.h>
#include <curtis_core/CounterMock.h>
#include <curtis_core/ReadBufferMock.h>

#include <curtis_core/Granulator.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Granulator : public Test
    {
    protected:
        void SetUp() override
        {
            counterMock_ = std::make_unique<NiceMock<CounterMock>>();
            counterMockPtr_ = counterMock_.get();

            glissonMock_ = std::make_unique<NiceMock<GlissonMock>>();
            glissonMockPtr_ = glissonMock_.get();

            readBufferMock_ = std::make_unique<NiceMock<ReadBufferMock>>();
            readBufferMockPtr_ = readBufferMock_.get();

            ON_CALL(factoryMock_, createGlisson())
                .WillByDefault(Return(ByMove(std::move(glissonMock_))));

            ON_CALL(factoryMock_, createCounter())
                    .WillByDefault(Return(ByMove(std::move(counterMock_))));

            ON_CALL(factoryMock_, createReadBuffer(_))
                    .WillByDefault(Return(ByMove(std::move(readBufferMock_))));

            ON_CALL(*glissonMockPtr_, getStartRandomRange())
                .WillByDefault(ReturnRef(startRandomRangeMock_));

            ON_CALL(*glissonMockPtr_, getEndRandomRange())
                    .WillByDefault(ReturnRef(endRandomRangeMock_));

            ON_CALL(*counterMockPtr_, getRandomRange())
                    .WillByDefault(ReturnRef(counterRandomRangeMock_));
        }

        void TearDown() override
        {
            glissonMock_ = nullptr;
            counterMock_ = nullptr;
            readBufferMock_ = nullptr;
        }

    protected:
        NiceMock<SegmentBankMock> segmentBankMock_;
        NiceMock<FactoryMock> factoryMock_;
        NiceMock<BufferMock> bufferMock_;
        NiceMock<RandomRangeMock<float>> startRandomRangeMock_;
        NiceMock<RandomRangeMock<float>> endRandomRangeMock_;
        NiceMock<RandomRangeMock<size_t>> counterRandomRangeMock_;

        std::unique_ptr<GlissonMock> glissonMock_;
        std::unique_ptr<CounterMock> counterMock_;
        std::unique_ptr<ReadBufferMock> readBufferMock_;

        GlissonMock* glissonMockPtr_;
        CounterMock* counterMockPtr_;
        ReadBufferMock* readBufferMockPtr_;
    };

    TEST_F(UnitTest_Granulator, construction)
    {
        EXPECT_CALL(factoryMock_, createGlisson());
        EXPECT_CALL(factoryMock_, createRandomizer());
        EXPECT_CALL(factoryMock_, createCounter());
        EXPECT_CALL(factoryMock_, createReadBuffer(_));

        Granulator(segmentBankMock_, 0, factoryMock_);
    }

    TEST_F(UnitTest_Granulator, setRepeatMin_Max)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_CALL(counterRandomRangeMock_, setMin(1));
        EXPECT_CALL(counterRandomRangeMock_, setMax(5));

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

        EXPECT_CALL(bufferMock_, getWritePtr());
        EXPECT_CALL(bufferMock_, size()).WillOnce(Return(1));
        EXPECT_CALL(*readBufferMockPtr_, getSample());
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
