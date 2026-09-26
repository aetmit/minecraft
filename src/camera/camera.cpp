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

    glm::mat4 view(1.0);

    view = glm::translate(view, -position);
    view = glm::rotate(view, -rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, -rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));


    return view;
}

} // namespace engine