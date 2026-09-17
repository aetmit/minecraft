#include "engine.hpp"
// define this to indicate that we are using opengl as a backend
#define OPENGL 

using namespace engine;

int main(int argc, const char *argv[]) {

    EngineConfig config(800, 600, "test window");
    Engine engine(config);
    engine.run();

    return 0;
}