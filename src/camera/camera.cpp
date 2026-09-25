#include <camera/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace engine {

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : position(0.0f), rotation(0.0f), fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane) {}

glm::mat4 Camera::projectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
}

glm::mat4 Camera::viewMatrix() const {
    return glm::translate(
        glm::mat4(1.0f),
        -position
    );
}

} // namespace engine