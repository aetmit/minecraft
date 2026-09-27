#pragma once

#include <memory>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <render/renderer.hpp>
#include <render/opengl/shader.hpp>
#include <render/opengl/vertex_buffer.hpp>
#include <render/opengl/index_buffer.hpp>
#include <render/opengl/texture.hpp>
#include <render/opengl/vertex_array.hpp>
#include <render/opengl/vertex.hpp>
#include <camera/camera.hpp>
#include <window/window.hpp>
#include <core/logger.hpp>

namespace engine {

namespace opengl {
class Renderer final : public engine::Renderer {
public:
    void drawSquare() override;

    void clearScreen() override;

    ~Renderer() override;

    Renderer(Window *window, Logger &logger);


    void updateProjection() override;

private:

    void clearErrors();
    void checkErrors();



   GLuint cubeIndices[36] = {
        0, 1, 2, 2, 3, 0,

        4, 7, 6, 6, 5, 4,

        8, 11, 10, 10, 9, 8,

        12, 13, 14, 14, 15, 12,

        16, 17, 18, 18, 19, 16,

        20, 23, 22, 22, 21, 20
    };

    Vertex cubeVertices[24] = {
        Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, -0.5f,  0.5f, 1.0f, 0.0f),
        Vertex( 0.5f,  0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 0.0f, 1.0f),

        Vertex( 0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 1.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f, 0.0f, 1.0f),

        Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 0.0f, 1.0f),

        // Right (+X)
        Vertex(0.5f, -0.5f,  0.5f, 0.0f, 0.0f),
        Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f, 1.0f, 1.0f),
        Vertex(0.5f,  0.5f,  0.5f, 0.0f, 1.0f),

        Vertex(-0.5f, 0.5f,  0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, 0.5f,  0.5f, 1.0f, 0.0f),
        Vertex( 0.5f, 0.5f, -0.5f, 1.0f, 1.0f),
        Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f),

        Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex( 0.5f, -0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 1.0f),
    };


    std::unique_ptr<Camera> camera;
    
    glm::mat4 model;

    // we use pointers here because we need runtime initalisation
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<VertexArray> vao;

    std::unique_ptr<IndexBuffer> ibo;

    std::unique_ptr<Shader> shaderProgram;

    std::unique_ptr<Texture> texture;
};

} // namespace opengl

} // namespace engine