#include "core/bootstrap.hpp"

#include <string_view>

namespace vo::core {

BootstrapOptions parse_bootstrap(int argc, char** argv) {
    BootstrapOptions opts;
    for (int i = 1; i < argc; ++i) {
        std::string_view arg{argv[i]};
        if (arg == "--config" && i + 1 < argc) {
            opts.config_path = argv[++i];
        } else if (arg == "--verbose" || arg == "-v") {
            opts.verbose = true;
        } else if (arg == "--dry-run") {
            opts.dry_run = true;
        }
    }
    return opts;
}

} // namespace vo::core