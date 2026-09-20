#pragma once

#include <glad/glad.h>
#include <render/renderer.hpp>
#include <render/opengl/program.hpp>
#include <window/window.hpp>

namespace engine {

class OpenGLRenderer : public Renderer {
public:

    void drawSquare() override;

    void clearScreen() override;

    ~OpenGLRenderer() override;

    explicit OpenGLRenderer(Window *window);

private:
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

    GLuint vbo;
    GLuint vao;

    GLuint ebo;

    OpenGLShaderProgram shaderProgram;
};

} // namespace engine