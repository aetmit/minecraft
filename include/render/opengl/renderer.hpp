#pragma once

#include <glad/glad.h>
#include <render/renderer.hpp>
#include <render/opengl/program.hpp>
#include <render/opengl/vertex_buffer.hpp>
#include <window/window.hpp>
#include <core/logger.hpp>

namespace engine {

class OpenGLRenderer : public Renderer {
public:
    // must be called before creating first instance of OPengL rendere
    static void loadOpenGL(Logger &logger);

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

    VertexBuffer vbo;
    GLuint vao;

    GLuint ebo;

    OpenGLShaderProgram shaderProgram;
};

} // namespace engine