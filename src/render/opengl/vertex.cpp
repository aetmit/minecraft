#include <render/opengl/vertex.hpp>

#include <cassert>
namespace engine {

namespace opengl {

Vertex::Vertex(float x, float y, float z, float u, float v): x(x), y(y), z(z), u(u), v(v) {}

std::size_t Vertex::offsetX() const {
    std::uintptr_t obj = getThisOffset();
    auto x = reinterpret_cast<std::uintptr_t>(&this->x);
    std::uintptr_t offset = x - obj;

    return static_cast<std::size_t>(offset);
}

std::size_t Vertex::offsetY() const {
    std::uintptr_t obj = getThisOffset();
    auto y = reinterpret_cast<std::uintptr_t>(&this->y);
    std::uintptr_t offset = y - obj;

    return static_cast<std::size_t>(offset);
}

std::size_t Vertex::offsetZ() const {
    std::uintptr_t obj = getThisOffset();
    auto z = reinterpret_cast<std::uintptr_t>(&this->z);
    std::uintptr_t offset = z - obj;

    return static_cast<std::size_t>(offset);   
}

std::size_t Vertex::offsetU() const {
    std::uintptr_t obj = getThisOffset();
    auto u = reinterpret_cast<std::uintptr_t>(&this->u);
    std::uintptr_t offset = u - obj;

    return static_cast<std::size_t>(offset);
}

std::size_t Vertex::offsetV() const {
    std::uintptr_t obj = getThisOffset();
    auto v = reinterpret_cast<std::uintptr_t>(&this->v);
    std::uintptr_t offset = v - obj;

    return static_cast<std::size_t>(offset);
}

std::uintptr_t Vertex::getThisOffset() const {
    return reinterpret_cast<std::uintptr_t>(this);
}

} // namespace opengl

} // namespace engine