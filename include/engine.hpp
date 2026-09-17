#pragma once

#include <string>

#include <window/window.hpp>

namespace engine {

struct EngineConfig {
    int windowWidth;
    int windowHeight;
    std::string windowName;

    EngineConfig(int windowWidth, int windowHeight, std::string windowName);
};

class Engine {

public:
    explicit Engine(EngineConfig& config);

    void run();

private:
    Window window;
};

} // namespace engine