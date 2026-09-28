#pragma once

#include <glm/glm.hpp>

namespace engine {

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    glm::mat4 viewMatrix() const;
    glm::mat4 projectionMatrix() const;

    glm::vec3 forward() const;

    glm::vec3 right() const;
    glm::vec3 up() const;

    void setAspectRatio(float aspectRatio);

    glm::vec3 position;

    float yaw;
    float pitch;

private:
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

} // namspace engine