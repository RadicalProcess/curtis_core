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

            ON_CALL(factoryMock_, createGranulator(_,_,_))
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
        NiceMock<RandomRangeMock<float>> randomRangeMock_;

        NiceMock<CounterMock> counterMock_;
        NiceMock<GlissonMock> glissonMock_;
        NiceMock<PannerMock> pannerMock_;
    };

    TEST_F(UnitTest_Curtis, construction)
    {
        EXPECT_CALL(factoryMock_, createSegmentBank(_, _));
        EXPECT_CALL(factoryMock_, createSegmentDetector(48000.0f, _));
        EXPECT_CALL(factoryMock_, createGranulator(_, _, _));
        EXPECT_CALL(*segmentDetectorMockPtr_, addListener(_));

        Curtis(48000.0f, 256, factoryMock_);
    }

    TEST_F(UnitTest_Curtis, setMix)
    {
        EXPECT_CALL(*inputMixMockPtr_, setMix(0.2f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setMix(0.2f);
    }

    TEST_F(UnitTest_Curtis, setSegmentMinLength)
    {
        EXPECT_CALL(*segmentDetectorMockPtr_, setSegmentMinLength(50));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setSegmentMinLength(50);
    }

    TEST_F(UnitTest_Curtis, setDensity)
    {
        EXPECT_CALL(*granulatorMockPtr_, setDensity(50.0f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setDensity(50.0f);
    }

    TEST_F(UnitTest_Curtis, setRepeatMin)
    {
        EXPECT_CALL(*granulatorMockPtr_, getCounter())
            .WillOnce(ReturnRef(counterMock_));
        EXPECT_CALL(counterMock_, setMaxCount(5));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setRepeat(5);
    }

    TEST_F(UnitTest_Curtis, setRandomRange)
    {
        EXPECT_CALL(*granulatorMockPtr_, setRandomRange(5));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setRandomRange(5);
    }

    TEST_F(UnitTest_Curtis, setGlissonEnabled)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
            .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, setGlissonEnabled(true));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setGlissonEnabled(true);
    }

    TEST_F(UnitTest_Curtis, setStartSpeedA)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getStartRandomRange())
                .WillOnce(ReturnRef(randomRangeMock_));
        EXPECT_CALL(randomRangeMock_, setA(1.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setStartSpeedA(1.5f);
    }

    TEST_F(UnitTest_Curtis, setStartSpeedB)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getStartRandomRange())
                .WillOnce(ReturnRef(randomRangeMock_));
        EXPECT_CALL(randomRangeMock_, setB(1.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setStartSpeedB(1.5f);
    }

    TEST_F(UnitTest_Curtis, setEndSpeedA)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getEndRandomRange())
                .WillOnce(ReturnRef(randomRangeMock_));
        EXPECT_CALL(randomRangeMock_, setA(1.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setEndSpeedA(1.5f);
    }

    TEST_F(UnitTest_Curtis, setEndSpeedB)
    {
        EXPECT_CALL(*granulatorMockPtr_, getGlisson())
                .WillOnce(ReturnRef(glissonMock_));
        EXPECT_CALL(glissonMock_, getEndRandomRange())
                .WillOnce(ReturnRef(randomRangeMock_));
        EXPECT_CALL(randomRangeMock_, setB(1.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setEndSpeedB(1.5f);
    }

    TEST_F(UnitTest_Curtis, setStartPositionA)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setStartA(-0.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setStartPositionA(-0.5f);
    }

    TEST_F(UnitTest_Curtis, setStartPositionB)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setStartB(0.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setStartPositionB(0.5f);
    }

    TEST_F(UnitTest_Curtis, setEndPositionA)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setEndA(-0.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setEndPositionA(-0.5f);
    }

    TEST_F(UnitTest_Curtis, setEndPositionB)
    {
        EXPECT_CALL(*granulatorMockPtr_, getPanner())
                .WillOnce(ReturnRef(pannerMock_));
        EXPECT_CALL(pannerMock_, setEndB(0.5f));

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.setEndPositionB(0.5f);
    }

    TEST_F(UnitTest_Curtis, process)
    {
        {
            InSequence seq;
            EXPECT_CALL(*inputMixMockPtr_, process(_, _));
            EXPECT_CALL(*segmentDetectorMockPtr_, process(_));
            EXPECT_CALL(*granulatorMockPtr_, process(_, _));
        }

        auto&& curtis = Curtis(48000.0f, 256, factoryMock_);
        curtis.process(bufferLeftMock_, bufferRightMock_);
    }
}

