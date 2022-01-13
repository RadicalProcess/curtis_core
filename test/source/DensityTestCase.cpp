#include <gtest/gtest.h>

#include <curtis_core/Density.h>

namespace rp::curtis
{
    TEST(UnitTest_Density, construction)
    {
        auto density = Density();
        EXPECT_TRUE(density.get());
    }

    TEST(UnitTest_Density, roll)
    {
        auto density = Density();
        density.roll();
        EXPECT_TRUE(density.get());
    }

    TEST(UnitTest_Density, set)
    {
        auto density = Density();
        density.set(0);
        density.roll();
        EXPECT_FALSE(density.get());
    }
}
