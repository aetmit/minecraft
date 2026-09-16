#ifndef RENDER_RENDERER_HPP
#define RENDER_RENDERER_HPP

namespace engine {
// TODO: provide a generic interface for the game logic to use and then create a subclass that inherits from this api
// so calling code does not need to be concerned with implementation details
class Renderer {

public:
    virtual ~Renderer() = default;
};

} // namespace engine



#endif // RENDER_RENDERER_HPP
