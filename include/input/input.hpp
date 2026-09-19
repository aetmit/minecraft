#pragma once

#include <array>
#include <cstddef>

namespace engine {

enum class Key {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    Space,
    Enter,
    Escape,
    Tab,
    Backspace,
    Delete,
    LeftShift,
    RightShift,
    LeftControl,
    RightControl,
    LeftAlt,
    RightAlt,
    CapsLock,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12, 


    // because c++23 does not provide reflection, we can determine how many keys there are in this enum class
    // by simply doing static_cast<std::size_t>(Key::Count) to get the number of elements since the variants 
    // are numbered from 0 upwards
    Count,
};

enum class MouseButton {
    Left,
    Middle,
    Right,
};

struct ButtonState {
    bool current{false};
    bool previous{false};
};

struct KeyState {
    bool current{false};
    bool previous{false};
};

class Input {

public: 
    // key currently being held
    bool isKeyDown(Key key) const;
    // key currently NOT being held
    bool isKeyUp(Key key) const;

    // key went from up to down this frame
    bool wasKeyPressed(Key key) const;
    // key went from down to up this frame
    bool wasKeyReleased(Key key) const;

    void setKeyUp(Key key);

    void setKeyDown(Key key);

    bool isMouseButtonDown(MouseButton button) const;
    bool isMouseButtonUp(MouseButton button) const;

    bool wasMouseButtonPressed(MouseButton button) const;
    bool wasMouseButtonReleased(MouseButton button) const;

    void setMouseButtonDown(MouseButton button);
    void setMouseButtonUp(MouseButton button);

    void setMousePosition(double mouseX, double mouseY);

    double mouseX() const;
    double mouseY() const;

    double mouseDeltaX();
    double mouseDeltaY();

    void update();

private:
    std::array<KeyState, static_cast<std::size_t>(Key::Count)> keys;

    std::array<ButtonState, 3> mouseButtons;

    double mouseX_;
    double mouseY_;
    double mouseDeltaX_;
    double mouseDeltaY_;
};

} // namespace engine