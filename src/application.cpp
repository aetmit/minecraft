#include <application.hpp>

#include <input/input.hpp>

int Application::run() {
    engine::Input input;
    engine::EngineConfig config(800, 600, "Minecraft", backend);

    engine::Engine engine(config, input);
    engine.run();
    return 0;
}

Application::Application(int backend) {
    switch (backend) {
        case BACKEND_OPENGL: 
            this->backend = engine::GraphicsBackend::OpenGL;
            break;
    }
}
