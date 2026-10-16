#include "services/network_tuner.hpp"
#include "utils/logger.hpp"
#include "utils/registry_utils.hpp"

#include <windows.h>

namespace vo::services {

NetworkTuner::NetworkTuner(ConfigService& cfg) : m_cfg(cfg) {}

bool NetworkTuner::set_tcp_nodelay(bool enabled) {
    const std::string path = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces";
    VO_LOG_INFO("tcp_nodelay -> {}", enabled);
    return utils::registry::set_dword(HKEY_LOCAL_MACHINE, path, "TcpAckFrequency", enabled ? 1 : 2);
}

bool NetworkTuner::set_nagle(bool enabled) {
    VO_LOG_INFO("nagle -> {}", enabled);
    return true;
}

bool NetworkTuner::flush_dns_cache() {
    return system("ipconfig /flushdns > NUL") == 0;
}

bool NetworkTuner::apply() {
    const bool nodelay = m_cfg.get_bool("network.tcp_nodelay", true);
    const bool nagle   = m_cfg.get_bool("network.nagle_algorithm", false);

    bool ok = true;
    ok &= set_tcp_nodelay(nodelay);
    ok &= set_nagle(nagle);
    ok &= flush_dns_cache();

    m_applied = ok;
    return ok;
}

bool NetworkTuner::restore() {
    if (!m_applied) return true;
    set_tcp_nodelay(false);
    set_nagle(true);
    m_applied = false;
    return true;
}

} // namespace vo::services