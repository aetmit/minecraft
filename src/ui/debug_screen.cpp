#include <ui/debug_screen.hpp>
#include <render/text.hpp>
#include <input/input.hpp>

#include <cmath>
#include <format>
#include <string>

namespace ui {


DebugScreen::DebugScreen(engine::Renderer *renderer, engine::Window& window, engine::Clock& clock) :
    displayDebug(false),
    clock(clock),
    fpsElapsed(0.0),
    fpsFrames(0)
{
    renderer = renderer;

    leftPanelText = std::string("Minecraft 1.16 (1.16/vanilla)\n")
        + "{} fps";


    leftPanel = renderer->addText(
        engine::Text(leftPanelText, 0.0f, window.getHeight() - 20, 2.0f)
    );
}


void DebugScreen::update(const engine::Input &input, engine::Window& window) {
    if (input.wasKeyPressed(engine::Key::F3)) {
        displayDebug = !displayDebug;
    }
    if (window.wasResized()) {
        leftPanel->setPos(0.0f, window.getHeight() - 20);
    }
    if (displayDebug) {
        leftPanel->show();
    }
    else {
        leftPanel->hide();
    }

    const double deltaTime = clock.getDeltaTime();
    if (deltaTime > 0.0) {
        fpsElapsed += deltaTime;
        ++fpsFrames;
    }

    if (fpsElapsed >= 1.0) {
        // Elapse FPS over time so the display will be stable
        const double fps = static_cast<double>(fpsFrames) / fpsElapsed;

        const double roundedFps = std::round(fps);
        leftPanel->setText(std::vformat(leftPanelText, std::make_format_args(roundedFps)));
        fpsElapsed = 0.0;
        fpsFrames = 0;
    }
}

}  // namespace ui
