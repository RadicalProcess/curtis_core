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

    TEST(UnitTest_Buffer, clean)
    {
        auto&& buffer1 = Buffer(3);
        auto&& vector = std::vector<float>{1.0, 2.0, 3.0};
        auto&& buffer2 = Buffer(vector.data(), vector.size());

        buffer1.append(buffer2);

        EXPECT_EQ(3, buffer1.size());

        buffer1.clean();

        EXPECT_EQ(0, buffer1.size());
    }


    TEST(UnitTest_Buffer, append_throw)
    {
        auto&& buffer1 = Buffer(3);
        auto&& vector = std::vector<float>{1.0, 2.0, 3.0, 4.0};
        auto&& buffer2 = Buffer(vector.data(), vector.size());

        EXPECT_THROW(buffer1.append(buffer2), std::out_of_range);
    }
}
