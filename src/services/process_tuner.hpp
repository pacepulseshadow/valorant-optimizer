#pragma once

#include "services/config_service.hpp"

#include <string>

namespace vo::services {

class ProcessTuner {
public:
    explicit ProcessTuner(ConfigService& cfg);

    bool apply_to(const std::string& process_name);
    bool restore();

private:
    bool set_priority(const std::string& priority);
    bool set_affinity(unsigned long mask);

    ConfigService& m_cfg;
    unsigned long  m_original_affinity = 0;
    bool           m_applied = false;
};

} // namespace vo::services