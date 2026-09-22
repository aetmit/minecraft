#include <render/opengl/vertex.hpp>

namespace engine {

Vertex::Vertex(float x, float y, float z): x(x), y(y), z(z) {}

std::size_t Vertex::offsetX() const {
    return offsetof(Vertex, x);
}

std::size_t Vertex::offsetY() const {
    return offsetof(Vertex, y);
}

std::size_t Vertex::offsetZ() const {
    return offsetof(Vertex, z);
}

} // namespace engine