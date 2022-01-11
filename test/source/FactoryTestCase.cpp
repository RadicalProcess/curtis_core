#include <gmock/gmock.h>

#include <curtis_core/SegmentBankMock.h>

#include <curtis_core/Factory.h>
#include <curtis_core/SegmentBank.h>
#include <curtis_core/SegmentDetector.h>
#include <curtis_core/Granulator.h>
#include <curtis_core/RandomRange.h>
#include <curtis_core/Glisson.h>
#include <curtis_core/Randomizer.h>
#include <curtis_core/Counter.h>

namespace rp::curtis
{
    using namespace testing;

    TEST(UnitTest_Factory, createSegmentBank)
    {
        auto&& segmentBank = Factory().createSegmentBank(3, 0);

        ASSERT_THAT(segmentBank, NotNull());
        EXPECT_THAT(segmentBank.get(), WhenDynamicCastTo<SegmentBank*>(NotNull()));
    }

    TEST(UnitTest_Factory, createSegmentDetector)
    {
        auto&& segmentDetector = Factory().createSegmentDetector(48000.f, 0);

        ASSERT_THAT(segmentDetector, NotNull());
        EXPECT_THAT(segmentDetector.get(), WhenDynamicCastTo<SegmentDetector*>(NotNull()));
    }

    TEST(UnitTest_Factory, createGranulator)
    {
        auto&& segmentBank = SegmentBankMock();
        auto&& granulator = Factory().createGranulator(segmentBank, 0);

        ASSERT_THAT(granulator, NotNull());
        EXPECT_THAT(granulator.get(), WhenDynamicCastTo<Granulator*>(NotNull()));
    }

    TEST(UnitTest_Factory, createBuffer_capacity)
    {
        auto&& buffer = Factory().createBuffer(10, false);

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

    TEST(UnitTest_Factory, createRandomRangeFloat)
    {
        auto&& factory = Factory();
        auto randomRange = factory.createRandomRangeFloat(5.0f, 10.0f);

        ASSERT_THAT(randomRange, NotNull());
        EXPECT_THAT(randomRange.get(), WhenDynamicCastTo<RandomRangeFloat*>(NotNull()));
    }

    TEST(UnitTest_Factory, createRandomRangeSizeT)
    {
        auto&& factory = Factory();
        auto randomRange = factory.createRandomRangeSizeT(5.0f, 10.0f);

        ASSERT_THAT(randomRange, NotNull());
        EXPECT_THAT(randomRange.get(), WhenDynamicCastTo<RandomRangeSizeT*>(NotNull()));
    }

    TEST(UnitTest_Factory, createGlisson)
    {
        auto&& factory = Factory();
        auto glisson = factory.createGlisson();

        ASSERT_THAT(glisson, NotNull());
        EXPECT_THAT(glisson.get(), WhenDynamicCastTo<Glisson*>(NotNull()));
    }

    TEST(UnitTest_Factory, createRandomizer)
    {
        auto&& factory = Factory();
        auto randomizer = factory.createRandomizer();

        ASSERT_THAT(randomizer, NotNull());
        EXPECT_THAT(randomizer.get(), WhenDynamicCastTo<Randomizer*>(NotNull()));
    }

    TEST(UnitTest_Factory, createCounter)
    {
        auto&& factory = Factory();
        auto counter = factory.createCounter();

        ASSERT_THAT(counter, NotNull());
        EXPECT_THAT(counter.get(), WhenDynamicCastTo<Counter*>(NotNull()));
    }
}
