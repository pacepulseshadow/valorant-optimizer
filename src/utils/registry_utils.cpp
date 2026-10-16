#include "utils/registry_utils.hpp"
#include "utils/logger.hpp"

namespace vo::utils::registry {

bool set_dword(HKEY root, const std::string& subkey, const std::string& name, DWORD value) {
    HKEY key = nullptr;
    if (RegCreateKeyExA(root, subkey.c_str(), 0, nullptr, 0,
                        KEY_SET_VALUE, nullptr, &key, nullptr) != ERROR_SUCCESS) {
        VO_LOG_ERROR("failed to open registry key: {}", subkey);
        return false;
    }
    LSTATUS status = RegSetValueExA(key, name.c_str(), 0, REG_DWORD,
                                    reinterpret_cast<const BYTE*>(&value), sizeof(value));
    RegCloseKey(key);
    return status == ERROR_SUCCESS;
}

bool set_string(HKEY root, const std::string& subkey, const std::string& name, const std::string& value) {
    HKEY key = nullptr;
    if (RegCreateKeyExA(root, subkey.c_str(), 0, nullptr, 0,
                        KEY_SET_VALUE, nullptr, &key, nullptr) != ERROR_SUCCESS) {
        return false;
    }
    LSTATUS status = RegSetValueExA(key, name.c_str(), 0, REG_SZ,
                                    reinterpret_cast<const BYTE*>(value.c_str()),
                                    static_cast<DWORD>(value.size() + 1));
    RegCloseKey(key);
    return status == ERROR_SUCCESS;
}

bool read_dword(HKEY root, const std::string& subkey, const std::string& name, DWORD& out) {
    HKEY key = nullptr;
    if (RegOpenKeyExA(root, subkey.c_str(), 0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS) {
        return false;
    }
    DWORD size = sizeof(out);
    DWORD type = 0;
    LSTATUS status = RegQueryValueExA(key, name.c_str(), nullptr, &type,
                                      reinterpret_cast<BYTE*>(&out), &size);
    RegCloseKey(key);
    return status == ERROR_SUCCESS && type == REG_DWORD;
}

} // namespace vo::utils::registry