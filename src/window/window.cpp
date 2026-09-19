#include <window/window.hpp>

#include <stdexcept>

namespace engine {

Window::Window(int width, int height, std::string name) {
    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize GLFW");
    }

    // make sure that we are using opengl v4.1 because that is the latest version macos supports 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("failed to create window");
    }

}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::makeContextCurrent() {
    glfwMakeContextCurrent(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}
} // namespace engine