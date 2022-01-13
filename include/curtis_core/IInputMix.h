#pragma once

#include <memory>

namespace rp::curtis
{
    class IInputMixParameter
    {
    public:
        virtual ~IInputMixParameter() = default;

        virtual void setMix(float mix) = 0;
    };

    class IInputMix
    {
    public:
        virtual ~IInputMix() = default;

        virtual void process(const IBuffer& left, const IBuffer& right, IBuffer& output);
    };

    using InputMixPtr = std::unique_ptr<IInputMix>;
}
