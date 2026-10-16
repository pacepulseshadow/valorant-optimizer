#pragma once

#include <windows.h>
#include <string>
#include <memory>

namespace vo::utils::win {

using unique_handle = std::unique_ptr<std::remove_pointer_t<HANDLE>, decltype(&CloseHandle)>;

unique_handle find_process(const std::string& process_name);
std::string   get_last_error_string();

} // namespace vo::utils::win