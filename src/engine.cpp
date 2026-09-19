#include <engine.hpp>

#include "render/opengl/renderer.hpp"

#include "render/opengl/renderer.hpp"

namespace engine {

EngineConfig::EngineConfig(int windowWidth, int windowHeight, std::string windowName, GraphicsBackend backend)
    :windowWidth(windowWidth), windowHeight(windowHeight), windowName(windowName), backend(backend)
{}

Engine::Engine(EngineConfig& config, Input &input)
        : window(config.windowWidth, config.windowHeight, config.windowName, input), previousTime(0), input(input) {

    // make sure that we are using opengl v4.1 because that is the latest version macos supports 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    switch (config.backend) {
        case GraphicsBackend::OpenGL:
            renderer = std::make_unique<OpenGLRenderer>(&window);
            break;
    }
}

void Engine::run() {

    while (!window.shouldClose()) {
        double currentTime = window.getTime();
        double deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        // update key state for new frame
        input.update();

        window.pollEvents();

        renderer->clearScreen();    


        renderer->drawTriangle();

        window.swapBuffers();

    }
}    

} // namespace engine
