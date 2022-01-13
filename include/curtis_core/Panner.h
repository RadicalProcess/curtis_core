#pragma once

#include "IPanner.h"

namespace rp::curtis
{
    class Panner : public IPanner
    {
    public:
        Panner();

        ~Panner() = default;

        void set(float position) override;

        void process(const IBuffer& inlet, IBuffer& left, IBuffer& right) override;

    private:
        float position_;
    };
}
