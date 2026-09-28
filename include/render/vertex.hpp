#pragma once

#include <math/glm.hpp>
namespace engine {

struct Vertex final {
    glm::vec3 position;
    glm::vec2 uv; 

    Vertex() = default;
    Vertex(glm::vec3 position, glm::vec2 uv);

    // temporary api
    Vertex(float x, float y, float z, float u, float v);
};

} // namespace engine