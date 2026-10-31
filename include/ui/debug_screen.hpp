#pragma once

#include <core/clock.hpp>
#include <window/window.hpp>
#include <render/renderer.hpp>
#include <input/input.hpp>

#include <cstddef>

namespace ui {

class DebugScreen {

public:
    DebugScreen(engine::Renderer *renderer, engine::Window& window, engine::Clock& clock);

    void update(const engine::Input &input, engine::Window& window);

private:
    std::string leftPanelText;
    std::string rightPanelText;

    bool displayDebug;

    engine::Text *leftPanel;
    engine::Text *rightPanel;

    engine::Clock& clock;

    double fpsElapsed;
    std::size_t fpsFrames;

    std::size_t getMemoryUsage() const;

    std::size_t getSystemMemory() const;
};

}  // namespace ui
