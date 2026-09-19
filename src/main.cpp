#include <engine.hpp>
#include <input/input.hpp>

using namespace engine;

int main(int argc, const char *argv[]) {

    EngineConfig config(800, 600, "Minecraft", GraphicsBackend::OpenGL);
    Input input;
    Engine engine(config, input);
    engine.run();

    return 0;
}