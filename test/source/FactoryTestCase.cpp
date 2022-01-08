#include <gmock/gmock.h>

#include <curtis_core/Factory.h>
#include <curtis_core/SegmentBank.h>
#include <curtis_core/SegmentDetector.h>
#include <curtis_core/Granulator.h>

namespace rp::curtis
{
    using namespace testing;

    TEST(UnitTest_Factory, createSegmentBank)
    {
        auto&& segmentBank = Factory().createSegmentBank(3);

        ASSERT_THAT(segmentBank, NotNull());
        EXPECT_THAT(segmentBank.get(), WhenDynamicCastTo<SegmentBank*>(NotNull()));
    }

    TEST(UnitTest_Factory, createSegmentDetector)
    {
        auto&& segmentDetector = Factory().createSegmentDetector(48000.f);

        ASSERT_THAT(segmentDetector, NotNull());
        EXPECT_THAT(segmentDetector.get(), WhenDynamicCastTo<SegmentDetector*>(NotNull()));
    }

    TEST(UnitTest_Factory, createGranulator)
    {
        auto&& granulator = Factory().createGranulator();

        ASSERT_THAT(granulator, NotNull());
        EXPECT_THAT(granulator.get(), WhenDynamicCastTo<Granulator*>(NotNull()));
    }
}
