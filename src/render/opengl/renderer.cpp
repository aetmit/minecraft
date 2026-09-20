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
    logger.info("Initalising OpenGL renderer");
    
    const std::string vendor =
        std::string("Vendor: ") +
        reinterpret_cast<const char*>(glGetString(GL_VENDOR));

    const std::string renderer =
        std::string("Renderer: ") +
        reinterpret_cast<const char*>(glGetString(GL_RENDERER));

    const std::string version =
        std::string("Version:  ") +
        reinterpret_cast<const char*>(glGetString(GL_VERSION));

    const std::string glsl =
        std::string("GLSL: ") +
        reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

    logger.info(vendor.c_str());
    logger.info(renderer.c_str());
    logger.info(version.c_str());
    logger.info(glsl.c_str());

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

    logger.info("Initialised OpenGL renderer successfully");
}

} // namespace engine
