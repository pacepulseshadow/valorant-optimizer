#pragma once

#include "services/config_service.hpp"
#include "handlers/cli_handler.hpp"
#include "handlers/profile_handler.hpp"

#include <string>
#include <vector>

namespace vo::core {

class Application {
public:
    Application();
    ~Application();

    int run(int argc, char** argv);

private:
    void load_defaults();
    void apply_startup_profile();

    services::ConfigService m_config;
    handlers::CliHandler     m_cli;
    handlers::ProfileHandler m_profiles;
    bool                     m_initialized = false;
};

} // namespace vo::core