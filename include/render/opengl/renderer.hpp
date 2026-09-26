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
class Renderer : public engine::Renderer {
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
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Left
        8, 9, 10,
        10, 11, 8,

        // Right
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20
    };

    Vertex cubeVertices[24] = {
        // Front (+Z)
        Vertex(-0.5f, -0.5f,  0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, -0.5f,  0.5f, 1.0f, 0.0f),
        Vertex( 0.5f,  0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 0.0f, 1.0f),

        // Back (-Z)
        Vertex( 0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex(-0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 1.0f, 1.0f),
        Vertex( 0.5f,  0.5f, -0.5f, 0.0f, 1.0f),

        // Left (-X)
        Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f),
        Vertex(-0.5f, -0.5f,  0.5f, 1.0f, 0.0f),
        Vertex(-0.5f,  0.5f,  0.5f, 1.0f, 1.0f),
        Vertex(-0.5f,  0.5f, -0.5f, 0.0f, 1.0f),

        // Right (+X)
        Vertex(0.5f, -0.5f,  0.5f, 0.0f, 0.0f),
        Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f),
        Vertex(0.5f,  0.5f, -0.5f, 1.0f, 1.0f),
        Vertex(0.5f,  0.5f,  0.5f, 0.0f, 1.0f),

        // Top (+Y)
        Vertex(-0.5f, 0.5f,  0.5f, 0.0f, 0.0f),
        Vertex( 0.5f, 0.5f,  0.5f, 1.0f, 0.0f),
        Vertex( 0.5f, 0.5f, -0.5f, 1.0f, 1.0f),
        Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f),

        // Bottom (-Y)
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