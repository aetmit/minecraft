#pragma once

#include <glad/glad.h>
#include <render/renderer.hpp>
#include <render/opengl/program.hpp>
#include <window/window.hpp>

namespace engine {

class OpenGLRenderer : public Renderer {
public:

    void drawTriangle() override;

    void clearScreen() override;

    ~OpenGLRenderer() override;

    explicit OpenGLRenderer(Window *window);

private:
    float triangleVertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    GLuint vbo;

    GLuint vao;

    OpenGLShaderProgram shaderProgram;
};

} // namespace engine