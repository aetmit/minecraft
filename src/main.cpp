#include "GLFW/glfw3.h"

#include "engine.hpp"

using namespace engine;

int main(int argc, const char *argv[]) {

    // make sure that we are using opengl v4.1 because that is the latest version macos supports 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    EngineConfig config(800, 600, "Minecraft", GraphicsBackend::OpenGL);
    Engine engine(config);
    engine.run();

    return 0;
}