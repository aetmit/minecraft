#include <engine.hpp>

#include <iostream>
#include <cstddef>
#include <memory>
#include <vector>

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

    std::vector<std::unique_ptr<Mesh>> chunkMeshes;

    constexpr int mapLength = 3;
    constexpr int mapWidth = 3;
    constexpr long long firstChunkX = -(mapLength / 2);
    constexpr long long firstChunkZ = -(mapWidth / 2);

    game::ChunkMesher mesher{logger};
    std::vector<game::Chunk> chunks(
        static_cast<std::size_t>(mapLength * mapWidth));

    const auto chunkIndex = [](int x, int z) {
        return static_cast<std::size_t>(x * mapWidth + z);
    };

    for (int x = 0; x < mapLength; ++x) {
        for (int z = 0; z < mapWidth; ++z) {
            chunks[chunkIndex(x, z)].setDummy(firstChunkX + x, firstChunkZ + z);
        }
    }

    for (int x = 0; x < mapLength; ++x) {
        for (int z = 0; z < mapWidth; ++z) {
            const game::Chunk* positiveX =
                x < (mapLength - 1) ? &chunks[chunkIndex(x + 1, z)] : nullptr;
            const game::Chunk* negativeX =
                x > 0 ? &chunks[chunkIndex(x - 1, z)] : nullptr;
            const game::Chunk* positiveZ =
                z < (mapWidth - 1) ? &chunks[chunkIndex(x, z + 1)] : nullptr;
            const game::Chunk* negativeZ =
                z > 0 ? &chunks[chunkIndex(x, z - 1)] : nullptr;

            MeshData data = mesher.generate(
                chunks[chunkIndex(x, z)], positiveX, negativeX, positiveZ, negativeZ);
            chunkMeshes.push_back(renderer->createMesh(data));
        }
    }
    
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

        for (const auto& mesh : chunkMeshes) {
            renderer->drawMesh(*mesh, transform);
        }

        window.swapBuffers();
    }
}    

} // namespace engine
