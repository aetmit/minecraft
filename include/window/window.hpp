#pragma once

#include <string>


#include <glad/glad.h>
// tell glfw not to include system opengl headers
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <input/input.hpp>

namespace engine {

class Window {

public:
    ~Window();

    Window(int width, int height, std::string name, Input &input);

    void pollEvents();

    void swapBuffers();

    bool shouldClose() const;

    void makeContextCurrent();

    double getTime();

private:
    GLFWwindow *getWindow() const;

    GLFWwindow *window;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    Input &input;
};

} // namespace engine
