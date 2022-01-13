#include <gmock/gmock.h>

#include <curtis_core/Buffer.h>

namespace rp::curtis
{
    TEST(UnitTest_Buffer, construction_unowned)
    {
        auto&& buffer = Buffer(nullptr, 10);
        EXPECT_EQ(10, buffer.size());
        EXPECT_FALSE(buffer.owned());
    }

    TEST(UnitTest_Buffer, consrutcion_owned)
    {
        auto&& buffer = Buffer(10);
        EXPECT_EQ(0, buffer.size());
        EXPECT_TRUE(buffer.owned());
    }

    TEST(UnitTest_Buffer, consrutcion_owned_fill)
    {
        auto&& buffer = Buffer(10, true);
        EXPECT_EQ(1, buffer.size());
        EXPECT_TRUE(buffer.owned());

        auto* ptr = buffer.getReadPtr();
        EXPECT_EQ(0.0f, *ptr);
    }

    TEST(UnitTest_Buffer, push)
    {
        auto&& buffer = Buffer(3);
        buffer.push(1.0f);
        buffer.push(2.0f);
        buffer.push(3.0f);

        EXPECT_EQ(1.0f, buffer.getReadPtr()[0]);
        EXPECT_EQ(2.0f, buffer.getReadPtr()[1]);
        EXPECT_EQ(3.0f, buffer.getReadPtr()[2]);

        EXPECT_EQ(3, buffer.size());
    }

    TEST(UnitTest_Buffer, push_throw)
    {
        auto&& buffer = Buffer(2);
        buffer.push(1.0f);
        buffer.push(2.0f);

        EXPECT_EQ(2, buffer.size());
        EXPECT_THROW(buffer.push(3.0f), std::out_of_range);
    }

    TEST(UnitTest_Buffer, copyFrom)
    {
        auto&& buffer1 = Buffer(2);
        buffer1.push(11.f);
        buffer1.push(15.f);

        auto&& buffer2 = Buffer(2);
        buffer2.copyFrom(buffer1);

        EXPECT_EQ(11.f, buffer2.getReadPtr()[0]);
        EXPECT_EQ(15.f, buffer2.getReadPtr()[1]);
    }

    TEST(UnitTest_Buffer, copyFrom_throw)
    {
        auto&& buffer1 = Buffer(2);
        buffer1.push(11.f);
        buffer1.push(15.f);

        auto&& buffer2 = Buffer(1);
        EXPECT_THROW(buffer2.copyFrom(buffer1), std::out_of_range);
    }

    TEST(UnitTest_Buffer, full)
    {
        auto&& buffer = Buffer(2);
        buffer.push(11.f);
        buffer.push(15.f);

        EXPECT_TRUE(buffer.full());
    }

    TEST(UnitTest_Buffer, applyGain)
    {
        auto&& buffer = Buffer(2);
        buffer.push(1.f);
        buffer.push(1.f);

        buffer.applyGain(0.5f);

        EXPECT_EQ(1.0f * 0.5f, buffer.getReadPtr()[0]);
        EXPECT_EQ(1.0f * 0.5f, buffer.getReadPtr()[1]);
    }

}
