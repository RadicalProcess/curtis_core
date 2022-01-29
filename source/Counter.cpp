#include "Counter.h"

namespace rp::curtis
{
    Counter::Counter(const IFactory& factory)
    : maxCount_(0)
    , remaining_(0)
    {}

    void Counter::setMaxCount(size_t count)
    {
        maxCount_ = count;

    }

    bool Counter::count()
    {
        if(remaining_ == 0)
        {
            remaining_ = maxCount_;
            return true;
        }
        remaining_--;
        return false;
    }
}
