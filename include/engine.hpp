#ifndef ENGINE_HPP
#define ENGINE_HPP

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

private:
    Window window;
};

} // namespace engine

#endif // ENGINE_HPP
