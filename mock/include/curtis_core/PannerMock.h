#include <gmock/gmock.h>

#include <curtis_core/IPanner.h>

namespace rp::curtis {

    class PannerMock : public IPanner {
    public:
        MOCK_METHOD(void, update, (), (override));
        MOCK_METHOD(void, setStartLeft, (float position), (override));
        MOCK_METHOD(void, setStartRight, (float position), (override));
        MOCK_METHOD(void, setEndLeft, (float position), (override));
        MOCK_METHOD(void, setEndRight, (float position), (override));
        MOCK_METHOD((std::pair<float, float>), getGainAt, (float phase), (const, override));
    };

}  // namespace rp::curtis
