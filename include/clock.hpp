#pragma once

#include <window/window.hpp>

namespace engine {

class Clock {

public:
    Clock(Window& window);

    double getCurrentTime() const;

    double getDeltaTime() const;

    void updateTime();

private:
    Window& window;

    double currentTime;
    double previousTime;
};

} // namespace engine
