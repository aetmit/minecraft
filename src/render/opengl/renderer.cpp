#include <render/opengl/renderer.hpp>

#include <stdexcept>
#include <glad/glad.h>

namespace engine {

void OpenGLRenderer::drawSquare() {

    // Use shader program
    shaderProgram.use();

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

OpenGLRenderer::~OpenGLRenderer() {
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
}

void OpenGLRenderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

OpenGLRenderer::OpenGLRenderer(Window *window, Logger &logger): Renderer(window, logger), shaderProgram(window) {

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specifies how OpenGL interprets vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shaderProgram.compileShader("assets/shaders/basic.vert", OpenGLShaderType::Vertex);
    shaderProgram.compileShader("assets/shaders/basic.frag", OpenGLShaderType::Fragment);

    shaderProgram.link();
}

} // namespace engine
