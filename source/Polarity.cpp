#include "Polarity.h"

namespace rp::curtis
{
    namespace
    {
        void notify(std::set<IPolarity::Listener*>& listeners)
        {
            for(auto* listener: listeners)
                listener->onPolarityChanged();
        }
    }

    void Polarity::set(float value, bool notification)
    {
        if(state_ == Negative && value > 1.00000001E-10f)
        {
            state_ = Positive;
            if(notification)
                notify(listeners_);
        }
        else if(state_ == Positive && value < -1.00000001E-10f)
        {
            state_ = Negative;

        }
    }

    void Polarity::reset()
    {
        state_ = Negative;
    }

    void Polarity::addListener(Listener* listener)
    {
        listeners_.insert(listener);
    }

    void Polarity::removeListener(Listener* listener)
    {
        listeners_.erase(listener);
    }
}
