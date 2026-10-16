#pragma once

#include "services/config_service.hpp"

namespace vo::services {

class NetworkTuner {
public:
    explicit NetworkTuner(ConfigService& cfg);

    bool apply();
    bool restore();

private:
    bool set_tcp_nodelay(bool enabled);
    bool set_nagle(bool enabled);
    bool flush_dns_cache();

    ConfigService& m_cfg;
    bool m_applied = false;
};

} // namespace vo::services