#include <render/opengl/renderer.hpp>

#include <stdexcept>
#include <sstream>

#include <glad/glad.h>


namespace engine {

namespace opengl {

void Renderer::drawSquare() {

    shaderProgram->bind();

    vao->bind();
    texture->bind();

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

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    shaderProgram = std::make_unique<Shader>(window, logger);
    shaderProgram->compileShader("assets/shaders/basic.vert", ShaderType::Vertex);
    shaderProgram->compileShader("assets/shaders/basic.frag", ShaderType::Fragment);

    shaderProgram->link();
    
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

    texture = std::make_unique<Texture>("assets/textures/dirt.png");

    texture->bind();
    shaderProgram->setUniform1i("uTexture", 0);

    vao->bind();

    vbo->bind();
    vbo->setData(squareVertices, sizeof(squareVertices));


    ibo->bind();
    ibo->setData(indices, sizeof(indices));

    // Specifies how OpenGL interprets vertex data
    VertexLayout layout(0, 3, VertexElementType::Float, false, sizeof(Vertex), static_cast<const void*>(0));
    vao->setLayout(layout);
    vao->enableSlot(0);
    VertexLayout uvlayout(1, 2, VertexElementType::Float, false, 2 * sizeof(Vertex), reinterpret_cast<const void*>(squareVertices[0].offsetU()));
    vao->setLayout(uvlayout);
    vao->enableSlot(1);

    

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
