#include <engine.hpp>
#include <input/input.hpp>

#include <application.hpp>

using namespace engine;

int main(int argc, const char *argv[]) {

    Application app(BACKEND_OPENGL);
    return app.run();
}