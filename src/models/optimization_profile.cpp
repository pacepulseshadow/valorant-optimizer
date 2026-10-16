#include "models/optimization_profile.hpp"

namespace vo::models {

OptimizationProfile make_competitive_profile() {
    OptimizationProfile p;
    p.name = "competitive";
    p.description = "Lowest input latency and highest network responsiveness.";
    p.is_default = true;
    p.tweaks = {
        {"network.tcp_nodelay",     "true",  true},
        {"network.nagle_algorithm", "false", true},
        {"input.mouse_acceleration","false", false},
        {"input.usb_polling_hz",    "1000",  false},
        {"graphics.disable_fullscreen_optimizations", "true", true},
        {"process.priority",        "high",  true},
    };
    return p;
}

OptimizationProfile make_low_end_profile() {
    OptimizationProfile p;
    p.name = "low_end";
    p.description = "Aggressive tweaks for older hardware.";
    p.tweaks = {
        {"graphics.shader_cache_size_mb", "512", true},
        {"process.priority",              "high", true},
        {"network.tcp_nodelay",           "true", true},
    };
    return p;
}

} // namespace vo::models