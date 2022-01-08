#include "Factory.h"
#include "SegmentBank.h"
#include "SegmentDetector.h"
#include "Granulator.h"

namespace rp::curtis
{
    SegmentBankPtr Factory::createSegmentBank(size_t numCaches) const
    {
        return std::make_unique<SegmentBank>(numCaches);
    }

    SegmentDetectorPtr Factory::createSegmentDetector(float sampleRate) const
    {
        return std::make_unique<SegmentDetector>(sampleRate);
    }

    GranulatorPtr Factory::createGranulator() const
    {
        return std::make_unique<Granulator>();
    }
}
