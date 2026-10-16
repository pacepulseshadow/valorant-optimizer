#pragma once

#include "services/config_service.hpp"
#include "handlers/profile_handler.hpp"

namespace vo::handlers {

class CliHandler {
public:
    CliHandler(services::ConfigService& cfg, ProfileHandler& profiles);

    int dispatch(int argc, char** argv);

private:
    int cmd_apply(const std::string& profile);
    int cmd_restore();
    int cmd_status();
    int cmd_help();

    services::ConfigService& m_cfg;
    ProfileHandler&          m_profiles;
};

} // namespace vo::handlers