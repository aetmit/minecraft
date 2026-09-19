#include <engine.hpp>

#include "render/opengl/renderer.hpp"

#include "render/opengl/renderer.hpp"

namespace engine {

EngineConfig::EngineConfig(int windowWidth, int windowHeight, std::string windowName, GraphicsBackend backend)
    :windowWidth(windowWidth), windowHeight(windowHeight), windowName(windowName), backend(backend)
{}

Engine::Engine(EngineConfig& config): window(config.windowWidth, config.windowHeight, config.windowName) {

    switch (config.backend) {
        case GraphicsBackend::OpenGL:
            renderer = std::make_unique<OpenGLRenderer>(&window);
            break;
    }
}

void Engine::run() {
    while (!window.shouldClose()) {

        window.pollEvents();

        renderer->clearScreen();    
        renderer->drawTriangle();

        window.swapBuffers();
    }
}    

} // namespace engine
