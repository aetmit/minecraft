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
}

void Input::setKeyDown(Key key) {
    keys[static_cast<std::size_t>(key)].current = true;
}

void Input::setKeyUp(Key key) {
    keys[static_cast<std::size_t>(key)].current = false;
}

bool Input::isMouseButtonDown(MouseButton button) const {

}

bool Input::isMouseButtonUp(MouseButton button) const {

}

bool Input::wasMouseButtonPressed(MouseButton button) const {

}

bool Input::wasMouseButtonReleased(MouseButton button) const {

}

void Input::setMouseButtonDown(MouseButton button) {

}
 
void Input::setMouseButtonUp(MouseButton button) {

}

void Input::setMousePosition(double mouseX, double mouseY) {

}

double Input::mouseX() const {

}
double Input::mouseY() const  {

}

double Input::mouseDeltaX() {

}

double Input::mouseDeltaY() {

}

} // namespace engine