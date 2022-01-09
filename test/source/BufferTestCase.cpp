#include <gmock/gmock.h>

#include <curtis_core/Buffer.h>

namespace rp::curtis
{
    TEST(UnitTest_Buffer, construction)
    {
        auto&& buffer = Buffer();
        EXPECT_EQ(0, buffer.size());
        EXPECT_FALSE(buffer.owned());
    }

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

    TEST(UnitTest_Buffer, append)
    {
        auto&& buffer1 = Buffer(3);
        auto&& vector = std::vector<float>{1.0, 2.0, 3.0};
        auto&& buffer2 = Buffer(vector.data(), vector.size());

        buffer1.append(buffer2);

        EXPECT_EQ(3, buffer1.size());
    }

    TEST(UnitTest_Buffer, append_twice)
    {
        auto&& buffer1 = Buffer(3);
        auto&& vector = std::vector<float>{1.0};
        auto&& buffer2 = Buffer(vector.data(), vector.size());

        buffer1.append(buffer2);
        EXPECT_EQ(1, buffer1.size());

        buffer1.append(buffer2);
        EXPECT_EQ(2, buffer1.size());
    }

    TEST(UnitTest_Buffer, clear)
    {
        auto&& buffer1 = Buffer(3);
        auto&& vector = std::vector<float>{1.0, 2.0, 3.0};
        auto&& buffer2 = Buffer(vector.data(), vector.size());

        buffer1.append(buffer2);

        EXPECT_EQ(3, buffer1.size());

        buffer1.clear();

        EXPECT_EQ(0, buffer1.size());
    }


    TEST(UnitTest_Buffer, append_throw)
    {
        auto&& buffer1 = Buffer(3);
        auto&& vector = std::vector<float>{1.0, 2.0, 3.0, 4.0};
        auto&& buffer2 = Buffer(vector.data(), vector.size());

        EXPECT_THROW(buffer1.append(buffer2), std::out_of_range);
    }

    TEST(UnitTest_Buffer, push)
    {
        auto&& buffer = Buffer(3);
        buffer.push(1.0f);
        buffer.push(2.0f);
        buffer.push(3.0f);

        EXPECT_EQ(1.0f, buffer.get()[0]);
        EXPECT_EQ(2.0f, buffer.get()[1]);
        EXPECT_EQ(3.0f, buffer.get()[2]);

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
}
