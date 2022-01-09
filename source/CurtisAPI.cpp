#include "CurtisAPI.h"
#include "Curtis.h"
#include "Buffer.h"

using namespace rp::curtis;

extern "C"
{
    CurtisCore* curtis_create(float sampleRate)
    {
        return reinterpret_cast<CurtisCore*>(new Curtis(sampleRate));
    }

    void curtis_destroy(CurtisCore* curtis_core)
    {
        delete reinterpret_cast<Curtis*>(curtis_core);
    }

    void curtis_segment_min_length(CurtisCore* curtis_core, float ms)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setSegmentMinLength(ms);
    }

    void curtis_segment_max_length(CurtisCore* curtis_core, float ms)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setSegmentMaxLength(ms);
    }

    void curtis_repeat_min(CurtisCore* curtis_core, uintptr_t count)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setRepeatMin(count);
    }

    void curtis_repeat_max(CurtisCore* curtis_core, uintptr_t count)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setRepeatMax(count);
    }

    void curtis_random_range(CurtisCore* curtis_core, uintptr_t range)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setRandomRange(range);
    }

    void curtis_glisson_enabled(CurtisCore* curtis_core, bool enabled)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setGlissonEnabled(enabled);
    }

    void curtis_start_min_speed(CurtisCore* curtis_core, float speed)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setStartMinSpeed(speed);
    }

    void curtis_start_max_speed(CurtisCore* curtis_core, float speed)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setStartMaxSpeed(speed);
    }

    void curtis_end_min_speed(CurtisCore* curtis_core, float speed)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setEndMinSpeed(speed);
    }

    void curtis_end_max_speed(CurtisCore* curtis_core, float speed)
    {
        reinterpret_cast<Curtis*>(curtis_core)->setEndMaxSpeed(speed);
    }

    void curtis_process(CurtisCore* curtis_core, float* buffer, uintptr_t block_size)
    {
        auto&& buf = Buffer(buffer, block_size);
        reinterpret_cast<Curtis*>(curtis_core)->process(buf);
    }
}
