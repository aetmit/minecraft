#include <engine.hpp>

#include <iostream>
#include <memory>

#include "render/opengl/renderer.hpp"

#include <game/player.hpp>
#include <render/mesh.hpp>

namespace engine {

EngineConfig::EngineConfig(int windowWidth, int windowHeight, std::string windowName, GraphicsBackend backend)
    :windowWidth(windowWidth), windowHeight(windowHeight), windowName(windowName), backend(backend)
{}

Engine::Engine(EngineConfig& config, Input &input, Logger &logger) :
    window(config.windowWidth, config.windowHeight, config.windowName, input, logger),
    previousTime(0),
    clock(window),
    input(input), logger(logger) {
    
    logger.info("Initialised window");
    logger.info("Initialised clock");
    logger.info("Initialised input system");

    switch (config.backend) {
        case GraphicsBackend::OpenGL:
            logger.info("Using backend OpenGL");
            renderer = std::make_unique<opengl::Renderer>(&window, logger);
            break;
    }

    logger.info("Engine initialised");
}

void Engine::run() {

    MeshData meshdata;
    meshdata.indices = {
        0, 1, 2, 2, 3, 0,

        4, 7, 6, 6, 5, 4,

        8, 11, 10, 10, 9, 8,

        12, 13, 14, 14, 15, 12,

        16, 17, 18, 18, 19, 16,

        20, 23, 22, 22, 21, 20
    };

    meshdata.vertices = {
        Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, -0.5f,  0.5f, 1.0f, 0.0f),
        Vertex( 0.5f,  0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 0.0f, 1.0f),

        Vertex( 0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 1.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f, 0.0f, 1.0f),

        Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 0.0f, 1.0f),


        Vertex(0.5f, -0.5f,  0.5f, 0.0f, 0.0f),
        Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f, 1.0f, 1.0f),
        Vertex(0.5f,  0.5f,  0.5f, 0.0f, 1.0f),

        Vertex(-0.5f, 0.5f,  0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, 0.5f,  0.5f, 1.0f, 0.0f),
        Vertex( 0.5f, 0.5f, -0.5f, 1.0f, 1.0f),
        Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f),

        Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex( 0.5f, -0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 1.0f),
    };

    std::unique_ptr<Mesh> mesh = renderer->createMesh(meshdata);

    window.setCursorLocked(true);

    game::Player player(window.aspectRatio());
    renderer->setCamera(&player.getCamera());

    while (!window.shouldClose()) {
        clock.updateTime();

        // update key state for new frame
        input.update();

        window.pollEvents();

        if (input.wasKeyPressed(Key::Escape)) {
            window.setCursorLocked(false);
        }

        if (window.wasResized()) {
            renderer->updateProjection();

            window.resetResizedFlag();
        }

        renderer->clearScreen();    

        if (!window.isCursorLocked() && input.wasMouseButtonPressed(MouseButton::Left)) {
            window.setCursorLocked(true);
        }

        if (window.isCursorLocked()) {
            player.update(clock.getDeltaTime(), input);
        }

        renderer->drawMesh(*mesh);


        window.swapBuffers();
    }
}    

} // namespace engine
