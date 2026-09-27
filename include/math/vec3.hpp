#pragma once

namespace engine {

namespace math {

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3() = default;
    Vec3(float x, float y, float z);
};

} // namespace math

} // namespace engine