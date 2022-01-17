#pragma once

#include <gmock/gmock.h>

#include <curtis_core/IInputMix.h>

namespace rp::curtis {

    class InputMixMock : public IInputMix {
    public:
        MOCK_METHOD(void, setMix, (float mix), (override));
        MOCK_METHOD(void, process, (IBuffer& leftBuffer, IBuffer& rightBuffer), (override));

    };
}
