#include <render/vertex.hpp>

namespace engine {

Vertex::Vertex(glm::vec3 position, glm::vec2 uv): position(position), uv(uv) {}

Vertex::Vertex(float x, float y, float z, float u, float v): position(x, y, z), uv(u, v) {}


} // namespace engine