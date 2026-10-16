#pragma once

#include <string>
#include <unordered_map>
#include <variant>

namespace vo::services {

using ConfigValue = std::variant<std::string, int, bool, double>;

class ConfigService {
public:
    explicit ConfigService(std::string path);

    bool load();
    void use_builtin_defaults();
    bool save() const;

    std::string get_string(const std::string& key, const std::string& fallback) const;
    int         get_int(const std::string& key, int fallback) const;
    bool        get_bool(const std::string& key, bool fallback) const;

    void set(const std::string& key, ConfigValue value);

private:
    std::string m_path;
    std::unordered_map<std::string, ConfigValue> m_values;
};

} // namespace vo::services