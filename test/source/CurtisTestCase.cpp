#include <gmock/gmock.h>

#include <curtis_core/FactoryMock.h>

#include <curtis_core/Curtis.h>

namespace rp::curtis
{
    using namespace testing;

    class UnitTest_Curtis : public Test
    {
    protected:

        NiceMock<FactoryMock> factoryMock_;
    };

    TEST_F(UnitTest_Curtis, construction)
    {
        EXPECT_CALL(factoryMock_, createSegmentBank(_));
        EXPECT_CALL(factoryMock_, createSegmentDetector(48000.0f));
        EXPECT_CALL(factoryMock_, createGranulator());

        Curtis(48000.0f, factoryMock_);
    }
}

