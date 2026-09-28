#pragma once

#include <math/glm.hpp>

namespace engine {

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform();
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    glm::mat4 matrix() const;
};

} // namespace engine