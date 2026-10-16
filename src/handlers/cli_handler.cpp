#include "handlers/cli_handler.hpp"
#include "utils/logger.hpp"

#include <iostream>
#include <string_view>

namespace vo::handlers {

CliHandler::CliHandler(services::ConfigService& cfg, ProfileHandler& profiles)
    : m_cfg(cfg), m_profiles(profiles) {}

int CliHandler::cmd_apply(const std::string& profile) {
    return m_profiles.apply(profile) ? 0 : 1;
}

int CliHandler::cmd_restore() {
    return m_profiles.restore_all() ? 0 : 1;
}

int CliHandler::cmd_status() {
    std::cout << "valorant-optimizer: active profile = "
              << m_cfg.get_string("optimizer.profile", "competitive") << '\n';
    return 0;
}

int CliHandler::cmd_help() {
    std::cout << "usage: valorant-optimizer <command> [args]\n"
                 "  apply <profile>   apply an optimization profile\n"
                 "  restore           restore all previous settings\n"
                 "  status            print current state\n"
                 "  help              show this message\n";
    return 0;
}

int CliHandler::dispatch(int argc, char** argv) {
    if (argc < 2) return cmd_status();
    std::string_view cmd{argv[1]};

    if (cmd == "apply") {
        std::string profile = (argc >= 3) ? argv[2] : "competitive";
        return cmd_apply(profile);
    }
    if (cmd == "restore") return cmd_restore();
    if (cmd == "status")  return cmd_status();
    if (cmd == "help")    return cmd_help();

    VO_LOG_WARN("unknown command: {}", cmd);
    return cmd_help();
}

} // namespace vo::handlers