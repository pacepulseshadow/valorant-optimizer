#pragma once

#include "services/config_service.hpp"
#include "services/network_tuner.hpp"
#include "services/graphics_tuner.hpp"
#include "services/process_tuner.hpp"
#include "services/input_tuner.hpp"

#include <string>

namespace vo::handlers {

class ProfileHandler {
public:
    explicit ProfileHandler(services::ConfigService& cfg);

    bool apply(const std::string& profile_name);
    bool restore_all();

private:
    services::ConfigService&  m_cfg;
    services::NetworkTuner    m_network;
    services::GraphicsTuner   m_graphics;
    services::ProcessTuner    m_process;
    services::InputTuner      m_input;
};

} // namespace vo::handlers