#pragma once

#include <window/window.hpp>
namespace engine {

// acts as an abstraction over the rendering backend so calling code does not need to
// care about what the underlying graphgics api is
class Renderer {

public:
    virtual ~Renderer() = default;


    // temporary function to test rnedering
    virtual void drawTriangle() = 0;

    // abstration over screen clearing
    virtual void clearScreen() = 0;

    Renderer(Window *window);
protected:
    Window *window;
};

} // namespace engine



