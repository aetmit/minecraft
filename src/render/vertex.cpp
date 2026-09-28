#include <render/vertex.hpp>

namespace engine {

Vertex::Vertex(math::Vec3 position, math::Vec2 uv): position(position), uv(uv) {}

Vertex::Vertex(float x, float y, float z, float u, float v): position(x, y, z), uv(u, v) {}


} // namespace engine