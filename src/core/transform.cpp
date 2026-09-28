#include <core/transform.hpp>

namespace engine {

Transform::Transform(): position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale): position(position), rotation(rotation), scale(scale) {}

glm::mat4 Transform::matrix() const {
    glm::mat4 mat = glm::mat4(1.0f);

    mat = glm::translate(mat, position);
    
    mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    mat = glm::scale(mat, scale);
    
    return mat;
}

} // namespace engine