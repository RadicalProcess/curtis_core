#include <gmock/gmock.h>

#include <curtis_core/RandomRange.h>

namespace rp::curtis
{
    TEST(RandomRangeFloat, getValue)
    {
        auto randomRange = RandomRangeFloat(5.0f, 10.0f);
        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 5.0f);
            EXPECT_LT(value, 10.0f);
        }
    }

    TEST(RandomRangeFloat, getValue_same_value)
    {
        auto randomRange = RandomRangeFloat(5.0f, 5.0f);
        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_EQ(value, 5.0f);
        }
    }

    TEST(RandomRangeFloat, setMin)
    {
        auto randomRange = RandomRangeFloat(5.0f, 10.0f);
        randomRange.setMin(8.0f);

        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 8.0f);
            EXPECT_LT(value, 10.0f);
        }
    }

    TEST(RandomRangeFloat, setMax)
    {
        auto randomRange = RandomRangeFloat(5.0f, 10.0f);
        randomRange.setMax(8.0f);

        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 5.0f);
            EXPECT_LT(value, 8.0f);
        }
    }

    TEST(RandomRangeSizeT, getValue)
    {
        auto randomRange = RandomRangeSizeT(5, 10);
        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 5);
            EXPECT_LT(value, 10);
        }
    }

    TEST(RandomRangeSizeT, getValue_same_value)
    {
        auto randomRange = RandomRangeSizeT(5, 5);
        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_EQ(value, 5);
        }
    }

    TEST(RandomRangeSizeT, setMin)
    {
        auto randomRange = RandomRangeSizeT(5, 10);
        randomRange.setMin(8);

        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 8);
            EXPECT_LT(value, 10);
        }
    }

    TEST(RandomRangeSizeT, setMax)
    {
        auto randomRange = RandomRangeSizeT(5, 10);
        randomRange.setMax(8);

        for(auto i = 0; i < 100; ++i)
        {
            const auto value = randomRange.getValue();
            EXPECT_GE(value, 5);
            EXPECT_LT(value, 8);
        }
    }
}
