#include "core/application.hpp"
#include "utils/logger.hpp"

#include <exception>

int main(int argc, char** argv) {
    vo::utils::Logger::init("logs/optimizer.log", vo::utils::LogLevel::Info);

    try {
        vo::core::Application app;
        return app.run(argc, argv);
    } catch (const std::exception& ex) {
        VO_LOG_ERROR("fatal: {}", ex.what());
        return 1;
    }
}