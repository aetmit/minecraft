#include <ui/debug_screen.hpp>
#include <render/text.hpp>
#include <input/input.hpp>

#include <cmath>
#include <format>

namespace ui {


DebugScreen::DebugScreen(engine::Renderer *renderer, engine::Window& window, engine::Clock& clock) :
    displayDebug(false),
    clock(clock),
    fpsElapsed(0.0),
    fpsFrames(0)
{
    renderer = renderer;

    // TODO: Hardcoded chunk updates
    versionText = renderer->addText(
        engine::Text(
            "Minecraft 1.16 (0 fps,<none> chunk updates)",
            0.0f, window.getHeight() - 20, 2.0f
        )
    );
}


void DebugScreen::update(const engine::Input &input, engine::Window& window) {
    if (input.wasKeyPressed(engine::Key::F3)) {
        displayDebug = !displayDebug;
    }
    if (window.wasResized()) {
        versionText->setPos(0.0f, window.getHeight() - 20);
    }
    if (displayDebug) {
        versionText->show();
    }
    else {
        versionText->hide();
    }

    const double deltaTime = clock.getDeltaTime();
    if (deltaTime > 0.0) {
        fpsElapsed += deltaTime;
        ++fpsFrames;
    }

    if (fpsElapsed >= 1.0) {
        // Elapse FPS over time so the display will be stable
        const double fps = static_cast<double>(fpsFrames) / fpsElapsed;

        // TODO: Hardcoded chunk updates
        versionText->setText(std::format(
            "Minecraft 1.16 ({} fps,<none> chunk updates)",
            std::round(fps))
        );
        fpsElapsed = 0.0;
        fpsFrames = 0;
    }
}

}  // namespace ui
