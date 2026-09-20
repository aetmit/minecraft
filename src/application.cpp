#include <application.hpp>

#include <exception>
#include <iostream>

#include <input/input.hpp>

int Application::run() {
    engine::Input input;
    engine::EngineConfig config(800, 600, "Minecraft", backend);

    engine::Engine engine(config, input);
    try {
        engine.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
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
