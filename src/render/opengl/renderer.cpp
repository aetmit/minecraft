#include <render/opengl/renderer.hpp>

#include <stdexcept>
#include <sstream>
#include <glad/glad.h>

namespace engine {

void OpenGLRenderer::drawSquare() {

    shaderProgram->use();

    int location = glGetUniformLocation(shaderProgram->getProgram(), "uColour");
    if (location == -1) {
        logger.error("Failed to find shader uniform");
    }
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

    glBindVertexArray(vao);

    clearErrors();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    checkErrors();
}

OpenGLRenderer::~OpenGLRenderer() {
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(1, &vao);
    logger.info("Shutdown OpenGL renderer successfully");
}

void OpenGLRenderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

OpenGLRenderer::OpenGLRenderer(Window *window, Logger &logger): Renderer(window, logger) {
    logger.info("Initalising OpenGL renderer");

    window->makeContextCurrent();

    logger.info("Loading OpenGL via GLAD");
    if (!gladLoadGL()) {
        throw std::runtime_error("failed to load GLAD");
    }
    logger.info("Sucessfully loaded OpenGL");

    shaderProgram = std::make_unique<OpenGLShaderProgram>(window);
    
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

    vbo = std::make_unique<VertexBuffer>();

    vbo->bind();
    vbo->setData(squareVertices, sizeof(squareVertices));

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Specifies how OpenGL interprets vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shaderProgram->compileShader("assets/shaders/basic.vert", OpenGLShaderType::Vertex);
    shaderProgram->compileShader("assets/shaders/basic.frag", OpenGLShaderType::Fragment);

    shaderProgram->link();

    logger.info("Initialised OpenGL renderer successfully");
}

void OpenGLRenderer::clearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

void OpenGLRenderer::checkErrors() {
    while (GLenum error = glGetError()) {
        std::stringstream ss;
        ss << "OpenGL internal error (code = " << error << ")";
        logger.error(ss.str().c_str());
    }
}

} // namespace engine
