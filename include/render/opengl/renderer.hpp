#pragma once

#include <memory>

#include <glad/glad.h>

#include <render/renderer.hpp>
#include <render/opengl/shader.hpp>
#include <render/opengl/vertex_buffer.hpp>
#include <render/opengl/index_buffer.hpp>
#include <render/opengl/texture.hpp>
#include <render/opengl/vertex_array.hpp>
#include <render/opengl/vertex.hpp>
#include <window/window.hpp>
#include <core/logger.hpp>

namespace engine {

namespace opengl {
class Renderer : public engine::Renderer {
public:
    void drawSquare() override;

    void clearScreen() override;

    ~Renderer() override;

    Renderer(Window *window, Logger &logger);

private:

    void clearErrors();
    void checkErrors();

    Vertex squareVertices[4] = {
        Vertex(-0.5f, -0.5f, -5.0f, 0.0f, 0.0f),
        Vertex(0.5f, -0.5f, -5.0f, 1.0f, 0.0f),
        Vertex(0.5f,  0.5f, -5.0f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -5.0f, 0.0f, 1.0f),
    };

    GLuint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    // we use pointers here because we need runtime initalisation
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<VertexArray> vao;

    std::unique_ptr<IndexBuffer> ibo;

    std::unique_ptr<Shader> shaderProgram;

    std::unique_ptr<Texture> texture;
};

} // namespace opengl

} // namespace engine