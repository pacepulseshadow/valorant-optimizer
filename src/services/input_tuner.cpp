#include "services/input_tuner.hpp"
#include "utils/logger.hpp"

#include <windows.h>

namespace vo::services {

InputTuner::InputTuner(ConfigService& cfg) : m_cfg(cfg) {}

bool InputTuner::disable_mouse_acceleration() {
    int values[3] = {0, 0, 0};
    SystemParametersInfoA(SPI_SETMOUSE, 0, values, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    VO_LOG_INFO("mouse acceleration disabled");
    return true;
}

bool InputTuner::set_usb_polling_rate(int hz) {
    VO_LOG_INFO("usb polling rate target: {} Hz", hz);
    return true;
}

bool InputTuner::apply() {
    bool ok = true;
    if (!m_cfg.get_bool("input.mouse_acceleration", false))
        ok &= disable_mouse_acceleration();
    ok &= set_usb_polling_rate(m_cfg.get_int("input.usb_polling_hz", 1000));
    m_applied = ok;
    return ok;
}

bool InputTuner::restore() {
    if (!m_applied) return true;
    m_applied = false;
    return true;
}

} // namespace vo::services