#include "renderer.hpp"

#include <glad/glad.h>

namespace engine {

void OpenGLRenderer::drawTriangle() {
    // TODO: draw a triangle
}

OpenGLRenderer::~OpenGLRenderer() {
    // delete resources that were acquired in the constructor
}

void OpenGLRenderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace engine