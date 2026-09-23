#include <render/opengl/vertex.hpp>

#include <cstdint>
#include <cassert>
namespace engine {

namespace opengl {

Vertex::Vertex(float x, float y, float z): x(x), y(y), z(z) {}

std::size_t Vertex::offsetX() const {
    auto obj = reinterpret_cast<std::uintptr_t>(this);
    auto x = reinterpret_cast<std::uintptr_t>(&this->x);
    std::uintptr_t offset = x - obj;

    return static_cast<std::size_t>(offset);
}

std::size_t Vertex::offsetY() const {
    auto obj = reinterpret_cast<std::uintptr_t>(this);
    auto y = reinterpret_cast<std::uintptr_t>(&this->y);
    std::uintptr_t offset = y - obj;

    return static_cast<std::size_t>(offset);
}

std::size_t Vertex::offsetZ() const {
    auto obj = reinterpret_cast<std::uintptr_t>(this);
    auto z = reinterpret_cast<std::uintptr_t>(&this->z);
    std::uintptr_t offset = z - obj;

    return static_cast<std::size_t>(offset);   
}

} // namespace opengl

} // namespace engine