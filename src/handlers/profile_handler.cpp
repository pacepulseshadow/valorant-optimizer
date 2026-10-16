#include "handlers/profile_handler.hpp"
#include "utils/logger.hpp"

namespace vo::handlers {

ProfileHandler::ProfileHandler(services::ConfigService& cfg)
    : m_cfg(cfg),
      m_network(cfg),
      m_graphics(cfg),
      m_process(cfg),
      m_input(cfg) {}

bool ProfileHandler::apply(const std::string& profile_name) {
    VO_LOG_INFO("applying profile: {}", profile_name);
    m_cfg.set("optimizer.profile", profile_name);

    bool ok = true;
    ok &= m_network.apply();
    ok &= m_graphics.apply();
    ok &= m_input.apply();
    ok &= m_process.apply_to("VALORANT-Win64-Shipping.exe");

    if (!ok) VO_LOG_WARN("profile {} applied with warnings", profile_name);
    return ok;
}

bool ProfileHandler::restore_all() {
    VO_LOG_INFO("restoring all tuners");
    bool ok = true;
    ok &= m_network.restore();
    ok &= m_graphics.restore();
    ok &= m_input.restore();
    ok &= m_process.restore();
    return ok;
}

} // namespace vo::handlers