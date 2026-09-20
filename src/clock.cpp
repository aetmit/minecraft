#include <clock.hpp>

namespace engine {

Clock::Clock(Window& window) :
    window(window),
    currentTime(0.0),
    previousTime(0.0)
{}

double Clock::getCurrentTime() const {
    return currentTime;
}

double Clock::getDeltaTime() const {
    return currentTime - previousTime;
}

void Clock::updateTime() {
    previousTime = currentTime;
    currentTime = window.getTime();
}

}  // namespace engine
