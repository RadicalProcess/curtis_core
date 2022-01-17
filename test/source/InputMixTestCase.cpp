#include <gtest/gtest.h>

#include <curtis_core//InputMix.h>

namespace rp::curtis
{
    using namespace testing;

    TEST(UnitTest_InputMix, construction)
    {
        auto&& inputMix = InputMix();
        auto&& left = Buffer(1);
        auto&& right = Buffer(1);
        left.push(1.0f);
        right.push(0.0f);

        inputMix.process(left, right);

        EXPECT_EQ(1.0f, left.getReadPtr()[0]);
        EXPECT_EQ(0.0f, right.getReadPtr()[0]);
    }

    TEST(UnitTest_InputMix, setMix)
    {
        auto&& inputMix = InputMix();
        auto&& left = Buffer(1);
        auto&& right = Buffer(1);
        left.push(1.0f);
        right.push(0.0f);
        inputMix.setMix(0.0f);
        inputMix.process(left, right);

        EXPECT_EQ(0.5f, left.getReadPtr()[0]);
        EXPECT_EQ(0.5f, right.getReadPtr()[0]);
    }

    TEST(UnitTest_InputMix, hard_right)
    {
        auto&& inputMix = InputMix();
        auto&& left = Buffer(1);
        auto&& right = Buffer(1);
        left.push(1.0f);
        right.push(0.0f);
        inputMix.setMix(1.0f);
        inputMix.process(left, right);

        EXPECT_EQ(0.0f, left.getReadPtr()[0]);
        EXPECT_EQ(1.0f, right.getReadPtr()[0]);
    }
}
