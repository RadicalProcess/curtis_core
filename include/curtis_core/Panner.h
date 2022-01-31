#pragma once

#include "IPanner.h"

namespace rp::curtis
{
    class Panner : public IPanner
    {
    public:
        Panner();

        ~Panner() = default;

        void setStartA(float position) override;

        void setStartB(float position) override;

        void setEndA(float position) override;

        void setEndB(float position) override;

        void update() override;

        std::tuple<float, float, float> getGainAt(float phase) const override;

    private:
        float startA_;
        float startB_;
        float endA_;
        float endB_;

        float start_;
        float end_;
    };
}
