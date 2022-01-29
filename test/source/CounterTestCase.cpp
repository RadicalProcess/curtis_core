#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>
#include <curtis_core/RandomRangeMock.h>

#include <curtis_core/Counter.h>

namespace rp::curtis
{
    using namespace testing;

    TEST(UnitTest_Counter, construction)
    {
        auto&& counter = Counter();

        EXPECT_TRUE(counter.count());
        EXPECT_TRUE(counter.count());
    }

    TEST(UnitTest_Counter, setMaxCount)
    {
        auto&& counter = Counter();
        counter.setMaxCount(1);
        EXPECT_TRUE(counter.count());
        EXPECT_FALSE(counter.count());
        EXPECT_TRUE(counter.count());
    }

    TEST(UnitTest_Counter, setMaxCount_two)
    {
        auto&& counter = Counter();
        counter.setMaxCount(2);
        EXPECT_TRUE(counter.count());
        EXPECT_FALSE(counter.count());
        EXPECT_FALSE(counter.count());
        EXPECT_TRUE(counter.count());
    }
}
