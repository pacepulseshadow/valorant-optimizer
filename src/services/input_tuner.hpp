#pragma once

#include "services/config_service.hpp"

namespace vo::services {

class InputTuner {
public:
    explicit InputTuner(ConfigService& cfg);

    bool apply();
    bool restore();

private:
    bool disable_mouse_acceleration();
    bool set_usb_polling_rate(int hz);

    ConfigService& m_cfg;
    bool m_applied = false;
};

} // namespace vo::services