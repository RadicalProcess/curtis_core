#include "IDensity.h"

namespace rp::curtis
{
    class Density : public IDensity
    {
    public:
        Density();

        ~Density() override = default;

        void set(int percentage) override;

        void roll() override;

        bool get() const override;

    private:
        int percentage_;
        bool state_;
    };
}
