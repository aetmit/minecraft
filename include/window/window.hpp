#pragma once

#include <string>
#include <optional>

#include <glad/glad.h>
// tell glfw not to include system opengl headers
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <input/input.hpp>
#include <core/logger.hpp>

namespace engine {

class Window {

public:
    ~Window();

    Window(int width, int height, std::string name, Input &input, Logger &logger);

    void pollEvents();

    void swapBuffers();

    bool shouldClose() const;

    void makeContextCurrent();

    double getTime();

    float aspectRatio() const;

    void resetResizedFlag();
    bool wasResized() const;

    void setCursorLocked(bool locked);
    bool isCursorLocked() const;

private:
    GLFWwindow *getWindow() const;

    GLFWwindow *window;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow *window, int button, int action, int mods);
    static void mousePositionCallback(GLFWwindow *window, double x, double y);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

    std::optional<MouseButton> translateMouseButton(int glfwButton);
    std::optional<Key> translateKey(int glfwKey);
    Input &input;
    Logger &logger;

    int width;
    int height;

    bool resized{false};
    bool cursorLocked{false};
};

} // namespace engine
