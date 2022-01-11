#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/RandomRangeMock.h>

#include <curtis_core/Counter.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Counter : public Test
    {
    protected:
        void SetUp() override
        {
            randomRangeMock_ = std::make_unique<NiceMock<RandomRangeMock<size_t>>>();
            randomRangeMockPtr_ = randomRangeMock_.get();

            ON_CALL(factoryMock_, createRandomRangeSizeT(_, _))
                .WillByDefault(Return(ByMove(std::move(randomRangeMock_))));
        }

        NiceMock<FactoryMock> factoryMock_;
        std::unique_ptr<RandomRangeMock<size_t>> randomRangeMock_;
        RandomRangeMock<size_t>* randomRangeMockPtr_;
    };

    TEST_F(UnitTest_Counter, construction)
    {
        EXPECT_CALL(factoryMock_, createRandomRangeSizeT(_, _));
        auto&& unused = Counter(factoryMock_);
    }

    TEST_F(UnitTest_Counter, getRandomRange)
    {
        EXPECT_CALL(factoryMock_, createRandomRangeSizeT(_, _));
        auto&& counter = Counter(factoryMock_);
        EXPECT_EQ(randomRangeMockPtr_, &counter.getRandomRange());
    }

    TEST_F(UnitTest_Counter, count)
    {
        auto&& counter = Counter(factoryMock_);

        EXPECT_CALL(*randomRangeMockPtr_, getValue());
        counter.count();
    }

    TEST_F(UnitTest_Counter, invocation)
    {
        auto&& counter = Counter(factoryMock_);

        EXPECT_TRUE(counter.count());
    }

    TEST_F(UnitTest_Counter, count_update_remaining)
    {
        auto&& counter = Counter(factoryMock_);

        EXPECT_CALL(*randomRangeMockPtr_, getValue())
            . Times(1)
            . WillOnce(Return(1));

        counter.count();
        counter.count();
    }

}
