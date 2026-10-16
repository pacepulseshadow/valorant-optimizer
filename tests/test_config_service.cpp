#include "services/config_service.hpp"

#include <cassert>
#include <iostream>

using namespace vo::services;

void test_builtin_defaults() {
    ConfigService cfg("nonexistent.toml");