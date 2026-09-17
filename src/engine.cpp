#include "engine.hpp"

namespace engine {

EngineConfig::EngineConfig(int windowWidth, int windowHeight, std::string windowName)
    :windowWidth(windowWidth), windowHeight(windowHeight), windowName(windowName) 
{}

Engine::Engine(EngineConfig& config): window(config.windowWidth, config.windowHeight, config.windowName) {}

void Engine::run() {
    while (!window.shouldClose()) {
        
        window.swapBuffers();

        window.pollEvents();
    }
}    

} // namespace engine