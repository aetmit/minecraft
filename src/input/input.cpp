#include <input/input.hpp>

namespace engine {

bool Input::isKeyDown(Key key) const {
    return keys[static_cast<std::size_t>(key)].current;
}

bool Input::isKeyUp(Key key) const {
    return !keys[static_cast<std::size_t>(key)].current;
}

bool Input::wasKeyPressed(Key key) const {
    const auto& state = keys[static_cast<std::size_t>(key)];
    return !state.previous && state.current;
}

bool Input::wasKeyReleased(Key key) const {
    const auto& state = keys[static_cast<std::size_t>(key)];
    return state.previous && !state.current;
}

void Input::update() {
    for (auto &key : keys) {
        key.previous = key.current;
    }

    for (auto &button : mouseButtons) {
        button.previous = button.current;
    }

    mouseDeltaX_ = mouseX - previousMouseX;
    mouseDeltaY_ = mouseY - previousMouseY;
    previousMouseX = mouseX;
    previousMouseY = mouseY;
}

void Input::setKeyDown(Key key) {
    keys[static_cast<std::size_t>(key)].current = true;
}

void Input::setKeyUp(Key key) {
    keys[static_cast<std::size_t>(key)].current = false;
}

bool Input::isMouseButtonDown(MouseButton button) const {
    return mouseButtons[static_cast<std::size_t>(button)].current;
}

bool Input::isMouseButtonUp(MouseButton button) const {
    return !mouseButtons[static_cast<std::size_t>(button)].current;
}

bool Input::wasMouseButtonPressed(MouseButton button) const {
    const auto &state = mouseButtons[static_cast<std::size_t>(button)];
    return !state.previous && state.current;
}

bool Input::wasMouseButtonReleased(MouseButton button) const {
    const auto &state = mouseButtons[static_cast<std::size_t>(button)];
    return state.previous && !state.current;
}

void Input::setMouseButtonDown(MouseButton button) {
    mouseButtons[static_cast<std::size_t>(button)].current = true;
}
 
void Input::setMouseButtonUp(MouseButton button) {
    mouseButtons[static_cast<std::size_t>(button)].current = false;
}

void Input::setMousePosition(double mouseX, double mouseY) {
    this->mouseX = mouseX;
    this->mouseY = mouseY;
}

double Input::mouseDeltaX() const {
    return mouseDeltaX_;
}

double Input::mouseDeltaY() const {
    return mouseDeltaY_;
}

void Input::resetMousePosition(double currentX, double currentY) {
    mouseX = currentX;
    mouseY = currentY;
    previousMouseX = currentX;
    previousMouseY = currentY;
    mouseDeltaX_ = 0.0;
    mouseDeltaY_ = 0.0;
}

} // namespace engine