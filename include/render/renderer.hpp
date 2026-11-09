#pragma once

#include <memory>

#include <render/text.hpp>
#include <window/window.hpp>
#include <render/mesh.hpp>
#include <core/logger.hpp>
#include <core/transform.hpp>
#include <camera/camera.hpp>

namespace engine {

// acts as an abstraction over the rendering backend so calling code does not need to
// care about what the underlying graphgics api is
class Renderer {

public:
    virtual ~Renderer() = default;

    virtual void drawMesh(const Mesh &mesh, Transform transform) = 0;

    // abstration over screen clearing
    virtual void clearScreen() = 0;

    // abstraction for updating the projection matrix
    virtual void updateProjection() = 0;

    virtual std::unique_ptr<Mesh> createMesh(MeshData data) = 0;

    virtual void setCamera(Camera *camera) = 0;

    virtual Text* addText(Text& text) = 0;

    virtual Text* addText(Text&& text) = 0;

    Renderer(Window *window, Logger &logger);
protected:
    Window *window;

    Logger &logger;
};

} // namespace engine
