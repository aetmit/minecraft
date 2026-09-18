#pragma once

#include <render/renderer.hpp>
#include <window/window.hpp>

namespace engine {

class OpenGLRenderer : public Renderer {
public:

    void drawTriangle() override;

    void clearScreen() override;

    ~OpenGLRenderer() override;

    explicit OpenGLRenderer(Window *window);
};

} // namespace engine