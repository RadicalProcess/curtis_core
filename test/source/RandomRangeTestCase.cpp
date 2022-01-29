#include <gmock/gmock.h>

#include <curtis_core/RandomRange.h>

namespace rp::curtis
{
    TEST(RandomRange, getValue)
    {
        auto randomRange = RandomRange(5.0f, 10.0f);
        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 5.0f);
            EXPECT_LT(value, 10.0f);
        }
    }

    TEST(RandomRange, getValue_same_value)
    {
        auto randomRange = RandomRange(5.0f, 5.0f);
        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_EQ(value, 5.0f);
        }
    }

    TEST(RandomRange, setA)
    {
        auto randomRange = RandomRange(5.0f, 10.0f);
        randomRange.setA(8.0f);

        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 8.0f);
            EXPECT_LT(value, 10.0f);
        }
    }

    TEST(RandomRange, setB)
    {
        auto randomRange = RandomRange(5.0f, 10.0f);
        randomRange.setB(8.0f);

        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 5.0f);
            EXPECT_LT(value, 8.0f);
        }
    }
}
