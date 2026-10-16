#pragma once

#include "services/config_service.hpp"

namespace vo::services {

class GraphicsTuner {
public:
    explicit GraphicsTuner(ConfigService& cfg);

    bool apply();
    bool restore();

private:
    bool disable_fullscreen_optimizations();
    bool set_gpu_scheduling_priority(const std::string& priority);

    ConfigService& m_cfg;
    bool m_applied = false;
};

} // namespace vo::services