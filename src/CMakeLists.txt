add_library(valorant_optimizer_core STATIC
    core/application.cpp
    core/bootstrap.cpp
    services/config_service.cpp
    services/network_tuner.cpp
    services/graphics_tuner.cpp
    services/process_tuner.cpp
    services/input_tuner.cpp
    handlers/cli_handler.cpp
    handlers/profile_handler.cpp
    models/optimization_profile.cpp
    models/system_snapshot.cpp
    utils/registry_utils.cpp
    utils/logger.cpp
    utils/win_handle.cpp
)

target_include_directories(valorant_optimizer_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(valorant_optimizer_core PUBLIC
    iphlpapi
    advapi32
    shell32
    powrprof
    ws2_32
)

add_executable(valorant-optimizer main.cpp)
target_link_libraries(valorant-optimizer PRIVATE valorant_optimizer_core)