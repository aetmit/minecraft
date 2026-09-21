#pragma once

#include <memory>

#include <glad/glad.h>

#include <render/renderer.hpp>
#include <render/opengl/program.hpp>
#include <render/opengl/vertex_buffer.hpp>
#include <render/opengl/index_buffer.hpp>
#include <window/window.hpp>
#include <core/logger.hpp>

namespace engine {

class OpenGLRenderer : public Renderer {
public:
    void drawSquare() override;

    void clearScreen() override;

    ~OpenGLRenderer() override;

    explicit OpenGLRenderer(Window *window, Logger &logger);

private:

    void clearErrors();
    void checkErrors();

    float squareVertices[12] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    GLuint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    // we have to use a pointer here because we need to ininitialise glad before constructing vbo
    std::unique_ptr<VertexBuffer> vbo;
    GLuint vao;

    std::unique_ptr<IndexBuffer> ibo;

    std::unique_ptr<OpenGLShaderProgram> shaderProgram;
};

} // namespace engine