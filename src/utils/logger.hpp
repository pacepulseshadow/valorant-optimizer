#pragma once

#include <string>
#include <string_view>
#include <mutex>

namespace vo::utils {

enum class LogLevel { Debug, Info, Warn, Error };

class Logger {
public:
    static void init(const std::string& file, LogLevel level);
    static void shutdown();
    static void log(LogLevel level, std::string_view msg);

    template <typename... Args>
    static void info(std::string_view fmt, Args&&... args);
};

} // namespace vo::utils

#define VO_LOG_INFO(...)  ::vo::utils::Logger::log(::vo::utils::LogLevel::Info,  __VA_ARGS__)
#define VO_LOG_WARN(...)  ::vo::utils::Logger::log(::vo::utils::LogLevel::Warn,  __VA_ARGS__)
#define VO_LOG_ERROR(...) ::vo::utils::Logger::log(::vo::utils::LogLevel::Error, __VA_ARGS__)
#define VO_LOG_DEBUG(...) ::vo::utils::Logger::log(::vo::utils::LogLevel::Debug, __VA_ARGS__)