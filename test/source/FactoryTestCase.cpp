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

    TEST(UnitTest_Factory, createBuffer)
    {
        auto&& buffer = Factory().createBuffer(10);

        ASSERT_THAT(buffer, NotNull());
        EXPECT_THAT(buffer.get(), WhenDynamicCastTo<Buffer*>(NotNull()));
    }

    TEST(UnitTest_Factory, createBuffer_unowned)
    {
        auto&& vector = std::vector<float>(10);
        auto&& buffer = Factory().createBuffer(vector.data(), vector.size());

        ASSERT_THAT(buffer, NotNull());
        EXPECT_THAT(buffer.get(), WhenDynamicCastTo<Buffer*>(NotNull()));
    }
}
