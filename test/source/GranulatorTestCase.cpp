#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/FactoryMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/RandomRangeMock.h>
#include <curtis_core/GlissonMock.h>
#include <curtis_core/CounterMock.h>
#include <curtis_core/ReadBufferMock.h>
#include <curtis_core/RandomizerMock.h>
#include <curtis_core/DensityMock.h>
#include <curtis_core/PannerMock.h>

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

            pannerMock_ = std::make_unique<NiceMock<PannerMock>>();
            pannerMockPtr_ = pannerMock_.get();

            glissonMock_ = std::make_unique<NiceMock<GlissonMock>>();
            glissonMockPtr_ = glissonMock_.get();

            readBufferMock_ = std::make_unique<NiceMock<ReadBufferMock>>();
            readBufferMockPtr_ = readBufferMock_.get();

            randomizerMock_ = std::make_unique<NiceMock<RandomizerMock>>();
            randomizerMockPtr_ = randomizerMock_.get();

            densityMock_ = std::make_unique<NiceMock<DensityMock>>();
            densityMockPtr_ = densityMock_.get();

            ON_CALL(factoryMock_, createGlisson())
                .WillByDefault(Return(ByMove(std::move(glissonMock_))));

            ON_CALL(factoryMock_, createCounter())
                    .WillByDefault(Return(ByMove(std::move(counterMock_))));

            ON_CALL(factoryMock_, createReadBuffer(_))
                    .WillByDefault(Return(ByMove(std::move(readBufferMock_))));

            ON_CALL(factoryMock_, createRandomizer())
                    .WillByDefault((Return(ByMove(std::move(randomizerMock_)))));

            ON_CALL(factoryMock_, createDensity())
                    .WillByDefault((Return(ByMove(std::move(densityMock_)))));

            ON_CALL(factoryMock_, createPanner())
                    .WillByDefault((Return(ByMove(std::move(pannerMock_)))));

            ON_CALL(*glissonMockPtr_, getStartRandomRange())
                .WillByDefault(ReturnRef(startRandomRangeMock_));

            ON_CALL(*glissonMockPtr_, getEndRandomRange())
                    .WillByDefault(ReturnRef(endRandomRangeMock_));


            dummyBuffer_.resize(1, 0.0f);
            ON_CALL(leftBufferMock_, getWritePtr())
                    .WillByDefault(Return(dummyBuffer_.data()));

            ON_CALL(rightBufferMock_, getWritePtr())
                    .WillByDefault(Return(dummyBuffer_.data()));

            ON_CALL(leftBufferMock_, size())
                    .WillByDefault(Return(1));
        }

        void TearDown() override
        {
            glissonMock_ = nullptr;
            counterMock_ = nullptr;
            readBufferMock_ = nullptr;
            densityMock_ = nullptr;
            counterMock_ = nullptr;
            pannerMock_ = nullptr;
        }

    protected:
        NiceMock<SegmentBankMock> segmentBankMock_;
        NiceMock<FactoryMock> factoryMock_;
        NiceMock<BufferMock> leftBufferMock_, rightBufferMock_;
        NiceMock<RandomRangeMock<float>> startRandomRangeMock_;
        NiceMock<RandomRangeMock<float>> endRandomRangeMock_;

        std::unique_ptr<GlissonMock> glissonMock_;
        std::unique_ptr<CounterMock> counterMock_;
        std::unique_ptr<ReadBufferMock> readBufferMock_;
        std::unique_ptr<RandomizerMock> randomizerMock_;
        std::unique_ptr<DensityMock> densityMock_;
        std::unique_ptr<PannerMock> pannerMock_;

        GlissonMock* glissonMockPtr_;
        CounterMock* counterMockPtr_;
        ReadBufferMock* readBufferMockPtr_;
        RandomizerMock* randomizerMockPtr_;
        DensityMock* densityMockPtr_;
        PannerMock* pannerMockPtr_;
        std::vector<float> dummyBuffer_;
    };

    TEST_F(UnitTest_Granulator, construction)
    {
        EXPECT_CALL(factoryMock_, createGlisson());
        EXPECT_CALL(factoryMock_, createRandomizer());
        EXPECT_CALL(factoryMock_, createCounter());
        EXPECT_CALL(factoryMock_, createReadBuffer(_));
        EXPECT_CALL(factoryMock_, createDensity());
        EXPECT_CALL(factoryMock_, createPanner());

        Granulator(segmentBankMock_, 0, factoryMock_);
    }

    TEST_F(UnitTest_Granulator, setDensity)
    {
        EXPECT_CALL(*densityMockPtr_, set(50));

        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        granulator.setDensity(50);
    }

    TEST_F(UnitTest_Granulator, setRandomRange)
    {
        EXPECT_CALL(*randomizerMockPtr_, setRange(5));

        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        granulator.setRandomRange(5);
    }

    TEST_F(UnitTest_Granulator, getCounter)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_EQ(counterMockPtr_, &granulator.getCounter());
    }

    TEST_F(UnitTest_Granulator, getGlisson)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_EQ(glissonMockPtr_, &granulator.getGlisson());
    }

    TEST_F(UnitTest_Granulator, getPanner)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);
        EXPECT_EQ(pannerMockPtr_, &granulator.getPanner());
    }

    TEST_F(UnitTest_Granulator, process)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);

        EXPECT_CALL(*densityMockPtr_, get()).WillOnce(Return(true));
        EXPECT_CALL(leftBufferMock_, getWritePtr());
        EXPECT_CALL(leftBufferMock_, size()).WillOnce(Return(1));
        EXPECT_CALL(rightBufferMock_, getWritePtr());

        EXPECT_CALL(*readBufferMockPtr_, getSample()).WillOnce(Return(0.5f));
        EXPECT_CALL(*readBufferMockPtr_, getPhase()).WillOnce(Return(0.5f));
        EXPECT_CALL(*pannerMockPtr_, getGainAt(0.5f)).WillOnce(Return(std::tuple<float, float, float>(0.5f, 0.5f, 0.0)));
        EXPECT_CALL(*glissonMockPtr_, getSpeedAt(0.5f)).WillOnce(Return(1.0f));
        EXPECT_CALL(*readBufferMockPtr_, advancePlayHead(1.0f)).WillOnce(Return(false));
        granulator.process(leftBufferMock_, rightBufferMock_);
    }

    TEST_F(UnitTest_Granulator, process_grain_muted)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);

        EXPECT_CALL(*densityMockPtr_, get()).WillOnce(Return(false));
        EXPECT_CALL(leftBufferMock_, getWritePtr());
        EXPECT_CALL(leftBufferMock_, size()).WillOnce(Return(1));
        EXPECT_CALL(*readBufferMockPtr_, getSample()).Times(0);
        EXPECT_CALL(*readBufferMockPtr_, getPhase()).WillOnce(Return(0.5f));
        EXPECT_CALL(*glissonMockPtr_, getSpeedAt(0.5f)).WillOnce(Return(1.0f));
        EXPECT_CALL(*readBufferMockPtr_, advancePlayHead(1.0f)).WillOnce(Return(false));
        granulator.process(leftBufferMock_,  rightBufferMock_);
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
        EXPECT_CALL(segmentBankMock_, getCache(_)).WillOnce(ReturnRef(leftBufferMock_));
        EXPECT_CALL(*readBufferMockPtr_, updateBuffer(_));

        granulator.process(leftBufferMock_,  rightBufferMock_);
    }

    TEST_F(UnitTest_Granulator, process_playhead_reaches_the_end_count_reaches_end)
    {
        auto&& granulator = Granulator(segmentBankMock_, 0, factoryMock_);

        ON_CALL(*readBufferMockPtr_, getSample()).WillByDefault(Return(0.5f));
        ON_CALL(*readBufferMockPtr_, advancePlayHead(_)).WillByDefault(Return(true));
        ON_CALL(*counterMockPtr_, count()).WillByDefault(Return(true));

        EXPECT_CALL(segmentBankMock_, getLatestCacheIndex()).WillOnce(Return(2));
        EXPECT_CALL(*densityMockPtr_, roll());
        EXPECT_CALL(*glissonMockPtr_, update());
        EXPECT_CALL(*randomizerMockPtr_, getValue()).WillOnce(Return(1));
        EXPECT_CALL(segmentBankMock_, size()).WillOnce(Return(1));
        EXPECT_CALL(segmentBankMock_, getCache(1)).WillOnce(ReturnRef(leftBufferMock_));
        EXPECT_CALL(*readBufferMockPtr_, updateBuffer(_));

        granulator.process(leftBufferMock_, rightBufferMock_);
    }
}
