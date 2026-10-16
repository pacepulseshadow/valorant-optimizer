#include "services/config_service.hpp"
#include "utils/logger.hpp"

#include <fstream>
#include <sstream>

namespace vo::services {

ConfigService::ConfigService(std::string path) : m_path(std::move(path)) {}

bool ConfigService::load() {
    std::ifstream in(m_path);
    if (!in.is_open()) return false;

    std::string line, section;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line.front() == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
            continue;
        }
        auto eq = line.find('=');
        if (eq == std::string::npos) continue;

        auto key   = section + "." + line.substr(0, eq);
        auto value = line.substr(eq + 1);
        // trim
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t"));

        if (value == "true" || value == "false") {
            m_values[key] = (value == "true");
        } else if (!value.empty() && value.front() == '"') {
            m_values[key] = value.substr(1, value.size() - 2);
        } else {
            try { m_values[key] = std::stoi(value); }
            catch (...) { m_values[key] = value; }
        }
    }
    VO_LOG_INFO("loaded {} keys from {}", m_values.size(), m_path);
    return true;
}

void ConfigService::use_builtin_defaults() {
    m_values["optimizer.profile"] = std::string{"competitive"};
    m_values["optimizer.auto_apply_on_launch"] = true;
    m_values["optimizer.restore_on_exit"] = true;
    m_values["network.tcp_nodelay"] = true;
    m_values["graphics.disable_fullscreen_optimizations"] = true;
    m_values["process.priority"] = std::string{"high"};
    m_values["logging.level"] = std::string{"info"};
}

std::string ConfigService::get_string(const std::string& key, const std::string& fallback) const {
    auto it = m_values.find(key);
    if (it == m_values.end()) return fallback;
    if (auto* v = std::get_if<std::string>(&it->second)) return *v;
    return fallback;
}

int ConfigService::get_int(const std::string& key, int fallback) const {
    auto it = m_values.find(key);
    if (it == m_values.end()) return fallback;
    if (auto* v = std::get_if<int>(&it->second)) return *v;
    return fallback;
}

bool ConfigService::get_bool(const std::string& key, bool fallback) const {
    auto it = m_values.find(key);
    if (it == m_values.end()) return fallback;
    if (auto* v = std::get_if<bool>(&it->second)) return *v;
    return fallback;
}

void ConfigService::set(const std::string& key, ConfigValue value) {
    m_values[key] = std::move(value);
}

bool ConfigService::save() const {
    std::ofstream out(m_path);
    if (!out.is_open()) return false;
    for (const auto& [k, v] : m_values) {
        out << k << " = ";
        std::visit([&out](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, std::string>) out << '"' << arg << '"';
            else if constexpr (std::is_same_v<T, bool>) out << (arg ? "true" : "false");
            else out << arg;
        }, v);
        out << '\n';
    }
    return true;
}

} // namespace vo::services