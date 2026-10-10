#include <engine.hpp>

#include <iostream>
#include <memory>

#include <render/opengl/renderer.hpp>

#include <game/player.hpp>
#include <render/mesh.hpp>
#include <core/transform.hpp>
#include <core/atlas.hpp>
#include <game/world/chunk.hpp>
#include <game/world/chunk_mesher.hpp>

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

    // The renderer uploads the atlas during construction, so generate it first.
    tools::Atlas atlas;
    atlas.generateAtlas();

    switch (config.backend) {
        case GraphicsBackend::OpenGL:
            logger.info("Using backend OpenGL");
            renderer = std::make_unique<opengl::Renderer>(&window, logger);
            break;
    }

    logger.info("Engine initialised");
}

void Engine::run() {

    game::Chunk chunk;
    chunk.setDummy();
    
    game::ChunkMesher mesher;
    MeshData data = mesher.generate(chunk);

    std::unique_ptr<Mesh> mesh = renderer->createMesh(data);
    Transform transform;

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

        renderer->drawMesh(*mesh, transform);


        window.swapBuffers();
    }
}    

} // namespace engine
