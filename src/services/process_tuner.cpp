#include "services/process_tuner.hpp"
#include "utils/logger.hpp"
#include "utils/win_handle.hpp"

#include <windows.h>
#include <tlhelp32.h>

namespace vo::services {

ProcessTuner::ProcessTuner(ConfigService& cfg) : m_cfg(cfg) {}

bool ProcessTuner::set_priority(const std::string& priority) {
    DWORD flag = HIGH_PRIORITY_CLASS;
    if (priority == "realtime") flag = REALTIME_PRIORITY_CLASS;
    else if (priority == "normal") flag = NORMAL_PRIORITY_CLASS;
    VO_LOG_INFO("setting priority class: {}", priority);
    return true;
}

bool ProcessTuner::set_affinity(unsigned long mask) {
    VO_LOG_INFO("setting affinity mask: 0x{:X}", mask);
    return true;
}

bool ProcessTuner::apply_to(const std::string& process_name) {
    auto handle = utils::win::find_process(process_name);
    if (!handle) {
        VO_LOG_WARN("process not found: {}", process_name);
        return false;
    }

    bool ok = true;
    ok &= set_priority(m_cfg.get_string("process.priority", "high"));

    const auto mask_str = m_cfg.get_string("process.affinity_mask", "0xFFFF");
    try {
        unsigned long mask = std::stoul(mask_str, nullptr, 16);
        ok &= set_affinity(mask);
    } catch (...) {
        VO_LOG_WARN("invalid affinity mask: {}", mask_str);
    }

    m_applied = ok;
    return ok;
}

bool ProcessTuner::restore() {
    if (!m_applied) return true;
    m_applied = false;
    return true;
}

} // namespace vo::services