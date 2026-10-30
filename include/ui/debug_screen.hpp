#pragma once

#include <core/clock.hpp>
#include <window/window.hpp>
#include <render/renderer.hpp>
#include <input/input.hpp>

#include <cstddef>
#include <memory>

namespace ui {

class DebugScreen {

public:
    DebugScreen(engine::Renderer *renderer, engine::Window& window, engine::Clock& clock);

    void update(const engine::Input &input, engine::Window& window);

private:
    std::unique_ptr<engine::Renderer> renderer;

    std::string leftPanelText;

    bool displayDebug;

    engine::Text *leftPanel;

    engine::Clock& clock;

    double fpsElapsed;
    std::size_t fpsFrames;
};

}  // namespace ui
