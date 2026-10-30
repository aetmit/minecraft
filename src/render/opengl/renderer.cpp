#include <render/opengl/renderer.hpp>

#include <stdexcept>
#include <sstream>

#include <glad/glad.h>

#include <math/glm.hpp>
#include <render/opengl/mesh.hpp>

namespace engine {

namespace opengl {

void Renderer::drawMesh(const engine::Mesh &mesh, Transform transform) {
    auto &glMesh = dynamic_cast<const engine::opengl::Mesh&>(mesh);

    glMesh.bind();
    shaderProgram->bind();
    texture->bind();

    clearErrors();
    auto view = camera->viewMatrix();
    shaderProgram->setUniformMat4("uView", view);
    checkErrors();

    clearErrors();
    auto model = transform.matrix();
    shaderProgram->setUniformMat4("uModel", model); 
    checkErrors();

    clearErrors();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(glMesh.getIndiciesLen()), GL_UNSIGNED_INT, nullptr);
    checkErrors();

    textShader->bind();
    for (auto& text : texts) {
        clearErrors();
        text.render(*textShader, window->getWidth(), window->getHeight());
        checkErrors();
    }

}

Renderer::~Renderer() {
    logger.info("Shutdown OpenGL renderer successfully");
}

void Renderer::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Renderer::Renderer(Window *window, Logger &logger) :
    engine::Renderer(window, logger)
{
    logger.info("Initalising OpenGL renderer");

    window->makeContextCurrent();

    logger.info("Loading OpenGL via GLAD");
    if (!gladLoadGL()) {
        throw std::runtime_error("failed to load GLAD");
    }
    logger.info("Sucessfully loaded OpenGL");

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);

    shaderProgram = std::make_unique<Shader>(window, logger);
    shaderProgram->compileShader("assets/shaders/solid.vert", ShaderType::Vertex);
    shaderProgram->compileShader("assets/shaders/solid.frag", ShaderType::Fragment);

    textShader = std::make_unique<Shader>(window, logger);
    textShader->compileShader("assets/shaders/text.vert", ShaderType::Vertex);
    textShader->compileShader("assets/shaders/text.frag", ShaderType::Fragment);

    asciiFonts = std::make_unique<Texture>("assets/fonts/ascii.png");


    shaderProgram->link();
    textShader->link();
    
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

    texture = std::make_unique<Texture>("assets/textures/dirt.png");

    shaderProgram->bind();

    texture->bind();
    clearErrors();
    shaderProgram->setUniform1i("uTexture", 0);
    checkErrors();

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

void Renderer::updateProjection() {
    camera->setAspectRatio(window->aspectRatio());
    auto projection = camera->projectionMatrix();

    shaderProgram->bind();
    shaderProgram->setUniformMat4("uProjection", projection);
}

std::unique_ptr<engine::Mesh> Renderer::createMesh(engine::MeshData data) {
    return std::make_unique<engine::opengl::Mesh>(std::move(data));
}

void Renderer::setCamera(Camera *camera) {
    this->camera = camera;
    updateProjection();
}

void Renderer::addText(Text& text) {
    texts.push_back(std::move(text));
    texts.back().engineInit(*asciiFonts);
}

} // namespace opengl

} // namespace engine
