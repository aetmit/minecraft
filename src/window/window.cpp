#include <window/window.hpp>

#include <stdexcept>
#include <sstream>
namespace engine {

Window::Window(int width, int height, std::string name, Input &input, Logger &logger): input(input), logger(logger), width(width), height(height) {
    if (!glfwInit()) {
        throw std::runtime_error("failed to initialize GLFW");
    }

    // make sure that we are using opengl v4.1 because that is the latest version macos supports 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    
    std::stringstream ss;
    ss << "Initalised window " << width << "x" << height << " with name " << name;
    logger.info(ss.str().c_str());

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("failed to create window");
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetCursorPosCallback(window, mousePositionCallback);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
    logger.info("Shut down window successsfully");
}

void Window::mouseCallback(GLFWwindow* window, int button, int action, int) {
    Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    auto mouseButton = self->translateMouseButton(button);

    if (!mouseButton) {
        return;
    }

    if (action == GLFW_PRESS) {
        self->input.setMouseButtonDown(*mouseButton);
    } else if (action == GLFW_RELEASE) {
        self->input.setMouseButtonUp(*mouseButton);
    }
}

std::optional<MouseButton> Window::translateMouseButton(int glfwButton) {
    switch (glfwButton) {
        case GLFW_MOUSE_BUTTON_LEFT: return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        case GLFW_MOUSE_BUTTON_RIGHT: return MouseButton::Right;

        default: return std::nullopt;
    }
}

void Window::mousePositionCallback(GLFWwindow *window, double x, double y) {
    Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    self->input.setMousePosition(x, y);
}

void Window::keyCallback(GLFWwindow *window, int key, int scancode, int action, int) {
    Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));

    auto engineKey = self->translateKey(key);

    if (!engineKey) {
        return;
    }

    if (action == GLFW_PRESS) {
        self->input.setKeyDown(*engineKey);
    } else if (action == GLFW_RELEASE) {
        self->input.setKeyUp(*engineKey);
    }
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    Window *self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    
    self->width = width;
    self->height = height;

    self->resized = true;

    glViewport(0, 0, width, height);
}

void Window::resetResizedFlag() {
    resized = false;
}

bool Window::wasResized() const {
    return resized;
}

std::optional<Key> Window::translateKey(int glfwKey) {
    switch (glfwKey) {
        case GLFW_KEY_A: return Key::A;
        case GLFW_KEY_B: return Key::B;
        case GLFW_KEY_C: return Key::C;
        case GLFW_KEY_D: return Key::D;
        case GLFW_KEY_E: return Key::E;
        case GLFW_KEY_F: return Key::F;
        case GLFW_KEY_G: return Key::G;
        case GLFW_KEY_H: return Key::H;
        case GLFW_KEY_I: return Key::I;
        case GLFW_KEY_J: return Key::J;
        case GLFW_KEY_K: return Key::K;
        case GLFW_KEY_L: return Key::L;
        case GLFW_KEY_M: return Key::M;
        case GLFW_KEY_N: return Key::N;
        case GLFW_KEY_O: return Key::O;
        case GLFW_KEY_P: return Key::P;
        case GLFW_KEY_Q: return Key::Q;
        case GLFW_KEY_R: return Key::R;
        case GLFW_KEY_S: return Key::S;
        case GLFW_KEY_T: return Key::T;
        case GLFW_KEY_U: return Key::U;
        case GLFW_KEY_V: return Key::V;
        case GLFW_KEY_W: return Key::W;
        case GLFW_KEY_X: return Key::X;
        case GLFW_KEY_Y: return Key::Y;
        case GLFW_KEY_Z: return Key::Z;

        case GLFW_KEY_0: return Key::Num0;
        case GLFW_KEY_1: return Key::Num1;
        case GLFW_KEY_2: return Key::Num2;
        case GLFW_KEY_3: return Key::Num3;
        case GLFW_KEY_4: return Key::Num4;
        case GLFW_KEY_5: return Key::Num5;
        case GLFW_KEY_6: return Key::Num6;
        case GLFW_KEY_7: return Key::Num7;
        case GLFW_KEY_8: return Key::Num8;
        case GLFW_KEY_9: return Key::Num9;

        case GLFW_KEY_UP:    return Key::ArrowUp;
        case GLFW_KEY_DOWN:  return Key::ArrowDown;
        case GLFW_KEY_LEFT:  return Key::ArrowLeft;
        case GLFW_KEY_RIGHT: return Key::ArrowRight;

        case GLFW_KEY_SPACE:     return Key::Space;
        case GLFW_KEY_ENTER:     return Key::Enter;
        case GLFW_KEY_ESCAPE:    return Key::Escape;
        case GLFW_KEY_TAB:       return Key::Tab;
        case GLFW_KEY_BACKSPACE: return Key::Backspace;
        case GLFW_KEY_DELETE:    return Key::Delete;

        case GLFW_KEY_LEFT_SHIFT:    return Key::LeftShift;
        case GLFW_KEY_RIGHT_SHIFT:   return Key::RightShift;
        case GLFW_KEY_LEFT_CONTROL:  return Key::LeftControl;
        case GLFW_KEY_RIGHT_CONTROL: return Key::RightControl;
        case GLFW_KEY_LEFT_ALT:      return Key::LeftAlt;
        case GLFW_KEY_RIGHT_ALT:     return Key::RightAlt;

        case GLFW_KEY_CAPS_LOCK: return Key::CapsLock;

        case GLFW_KEY_F1:  return Key::F1;
        case GLFW_KEY_F2:  return Key::F2;
        case GLFW_KEY_F3:  return Key::F3;
        case GLFW_KEY_F4:  return Key::F4;
        case GLFW_KEY_F5:  return Key::F5;
        case GLFW_KEY_F6:  return Key::F6;
        case GLFW_KEY_F7:  return Key::F7;
        case GLFW_KEY_F8:  return Key::F8;
        case GLFW_KEY_F9:  return Key::F9;
        case GLFW_KEY_F10: return Key::F10;
        case GLFW_KEY_F11: return Key::F11;
        case GLFW_KEY_F12: return Key::F12;

        default:
            return std::nullopt;
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

float Window::aspectRatio() const {
    return static_cast<float>(width) / static_cast<float>(height);
}
} // namespace engine