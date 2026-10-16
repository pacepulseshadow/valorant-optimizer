#include "services/graphics_tuner.hpp"
#include "utils/logger.hpp"
#include "utils/registry_utils.hpp"

namespace vo::services {

GraphicsTuner::GraphicsTuner(ConfigService& cfg) : m_cfg(cfg) {}

bool GraphicsTuner::disable_fullscreen_optimizations() {
    const std::string path = "SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers";
    VO_LOG_INFO("disabling fullscreen optimizations");
    return utils::registry::set_dword(HKEY_LOCAL_MACHINE, path, "DisableFullscreenOptimizations", 1);
}

bool GraphicsTuner::set_gpu_scheduling_priority(const std::string& priority) {
    VO_LOG_INFO("gpu scheduling priority -> {}", priority);
    return true;
}

bool GraphicsTuner::apply() {
    bool ok = true;
    if (m_cfg.get_bool("graphics.disable_fullscreen_optimizations", true))
        ok &= disable_fullscreen_optimizations();
    ok &= set_gpu_scheduling_priority(m_cfg.get_string("graphics.gpu_scheduling_priority", "high"));
    m_applied = ok;
    return ok;
}

bool GraphicsTuner::restore() {
    if (!m_applied) return true;
    m_applied = false;
    return true;
}

} // namespace vo::services