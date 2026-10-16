#include "utils/logger.hpp"

#include <fstream>
#include <chrono>
#include <iostream>
#include <mutex>

namespace vo::utils {

namespace {
    std::ofstream   g_file;
    LogLevel        g_level = LogLevel::Info;
    std::mutex      g_mutex;

    const char* level_name(LogLevel l) {
        switch (l) {
            case LogLevel::Debug: return "DEBUG";
            case LogLevel::Info:  return "INFO";
            case LogLevel::Warn:  return "WARN";
            case LogLevel::Error: return "ERROR";
        }
        return "?";
    }
}

void Logger::init(const std::string& file, LogLevel level) {
    std::lock_guard lock(g_mutex);
    g_level = level;
    g_file.open(file, std::ios::app);
}

void Logger::shutdown() {
    std::lock_guard lock(g_mutex);
    if (g_file.is_open()) g_file.close();
}

void Logger::log(LogLevel level, std::string_view msg) {
    if (level < g_level) return;
    std::lock_guard lock(g_mutex);
    auto now = std::chrono::system_clock::now();
    auto t   = std::chrono::system_clock::to_time_t(now);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&t));

    if (g_file.is_open()) {
        g_file << buf << " [" << level_name(level) << "] " << msg << '\n';
        g_file.flush();
    } else {
        std::cout << buf << " [" << level_name(level) << "] " << msg << '\n';
    }
}

} // namespace vo::utils