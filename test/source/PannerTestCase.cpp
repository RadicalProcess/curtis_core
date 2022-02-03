#include <gtest/gtest.h>

#include <cmath>
#include <sstream>
#include <algorithm>

#include <curtis_core/Panner.h>

namespace rp::curtis
{
    using namespace testing;
    const float halfPI { 1.57079632679 };
    const float quarterPI = halfPI / 2.0f;

    struct TestValue
    {
        float startLeft;
        float startRight;
        float endLeft;
        float endRight;
        float phase;
        float leftExpected;
        float rightExpected;
    };

    class UnitTest_Panner :public TestWithParam<TestValue> {
    };

    TEST_P(UnitTest_Panner, ParameterizedTest) {
        auto&& panner = Panner();
        auto&& param = GetParam();
        panner.setStartA(param.startLeft);
        panner.setStartB(param.startRight);
        panner.setEndA(param.endLeft);
        panner.setEndB(param.endRight);
        panner.update();

        auto [left, right, position] = panner.getGainAt(param.phase);
        EXPECT_FLOAT_EQ(param.leftExpected, left);
        EXPECT_FLOAT_EQ(param.rightExpected, right);
    }

    INSTANTIATE_TEST_SUITE_P(
            UnitTest_Panner,
            UnitTest_Panner,
            Values(
                    TestValue{0.f, 0.f, 0.f, 0.f, 0.f, std::cosf(static_cast<float>(quarterPI)), std::cosf(static_cast<float>(quarterPI))},
                    TestValue{0.f, 0.f, 0.f, 0.f, 1.f, std::cosf(static_cast<float>(quarterPI)), std::cosf(static_cast<float>(quarterPI))},
                    TestValue{-1.f, -1.f, -1.f, -1.f, 0.f, 1.f, std::cosf(static_cast<float>(halfPI))},
                    TestValue{-1.f, -1.f, -1.f, -1.f, 1.f, 1.f, std::cosf(static_cast<float>(halfPI))},
                    TestValue{1.f, 1.f, 1.f, 1.f, 0.f, std::cosf(static_cast<float>(halfPI)), 1.f},
                    TestValue{1.f, 1.f, 1.f, 1.f, 1.f, std::cosf(static_cast<float>(halfPI)), 1.f}
            ),
            [](const TestParamInfo<TestValue>& info)->std::string{
                auto param = info.param;
                auto ss = std::stringstream();
                ss << "stl" << param.startLeft << "_str" << param.startRight << "_edl" << param.endLeft << "_enr" << param.endRight << "_p" << param.phase;
                auto str = ss.str();
                std::replace( str.begin(), str.end(), '-', 'm');
                return str;
            });
}
