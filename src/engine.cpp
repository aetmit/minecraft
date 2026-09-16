#include "engine.hpp"

namespace engine {

    EngineConfig::EngineConfig(int windowWidth, int windowHeight, std::string windowName)
        :windowWidth(windowWidth), windowHeight(windowHeight), windowName(windowName) 
    {}

    Engine::Engine(EngineConfig& config) {
        window = Window(config.windowWidth, config.windowHeight, config.windowName);

    }
} // namespace engine