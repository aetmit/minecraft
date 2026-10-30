#pragma once

#include <window/window.hpp>
#include <render/renderer.hpp>
#include <input/input.hpp>

#include <memory>

namespace ui {

class DebugScreen {

public:
    DebugScreen(engine::Renderer *renderer, engine::Window& window);

    void update(const engine::Input &input, engine::Window& window);

private:
    std::unique_ptr<engine::Renderer> renderer;

    bool displayDebug;

    engine::Text *versionText;
};

}  // namespace ui
