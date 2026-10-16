#pragma once

#include <string>
#include <windows.h>

namespace vo::utils::registry {

bool set_dword(HKEY root, const std::string& subkey, const std::string& name, DWORD value);
bool set_string(HKEY root, const std::string& subkey, const std::string& name, const std::string& value);
bool read_dword(HKEY root, const std::string& subkey, const std::string& name, DWORD& out);

} // namespace vo::utils::registry