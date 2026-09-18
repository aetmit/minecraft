#include <render/opengl/renderer.hpp>

#include <stdexcept>
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

OpenGLRenderer::OpenGLRenderer(Window *window): Renderer(window) {
    window->makeContextCurrent();

    if (!gladLoadGL()) {
        throw std::runtime_error("failed to load glad");
    }
}

} // namespace engine