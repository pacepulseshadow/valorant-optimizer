#include "core/application.hpp"
#include "utils/logger.hpp"

namespace vo::core {

Application::Application()
    : m_config("config/default.toml"),
      m_cli(m_config, m_profiles),
      m_profiles(m_config) {}

Application::~Application() = default;

void Application::load_defaults() {
    if (!m_config.load()) {
        VO_LOG_WARN("config not found, using built-in defaults");
        m_config.use_builtin_defaults();
    }
    m_initialized = true;
}

void Application::apply_startup_profile() {
    const auto profile = m_config.get_string("optimizer.profile", "competitive");
    VO_LOG_INFO("applying startup profile: {}", profile);
    m_profiles.apply(profile);
}

int Application::run(int argc, char** argv) {
    load_defaults();
    if (!m_initialized) {
        VO_LOG_ERROR("application failed to initialize");
        return 2;
    }

    if (m_config.get_bool("optimizer.auto_apply_on_launch", true)) {
        apply_startup_profile();
    }

    return m_cli.dispatch(argc, argv);
}

} // namespace vo::core