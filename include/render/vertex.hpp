#pragma once

#include <math/vec2.hpp>
#include <math/vec3.hpp>

namespace engine {

struct Vertex {
    math::Vec3 position;
    math::Vec2 uv; 
};

} // namespace engine