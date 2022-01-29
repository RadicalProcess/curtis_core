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

        std::pair<float, float> getGainAt(float phase) const override;

    private:
        float startLeft_;
        float startRight_;
        float endLeft_;
        float endRight_;

        float start_;
        float end_;
    };
}
