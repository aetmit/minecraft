#include <window/window.hpp>

#include <stdexcept>

namespace engine {

Window::Window(int width, int height, std::string name, Input &input): input(input) {
    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize GLFW");
    }

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("failed to create window");
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if (action == GLFW_PRESS) {
        self->input.setKeyDown(static_cast<Key>(key));
    } else if (action == GLFW_RELEASE) {
        self->input.setKeyUp(static_cast<Key>(key));
    }
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

double Window::getTime() {
    return glfwGetTime();
}
} // namespace engine