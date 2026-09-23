#include <render/opengl/renderer.hpp>

#include <stdexcept>
#include <sstream>

#include <glad/glad.h>

#include <render/opengl/texture.hpp>


namespace engine {

namespace opengl {

void Renderer::drawSquare() {

    shaderProgram->bind();

    int location = glGetUniformLocation(shaderProgram->getProgram(), "uColour");
    if (location == -1) {
        logger.error("Failed to find shader uniform");
    }
    glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f);

    vao->bind();

    clearErrors();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    checkErrors();
}

Renderer::~Renderer() {
    logger.info("Shutdown OpenGL renderer successfully");
}

void Renderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

Renderer::Renderer(Window *window, Logger &logger): engine::Renderer(window, logger) {
    logger.info("Initalising OpenGL renderer");

    window->makeContextCurrent();

    logger.info("Loading OpenGL via GLAD");
    if (!gladLoadGL()) {
        throw std::runtime_error("failed to load GLAD");
    }
    logger.info("Sucessfully loaded OpenGL");

    shaderProgram = std::make_unique<ShaderProgram>(window);
    
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

    vao = std::make_unique<VertexArray>();
    vbo = std::make_unique<VertexBuffer>();
    ibo = std::make_unique<IndexBuffer>();

    Texture texture("assets/textures/dirt.png");
    texture.bind();

    vao->bind();

    vbo->bind();
    vbo->setData(squareVertices, sizeof(squareVertices));


    ibo->bind();
    ibo->setData(indices, sizeof(indices));

    // Specifies how OpenGL interprets vertex data
    VertexLayout layout(0, 3, VertexElementType::Float, false, 3 * sizeof(float), static_cast<const void*>(0));
    vao->setLayout(layout);
    vao->enableSlot(0);

    shaderProgram->compileShader("assets/shaders/basic.vert", ShaderType::Vertex);
    shaderProgram->compileShader("assets/shaders/basic.frag", ShaderType::Fragment);

    shaderProgram->link();

    logger.info("Initialised OpenGL renderer successfully");
}

void Renderer::clearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

void Renderer::checkErrors() {
    while (GLenum error = glGetError()) {
        std::stringstream ss;
        ss << "OpenGL internal error (code = " << error << ")";
        logger.error(ss.str().c_str());
    }
}

} // namespace opengl

} // namespace engine
