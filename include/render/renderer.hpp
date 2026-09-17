#pragma once

#include "window/window.hpp"
namespace engine {

// acts as an abstraction over the rendering backend so calling code does not need to
// care about what the underlying graphgics api is
class Renderer {

public:
    virtual ~Renderer() = default;

protected:
    Window window;
};

} // namespace engine



