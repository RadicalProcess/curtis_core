#include <gtest/gtest.h>

#include <curtis_core/Randomizer.h>

namespace rp::curtis
{
    using namespace testing;

    TEST(UnitTest_Randomizer, getValue)
    {
        auto&& randomizer = Randomizer();
        EXPECT_EQ(0, randomizer.getValue());
    }

    TEST(UnitTest_Randomizer, setRange)
    {
        auto&& randomizer = Randomizer();
        randomizer.setRange(5);

        for(auto i = 0; i < 1000; i++)
        {
            const auto value = randomizer.getValue();
            EXPECT_GE(value, 0);
            EXPECT_LT(value, 5);
        }
    }
}
