#pragma once

#include "render/renderer.hpp"

namespace engine {

class OpenGLRenderer : public Renderer {
public:

    void drawTriangle() override;

    void clearScreen() override;

    ~OpenGLRenderer() override;
};

} // namespace engine