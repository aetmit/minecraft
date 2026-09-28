#pragma once

#include <memory>

#include <glad/glad.h>

#include <math/glm.hpp>
#include <render/renderer.hpp>
#include <render/mesh.hpp>
#include <render/opengl/shader.hpp>
#include <render/opengl/vertex_buffer.hpp>
#include <render/opengl/index_buffer.hpp>
#include <render/opengl/texture.hpp>
#include <render/opengl/vertex_array.hpp>
#include <camera/camera.hpp>
#include <window/window.hpp>
#include <core/transform.hpp>
#include <core/logger.hpp>

namespace engine {

namespace opengl {
class Renderer final : public engine::Renderer {
public:

    void drawMesh(const engine::Mesh &mesh, Transform transform) override;

    void clearScreen() override;

    ~Renderer() override;
    Renderer(Window *window, Logger &logger);

    void updateProjection() override;

    std::unique_ptr<engine::Mesh> createMesh(engine::MeshData data) override;

    void setCamera(Camera *camera) override;

private:

    void clearErrors();
    void checkErrors();

    Camera *camera;
    
    // we use pointers here because we need runtime initalisation
    std::unique_ptr<Shader> shaderProgram;

    std::unique_ptr<Texture> texture;
};

} // namespace opengl

} // namespace engine