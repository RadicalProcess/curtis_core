#include "Counter.h"

namespace rp::curtis
{
    Counter::Counter(const IFactory& factory)
    : repeatRandomRange_(factory.createRandomRangeSizeT(0, 0))
    , remaining_(0)
    {}

    IRandomRange<size_t>& Counter::getRandomRange()
    {
        return *repeatRandomRange_;
    }

    bool Counter::count()
    {
        if(remaining_ == 0)
        {
            remaining_ = repeatRandomRange_->getValue();
            return true;
        }
        remaining_--;
        return false;
    }
}
