#include "utils/win_handle.hpp"

#include <tlhelp32.h>

namespace vo::utils::win {

unique_handle find_process(const std::string& process_name) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        return {nullptr, &CloseHandle};
    }

    PROCESSENTRY32A entry{};
    entry.dwSize = sizeof(entry);

    if (Process32FirstA(snapshot, &entry)) {
        do {
            if (process_name == entry.szExeFile) {
                CloseHandle(snapshot);
                HANDLE h = OpenProcess(PROCESS_SET_INFORMATION | PROCESS_QUERY_INFORMATION,
                                       FALSE, entry.th32ProcessID);
                return {h, &CloseHandle};
            }
        } while (Process32NextA(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return {nullptr, &CloseHandle};
}

std::string get_last_error_string() {
    DWORD err = GetLastError();
    if (err == 0) return "no error";

    LPSTR buffer = nullptr;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                   nullptr, err, 0, reinterpret_cast<LPSTR>(&buffer), 0, nullptr);
    std::string result = buffer ? buffer : "unknown error";
    LocalFree(buffer);
    return result;
}

} // namespace vo::utils::win