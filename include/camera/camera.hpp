#pragma once

#include <glm/glm.hpp>

namespace engine {

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    glm::mat4 viewMatrix() const;
    glm::mat4 projectionMatrix() const;

    void setAspectRatio(float aspectRatio);

    glm::vec3 position;
    glm::vec3 rotation;

private:
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

} // namspace engine