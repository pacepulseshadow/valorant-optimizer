#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace vo::models {

struct CpuInfo {
    std::string vendor;
    std::string brand;
    uint32_t    logical_cores = 0;
    uint32_t    physical_cores = 0;
};

struct GpuInfo {
    std::string name;
    uint64_t    vram_bytes = 0;
    std::string driver_version;
};

struct SystemSnapshot {
    CpuInfo              cpu;
    std::vector<GpuInfo> gpus;
    uint64_t             total_ram_bytes = 0;
    std::string          os_build;
    bool                 game_bar_enabled = false;
};

SystemSnapshot capture_system_snapshot();

} // namespace vo::models