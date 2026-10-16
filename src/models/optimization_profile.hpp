#pragma once

#include <string>
#include <vector>

namespace vo::models {

struct TweakEntry {
    std::string key;
    std::string value;
    bool        requires_admin = false;
};

struct OptimizationProfile {
    std::string            name;
    std::string            description;
    std::vector<TweakEntry> tweaks;
    bool                   is_default = false;
};

OptimizationProfile make_competitive_profile();
OptimizationProfile make_low_end_profile();

} // namespace vo::models