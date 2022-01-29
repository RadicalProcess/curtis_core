#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/RandomRangeMock.h>

#include <curtis_core/Glisson.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Glisson : public Test
    {
    protected:
        void SetUp() override
        {
            startRandomRangeMock_ = std::make_unique<RandomRangeMock<float>>();
            startRandomRangeMockPtr_ = startRandomRangeMock_.get();
            endRandomRangeMock_ = std::make_unique<RandomRangeMock<float>>();
            endRandomRangeMockPtr_ = endRandomRangeMock_.get();

            ON_CALL(factoryMock_, createRandomRange(_, _))
                .WillByDefault(Invoke([&](float a, float b){
                    if( count_++ == 0)
                        return std::move(startRandomRangeMock_);
                    else
                        return std::move(endRandomRangeMock_);
                }));
        }

        std::unique_ptr<RandomRangeMock<float>> startRandomRangeMock_;
        RandomRangeMock<float>* startRandomRangeMockPtr_;

        std::unique_ptr<RandomRangeMock<float>> endRandomRangeMock_;
        RandomRangeMock<float>* endRandomRangeMockPtr_;

        NiceMock<FactoryMock> factoryMock_;
        size_t count_ { 0 };
    };

    TEST_F(UnitTest_Glisson, construction)
    {
        EXPECT_CALL(factoryMock_, createRandomRange(1.0f, 1.0f)).Times(2);

        auto&& unused = Glisson(factoryMock_);
    }

    TEST_F(UnitTest_Glisson, update)
    {
        EXPECT_CALL(*startRandomRangeMockPtr_, getValue());
        EXPECT_CALL(*endRandomRangeMockPtr_, getValue());

        auto&& glisson = Glisson(factoryMock_);
        glisson.update();
    }

    TEST_F(UnitTest_Glisson, getSpeedAt)
    {
        EXPECT_CALL(*startRandomRangeMockPtr_, getValue()).WillOnce(Return(1.0f));
        EXPECT_CALL(*endRandomRangeMockPtr_, getValue()).WillOnce(Return(2.0f));

        auto&& glisson = Glisson(factoryMock_);
        glisson.update();
        const auto speed = glisson.getSpeedAt(0.5f);
        EXPECT_EQ((2.0f - 1.0f) * 0.5f + 1.0f, speed);
    }

    TEST_F(UnitTest_Glisson, setGlissonEnabled)
    {
        EXPECT_CALL(*startRandomRangeMockPtr_, getValue()).WillOnce(Return(1.0f));
        EXPECT_CALL(*endRandomRangeMockPtr_, getValue()).WillOnce(Return(2.0f));

        auto&& glisson = Glisson(factoryMock_);
        glisson.update();
        glisson.setGlissonEnabled(false);
        const auto speed = glisson.getSpeedAt(0.5f);
        EXPECT_EQ(1.0f, speed);
    }

    TEST_F(UnitTest_Glisson, getStartRandomRange)
    {
        auto&& glisson = Glisson(factoryMock_);
        EXPECT_EQ(startRandomRangeMockPtr_, &glisson.getStartRandomRange());
    }

    TEST_F(UnitTest_Glisson, getEndRandomRange)
    {
        auto&& glisson = Glisson(factoryMock_);
        EXPECT_EQ(endRandomRangeMockPtr_, &glisson.getEndRandomRange());
    }
}
