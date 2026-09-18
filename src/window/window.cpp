#include <window/window.hpp>

#include <stdexcept>

namespace engine {

Window::Window(int width, int height, std::string name) {
    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize GLFW");
    }

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("failed to create window");
    }

    glfwMakeContextCurrent(window);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}
} // namespace engine