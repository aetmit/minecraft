#include <engine.hpp>

#include <iostream>

#include "render/opengl/renderer.hpp"

#include "render/opengl/renderer.hpp"

namespace engine {

EngineConfig::EngineConfig(int windowWidth, int windowHeight, std::string windowName, GraphicsBackend backend)
    :windowWidth(windowWidth), windowHeight(windowHeight), windowName(windowName), backend(backend)
{}

Engine::Engine(EngineConfig& config, Input &input, Logger &logger) :
    window(config.windowWidth, config.windowHeight, config.windowName, input),
    previousTime(0),
    clock(window),
    input(input), logger(logger) {
    
    logger.info("Initialised window");
    logger.info("Initialised clock");
    logger.info("Initialised input system");

    switch (config.backend) {
        case GraphicsBackend::OpenGL:
            logger.info("Using backend OpenGL");
            renderer = std::make_unique<OpenGLRenderer>(&window, logger);
            break;
    }

    logger.info("Engine initialised");
}

void Engine::run() {

    while (!window.shouldClose()) {
        clock.updateTime();

        // update key state for new frame
        input.update();

        window.pollEvents();

        renderer->clearScreen();    


        renderer->drawSquare();


        window.swapBuffers();
    }
}    

} // namespace engine
