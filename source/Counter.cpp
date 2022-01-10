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

    void Counter::count(const std::function<void()>& onCountEnded)
    {
        if(remaining_ == 0)
        {
            onCountEnded();
            remaining_ = repeatRandomRange_->getValue();
        }
        else
            remaining_--;
    }
}
