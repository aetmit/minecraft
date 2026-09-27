#pragma once

#include <window/window.hpp>
#include <render/mesh.hpp>
#include <core/logger.hpp>

namespace engine {

// acts as an abstraction over the rendering backend so calling code does not need to
// care about what the underlying graphgics api is
class Renderer {

public:
    virtual ~Renderer() = default;

    virtual void drawMesh(const Mesh &mesh) = 0;

    // temporary function to test rnedering
    virtual void drawSquare() = 0;

    // abstration over screen clearing
    virtual void clearScreen() = 0;

    // abstraction for updating the projection matrix
    virtual void updateProjection() = 0;

    Renderer(Window *window, Logger &logger);
protected:
    Window *window;

    Logger &logger;
};

} // namespace engine



