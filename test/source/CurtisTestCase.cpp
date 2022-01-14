#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/SegmentBankMock.h>
#include <curtis_core/SegmentDetectorMock.h>
#include <curtis_core/GranulatorMock.h>
#include <curtis_core/BufferMock.h>

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

            segmentDetectorMockPtr_ = segmentDetectorMock_.get();
            granulatorMockPtr_ = granulatorMock_.get();

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
        }

        NiceMock<FactoryMock> factoryMock_;
        std::unique_ptr<SegmentBankMock> segmentBankMock_;
        std::unique_ptr<SegmentDetectorMock> segmentDetectorMock_;
        std::unique_ptr<GranulatorMock> granulatorMock_;

        SegmentDetectorMock* segmentDetectorMockPtr_;
        GranulatorMock* granulatorMockPtr_;

        NiceMock<BufferMock> bufferLeftMock_, bufferRightMock_;
    };

    TEST_F(UnitTest_Curtis, construction)
    {
        EXPECT_CALL(factoryMock_, createSegmentBank(_, _));
        EXPECT_CALL(factoryMock_, createSegmentDetector(48000.0f, _));
        EXPECT_CALL(factoryMock_, createGranulator(_, _));
        EXPECT_CALL(*segmentDetectorMockPtr_, addListener(_));

        Curtis(48000.0f, factoryMock_);
    }

    TEST_F(UnitTest_Curtis, setSegmentMinLength)
    {
        EXPECT_CALL(*segmentDetectorMockPtr_, setSegmentMinLength(50));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setSegmentMinLength(50);
    }

    TEST_F(UnitTest_Curtis, setRepeatMin)
    {
        EXPECT_CALL(*granulatorMockPtr_, setRepeatMin(5));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setRepeatMin(5);
    }

    TEST_F(UnitTest_Curtis, setRepeatMax)
    {
        EXPECT_CALL(*granulatorMockPtr_, setRepeatMax(5));

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
        EXPECT_CALL(*granulatorMockPtr_, setGlissonEnabled(true));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setGlissonEnabled(true);
    }

    TEST_F(UnitTest_Curtis, setStartMinSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, setStartMinSpeed(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setStartMinSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, setStartMaxSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, setStartMaxSpeed(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setStartMaxSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, setEndMinSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, setEndMinSpeed(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setEndMinSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, setEndMaxSpeed)
    {
        EXPECT_CALL(*granulatorMockPtr_, setEndMaxSpeed(1.5f));

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.setEndMaxSpeed(1.5f);
    }

    TEST_F(UnitTest_Curtis, process)
    {
        {
            InSequence seq;
            EXPECT_CALL(*segmentDetectorMockPtr_, process(_));
            EXPECT_CALL(*granulatorMockPtr_, process(_, _));
        }

        auto&& curtis = Curtis(48000.0f, factoryMock_);
        curtis.process(bufferLeftMock_, bufferRightMock_);
    }
}

