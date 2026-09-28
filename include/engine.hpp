#pragma once

#include <string>
#include <memory>

#include <core/clock.hpp>
#include <core/logger.hpp>
#include <window/window.hpp>
#include <render/renderer.hpp>
#include <input/input.hpp>

namespace engine {

enum class GraphicsBackend {
    OpenGL,
};

struct EngineConfig {
    int windowWidth;
    int windowHeight;
    std::string windowName;
    GraphicsBackend backend;

    EngineConfig(int windowWidth, int windowHeight, std::string windowName,  GraphicsBackend backend);
};

class Engine {

public:
    explicit Engine(EngineConfig& config, Input &input, Logger &logger);

    void run();

private:
    Window window;

    std::unique_ptr<Renderer> renderer;

    double previousTime;

    Clock clock;

    Logger &logger;

    Input &input;
};

} // namespace engine