#include <render/opengl/renderer.hpp>

#include <stdexcept>
#include <glad/glad.h>

namespace engine {

void OpenGLRenderer::drawTriangle() {

    // Use shader program
    shaderProgram.use();

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    
}

OpenGLRenderer::~OpenGLRenderer() {
    // delete resources that were acquired in the constructor
}

void OpenGLRenderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

OpenGLRenderer::OpenGLRenderer(Window *window): Renderer(window), shaderProgram(window) {

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    // Specifies how OpenGL interprets vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shaderProgram.loadShader("assets/shaders/triangle.vert", OpenGLShaderType::Vertex);
    shaderProgram.loadShader("assets/shaders/triangle.frag", OpenGLShaderType::Fragment);

    shaderProgram.link();
}

} // namespace engine
