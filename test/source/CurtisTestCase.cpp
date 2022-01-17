#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/SegmentDetectorMock.h>
#include <curtis_core/GranulatorMock.h>
#include <curtis_core/BufferMock.h>
#include <curtis_core/InputMixMock.h>
#include <curtis_core/CounterMock.h>
#include <curtis_core/RandomRangeMock.h>
#include <curtis_core/GlissonMock.h>
#include <curtis_core/PannerMock.h>

#include <curtis_core/Curtis.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Curtis : public Test
    {
    protected:
        void SetUp() override
        {
            segmentBankMock_ = std::make_unique<NiceMock<SegmentBankMock>>();
            segmentDetectorMock_ = std::make_unique<NiceMock<SegmentDetectorMock>>();
            granulatorMock_ = std::make_unique<NiceMock<GranulatorMock>>();
            inputMixMock_ = std::make_unique<NiceMock<InputMixMock>>();

            segmentDetectorMockPtr_ = segmentDetectorMock_.get();
            granulatorMockPtr_ = granulatorMock_.get();
            inputMixMockPtr_ = inputMixMock_.get();

            ON_CALL(factoryMock_, createInputMix())
                    .WillByDefault(Return(ByMove(std::move(inputMixMock_))));

            ON_CALL(factoryMock_, createSegmentBank(_, _))
                .WillByDefault(Return(ByMove(std::move(segmentBankMock_))));

            ON_CALL(factoryMock_, createSegmentDetector(_,_))
                    .WillByDefault(Return(ByMove(std::move(segmentDetectorMock_))));

            ON_CALL(factoryMock_, createGranulator(_,_))
                    .WillByDefault(Return(ByMove(std::move(granulatorMock_))));


        }

        void TearDown() override
        {
            segmentBankMock_ = nullptr;
            segmentDetectorMock_ = nullptr;
            granulatorMock_ = nullptr;
            inputMixMock_ = nullptr;
        }

        NiceMock<FactoryMock> factoryMock_;
        std::unique_ptr<SegmentBankMock> segmentBankMock_;
        std::unique_ptr<SegmentDetectorMock> segmentDetectorMock_;
        std::unique_ptr<GranulatorMock> granulatorMock_;
        std::unique_ptr<InputMixMock> inputMixMock_;

        SegmentDetectorMock* segmentDetectorMockPtr_;
        GranulatorMock* granulatorMockPtr_;
        InputMixMock* inputMixMockPtr_;

        NiceMock<BufferMock> bufferLeftMock_, bufferRightMock_;
        NiceMock<RandomRangeMock<size_t>> randomRangeSizeTMock_;
        NiceMock<RandomRangeMock<float>> randomRangeFloatMock_;

        NiceMock<CounterMock> counterMock_;
        NiceMock<GlissonMock> glissonMock_;
        NiceMock<PannerMock> pannerMock_;
    };

    TEST_F(UnitTest_Curtis, construction)
    {
        EXPECT_CALL(factoryMock_, createSegmentBank(_, _));
        EXPECT_CALL(factoryMock_, createSegmentDetector(48000.0f, _));
        EXPECT_CALL(factoryMock_, createGranulator(_, _));
        EXPECT_CALL(*segmentDetectorMockPtr_, addListener(_));

        Curtis(48000.0f, factoryMock_);
    }

    TEST_F(UnitTest_Curtis, setMix)
    {
        EXPECT_CALL(*inputMixMockPtr_, setMix(0.2f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setMix(0.2f);
    }

    TEST_F(UnitTest_Curtis, setSegmentMinLength)
    {
        EXPECT_CALL(*segmentDetectorMockPtr_, setSegmentMinLength(50));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setSegmentMinLength(50);
    }

    TEST_F(UnitTest_Curtis, setDensity)
    {
        EXPECT_CALL(*granulatorMockPtr_, setDensity(50.0f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setDensity(50.0f);
    }

    TEST_F(UnitTest_Curtis, setRepeatMin)
    {
        EXPECT_CALL(*granulatorMockPtr_, getCounter())
            .WillOnce(ReturnRef(counterMock_));
        EXPECT_CALL(counterMock_, getRandomRange())
            .WillOnce(ReturnRef(randomRangeSizeTMock_));
        EXPECT_CALL(randomRangeSizeTMock_, setMin(5));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setRepeatMin(5);
    }

    TEST_F(UnitTest_Curtis, setRepeatMax)
    {
        EXPECT_CALL(*granulatorMockPtr_, getCounter())
                .WillOnce(ReturnRef(counterMock_));
        EXPECT_CALL(counterMock_, getRandomRange())
                .WillOnce(ReturnRef(randomRangeSizeTMock_));
        EXPECT_CALL(randomRangeSizeTMock_, setMax(5));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setRepeatMax(5);
    }

    TEST_F(UnitTest_Curtis, setRandomRange)
    {
        EXPECT_CALL(*granulatorMockPtr_, setRandomRange(5));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setRandomRange(5);
    }

    TEST_F(UnitTest_Curtis, setGlissonEnabled)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
            .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, setGlissonEnabled(true));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setGlissonEnabled(true);
    }

    TEST_F(UnitTest_Curtis, setStartMinSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getStartRandomRange())
                .WillOnce(ReturnRef(randomRangeFloatMock_));
        EXPECT_CALL(randomRangeFloatMock_, setMin(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setStartMinSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, setStartMaxSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getStartRandomRange())
                .WillOnce(ReturnRef(randomRangeFloatMock_));
        EXPECT_CALL(randomRangeFloatMock_, setMax(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setStartMaxSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, setEndMinSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getEndRandomRange())
                .WillOnce(ReturnRef(randomRangeFloatMock_));
        EXPECT_CALL(randomRangeFloatMock_, setMin(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setEndMinSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, setEndMaxSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getEndRandomRange())
                .WillOnce(ReturnRef(randomRangeFloatMock_));
        EXPECT_CALL(randomRangeFloatMock_, setMax(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setEndMaxSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, setStartLeft)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setStartLeft(-0.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setStartLeft(-0.5f);
    }

    TEST_F(UnitTest_Curtis, setStartRight)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setStartRight(0.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setStartRight(0.5f);
    }

    TEST_F(UnitTest_Curtis, setEndLeft)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setEndLeft(-0.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setEndLeft(-0.5f);
    }

    TEST_F(UnitTest_Curtis, setEndRight)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setEndRight(0.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setEndRight(0.5f);
    }

    TEST_F(UnitTest_Curtis, process)
    {
        {
            InSequence seq;
            EXPECT_CALL(*inputMixMockPtr_, process(_, _));
            EXPECT_CALL(*segmentDetectorMockPtr_, process(_));
            EXPECT_CALL(*granulatorMockPtr_, process(_, _));
        }

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.process(bufferLeftMock_, bufferRightMock_);
    }
}

