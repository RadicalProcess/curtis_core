#include <gtest/gtest.h>

#include <cmath>

#include <curtis_core/Panner.h>
#include <curtis_core/Buffer.h>

namespace rp::curtis
{
    TEST(UnitTest_Panner, process )
    {
        auto&& panner = Panner();
        auto&& buffer = Buffer(1);
        auto&& rightBuffer = Buffer(1);

        buffer.push(1.0f);
        panner.process(buffer, rightBuffer);

        EXPECT_EQ(std::cosf(0.5* static_cast<float>(M_PI_2)), buffer.getReadPtr()[0]);
        EXPECT_EQ(std::cosf(0.5* static_cast<float>(M_PI_2)), rightBuffer.getReadPtr()[0]);
    }

    TEST(UnitTest_Panner, hard_left_process )
    {
        auto&& panner = Panner();
        auto&& buffer = Buffer(1);
        auto&& rightBuffer = Buffer(1);

        buffer.push(1.0f);
        panner.set(-1.0f);
        panner.process(buffer, rightBuffer);

        EXPECT_EQ(1.0f, buffer.getReadPtr()[0]);
    }

    TEST(UnitTest_Panner, hard_right_process )
    {
        auto&& panner = Panner();
        auto&& buffer = Buffer(1);
        auto&& rightBuffer = Buffer(1);

        buffer.push(1.0f);
        panner.set(1.0f);
        panner.process(buffer, rightBuffer);

        EXPECT_EQ(1.0f, rightBuffer.getReadPtr()[0]);
    }
}
