#pragma once

#include <string>

namespace vo::core {

struct BootstrapOptions {
    std::string config_path = "config/default.toml";
    bool        verbose     = false;
    bool        dry_run     = false;
};

BootstrapOptions parse_bootstrap(int argc, char** argv);

} // namespace vo::core