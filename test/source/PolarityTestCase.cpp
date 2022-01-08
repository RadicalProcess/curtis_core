#include <gtest/gtest.h>

#include <curtis_core/PolarityMock.h>

#include <curtis_core/Polarity.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Polarity : public Test
    {
    protected:
        NiceMock<PolarityListenerMock> polarityListenerMock_;
    };

    TEST_F(UnitTest_Polarity, addListener_positive_negative)
    {
        auto&& polarity = Polarity();
        polarity.addListener(&polarityListenerMock_);

        EXPECT_CALL(polarityListenerMock_, onPolarityChanged()).Times(1);

        polarity.set(0.1f, true);
        polarity.set(-0.1f, true);
    }

    TEST_F(UnitTest_Polarity, addListener_positive_negative_no_notification)
    {
        auto&& polarity = Polarity();
        polarity.addListener(&polarityListenerMock_);

        EXPECT_CALL(polarityListenerMock_, onPolarityChanged()).Times(0);

        polarity.set(0.1f, true);
        polarity.set(-0.1f, false);
    }

    TEST_F(UnitTest_Polarity, removeListener)
    {
        auto&& polarity = Polarity();
        polarity.addListener(&polarityListenerMock_);

        EXPECT_CALL(polarityListenerMock_, onPolarityChanged()).Times(0);

        polarity.set(0.1f, true);
        polarity.removeListener(&polarityListenerMock_);
        polarity.set(-0.1f, true);
    }

    TEST_F(UnitTest_Polarity, addListener_negative_positive)
    {
        auto&& polarity = Polarity();
        polarity.addListener(&polarityListenerMock_);

        EXPECT_CALL(polarityListenerMock_, onPolarityChanged()).Times(1);

        polarity.set(-0.1f, true);
        polarity.set(0.1f, true);
    }

    TEST_F(UnitTest_Polarity, addListener_multiple_callbacks)
    {
        auto&& polarity = Polarity();
        polarity.addListener(&polarityListenerMock_);

        EXPECT_CALL(polarityListenerMock_, onPolarityChanged()).Times(2);

        polarity.set(0.1f, true);
        polarity.set(-0.1f, true);
        polarity.set(0.5f, true);
    }

    TEST_F(UnitTest_Polarity, addListener_zero_uncrossed)
    {
        auto&& polarity = Polarity();
        polarity.addListener(&polarityListenerMock_);

        EXPECT_CALL(polarityListenerMock_, onPolarityChanged()).Times(1);

        polarity.set(0.1f, true);
        polarity.set(-0.1f, true);
        polarity.set(0.0f, true);
    }

    TEST_F(UnitTest_Polarity, reset)
    {
        auto&& polarity = Polarity();
        polarity.addListener(&polarityListenerMock_);

        EXPECT_CALL(polarityListenerMock_, onPolarityChanged()).Times(0);

        polarity.set(0.1f, true);
        polarity.reset(); // state becomes zero
        polarity.set(-0.1f, true);
    }
}
