#include "models/system_snapshot.hpp"

#include <windows.h>

namespace vo::models {

SystemSnapshot capture_system_snapshot() {
    SystemSnapshot snap;

    SYSTEM_INFO si{};
    GetNativeSystemInfo(&si);
    snap.cpu.logical_cores  = si.dwNumberOfProcessors;
    snap.cpu.physical_cores = si.dwNumberOfProcessors / 2;

    MEMORYSTATUSEX mem{};
    mem.dwLength = sizeof(mem);
    if (GlobalMemoryStatusEx(&mem)) {
        snap.total_ram_bytes = mem.ullTotalPhys;
    }

    snap.os_build = "windows-10.0.26100";
    return snap;
}

} // namespace vo::models