#pragma once
#include <cstdlib>

namespace rp::curtis
{
    class Curtis
    {
    public:
        Curtis(float sampleRate);

        void setSegmentMinLength(float ms);
        void setSegmentMaxLength(float ms);

        void setRepeatMin(size_t count);
        void setRepeatMax(size_t count);

        void setRandomRange(size_t range);

        void setGlissonEnabled(bool enabled);
        void setStartMinSpeed(float speed);
        void setStartMaxSpeed(float speed);
        void setEndMinSpeed(float speed);
        void setEndMaxSpeed(float speed);
    };
}
