#pragma once

#include <set>

#include "IPolarity.h"

namespace rp::curtis
{
    class Polarity : public IPolarity
    {
    public:
        ~Polarity() override = default;

        void set(float value, bool notification) override;

        void reset() override;

        void addListener(Listener* listener) override;

        void removeListener(Listener* listener) override;

    private:

        enum State{
            Positive,
            Negative,
        };

        std::set<Listener*> listeners_;
        State state_ { Negative };
    };
}
