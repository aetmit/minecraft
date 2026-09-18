#include <engine.hpp>

#include <GLFW/glfw3.h>

using namespace engine;

int main(int argc, const char *argv[]) {

    EngineConfig config(800, 600, "Minecraft", GraphicsBackend::OpenGL);
    Engine engine(config);
    engine.run();

    return 0;
}