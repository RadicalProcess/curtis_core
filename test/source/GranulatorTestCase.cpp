#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/RandomRangeMock.h>
#include <curtis_core/GlissonMock.h>
#include <curtis_core/CounterMock.h>
#include <curtis_core/ReadBufferMock.h>
#include <curtis_core/RandomizerMock.h>

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

            randomizerMock_ = std::make_unique<NiceMock<RandomizerMock>>();
            randomizerMockPtr_ = randomizerMock_.get();

            ON_CALL(factoryMock_, createGlisson())
                .WillByDefault(Return(ByMove(std::move(glissonMock_))));

            ON_CALL(factoryMock_, createCounter())
                    .WillByDefault(Return(ByMove(std::move(counterMock_))));

            ON_CALL(factoryMock_, createReadBuffer(_))
                    .WillByDefault(Return(ByMove(std::move(readBufferMock_))));

            ON_CALL(factoryMock_, createRandomizer())
                    .WillByDefault((Return(ByMove(std::move(randomizerMock_)))));

            ON_CALL(*glissonMockPtr_, getStartRandomRange())
                .WillByDefault(ReturnRef(startRandomRangeMock_));

            ON_CALL(*glissonMockPtr_, getEndRandomRange())
                    .WillByDefault(ReturnRef(endRandomRangeMock_));

            ON_CALL(*counterMockPtr_, getRandomRange())
                    .WillByDefault(ReturnRef(counterRandomRangeMock_));

            dummyBuffer_.resize(1, 0.0f);
            ON_CALL(bufferMock_, getWritePtr())
                    .WillByDefault(Return(dummyBuffer_.data()));

            ON_CALL(bufferMock_, size())
                    .WillByDefault(Return(1));
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
        std::unique_ptr<RandomizerMock> randomizerMock_;

        GlissonMock* glissonMockPtr_;
        CounterMock* counterMockPtr_;
        ReadBufferMock* readBufferMockPtr_;
        RandomizerMock* randomizerMockPtr_;
        std::vector<float> dummyBuffer_;
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
        EXPECT_CALL(*readBufferMockPtr_, getSample()).WillOnce(Return(0.5f));
        EXPECT_CALL(*readBufferMockPtr_, getPhase()).WillOnce(Return(0.5f));
        EXPECT_CALL(*glissonMockPtr_, getSpeedAt(0.5f)).WillOnce(Return(1.0f));
        EXPECT_CALL(*readBufferMockPtr_, advancePlayHead(1.0f)).WillOnce(Return(false));
        granulator.process(bufferMock_);
    }

    TEST_F(UnitTest_Granulator, process_playhead_reaches_the_end)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);

        ON_CALL(*readBufferMockPtr_, getSample()).WillByDefault(Return(0.5f));
        ON_CALL(*readBufferMockPtr_, advancePlayHead(_)).WillByDefault(Return(true));

        EXPECT_CALL(*counterMockPtr_, count()).WillOnce(Return(false));
        EXPECT_CALL(*glissonMockPtr_, update());
        EXPECT_CALL(*randomizerMockPtr_, getValue()).WillOnce(Return(0));
        EXPECT_CALL(segmentBankMock_, size()).WillOnce(Return(1));
        EXPECT_CALL(segmentBankMock_, getCache(_)).WillOnce(ReturnRef(bufferMock_));
        EXPECT_CALL(*readBufferMockPtr_, updateBuffer(_));

        granulator.process(bufferMock_);
    }

    TEST_F(UnitTest_Granulator, process_playhead_reaches_the_end_count_reaches_end)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);

        ON_CALL(*readBufferMockPtr_, getSample()).WillByDefault(Return(0.5f));
        ON_CALL(*readBufferMockPtr_, advancePlayHead(_)).WillByDefault(Return(true));
        ON_CALL(*counterMockPtr_, count()).WillByDefault(Return(true));

        EXPECT_CALL(segmentBankMock_, getLatestCacheIndex()).WillOnce(Return(2));
        EXPECT_CALL(*glissonMockPtr_, update());
        EXPECT_CALL(*randomizerMockPtr_, getValue()).WillOnce(Return(1));
        EXPECT_CALL(segmentBankMock_, size()).WillOnce(Return(1));
        EXPECT_CALL(segmentBankMock_, getCache(1)).WillOnce(ReturnRef(bufferMock_));
        EXPECT_CALL(*readBufferMockPtr_, updateBuffer(_));

        granulator.process(bufferMock_);
    }
}
