#pragma once

#include "IPanner.h"

namespace rp::curtis
{
    class Panner : public IPanner
    {
    public:
        Panner();

        ~Panner() = default;

        void setStartLeft(float position) override;

        void setStartRight(float position) override;

        void setEndLeft(float position) override;

        void setEndRight(float position) override;

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
