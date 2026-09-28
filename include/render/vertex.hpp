#pragma once

#include <math/vec2.hpp>
#include <math/vec3.hpp>

namespace engine {

struct Vertex final {
    math::Vec3 position;
    math::Vec2 uv; 

    Vertex() = default;
    Vertex(math::Vec3 position, math::Vec2 uv);

    // temporary api
    Vertex(float x, float y, float z, float u, float v);
};

} // namespace engine