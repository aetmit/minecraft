#include <ui/debug_screen.hpp>
#include <render/text.hpp>

#include <input/input.hpp>

namespace ui {


DebugScreen::DebugScreen(engine::Renderer *renderer, engine::Window& window) :
    displayDebug(false)
{
    renderer = renderer;
    versionText = renderer->addText(engine::Text("Minecraft 1.16.1", 0.0f, window.getHeight() - 20));
}


void DebugScreen::update(const engine::Input &input, engine::Window& window) {
    if (input.isKeyDown(engine::Key::F3)) {
        displayDebug = !displayDebug;
    }
    if (window.wasResized()) {
        versionText->setPos(0.0f, window.getHeight() - 20);
    }

}

}  // namespace ui
