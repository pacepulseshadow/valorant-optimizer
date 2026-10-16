add_executable(optimizer_tests
    test_config_service.cpp
    test_profile_handler.cpp
)

target_link_libraries(optimizer_tests PRIVATE valorant_optimizer_core)
target_include_directories(optimizer_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_test(NAME optimizer_tests COMMAND optimizer_tests)