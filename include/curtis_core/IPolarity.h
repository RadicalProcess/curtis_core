#pragma once

#include <memory>

namespace rp::curtis
{
    class IPolarity
    {
    public:
        class Listener
        {
        public:
            virtual ~Listener() = default;

            virtual void onPolarityChanged() = 0;
        };

    public:
        virtual ~IPolarity() = default;

        virtual void set(float value, bool notification) = 0;

        virtual void reset() = 0;

        virtual void addListener(Listener* listener) = 0;

        virtual void removeListener(Listener* listener) = 0;
    };

    using PolarityPtr = std::unique_ptr<IPolarity>;
}
