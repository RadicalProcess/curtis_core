#include <gmock/gmock.h>

#include <curtis_core/IPanner.h>

namespace rp::curtis {

    class PannerMock : public IPanner {
    public:
        MOCK_METHOD(void, update, (), (override));
        MOCK_METHOD(void, setStartA, (float position), (override));
        MOCK_METHOD(void, setStartB, (float position), (override));
        MOCK_METHOD(void, setEndA, (float position), (override));
        MOCK_METHOD(void, setEndB, (float position), (override));
        MOCK_METHOD((std::tuple<float, float, float>), getGainAt, (float phase), (const, override));
    };

}  // namespace rp::curtis
