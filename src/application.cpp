#include <application.hpp>

#include <exception>
#include <iostream>

#include <input/input.hpp>
#include <core/logger.hpp>

int Application::run() {
    engine::Logger logger; 
    logger.setLogLevel(engine::LogLevel::Verbose);
    logger.verbose("Hello World!");
    try {
        engine::Input input;
        engine::EngineConfig config(800, 600, "Minecraft", backend);
        engine::Engine engine(config, input, logger);
        engine.run();
    } catch (const std::exception &e) {
        logger.error(e.what());
        return 1;
    }
    return 0;
}

Application::Application(int backend) {
    switch (backend) {
        case BACKEND_OPENGL: 
            this->backend = engine::GraphicsBackend::OpenGL;
            break;
    }
}
