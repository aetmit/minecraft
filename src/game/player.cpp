#include <game/player.hpp>

#include <glm/glm.hpp>

namespace game {

Player::Player(float aspectRatio): camera(70.0f, aspectRatio, 0.1f, 1000.0f), sensitivity(0.1f), moveSpeed(5.0f) {
    camera.position = glm::vec3(0.0f, 0.0f, 3.0f);
}

void Player::update(float deltaTime, const engine::Input &input) {
    float xOffset = static_cast<float>(input.mouseDeltaX()) * sensitivity;
    float yOffset = static_cast<float>(input.mouseDeltaY()) * sensitivity;

    camera.yaw += xOffset;
    camera.pitch -= yOffset;

    // clamping
    if (camera.pitch > 89.0f) {
        camera.pitch = 89.0f; 
    }

    if (camera.pitch < -89.0f) {
        camera.pitch = -89.0f;
    }

    float speed = deltaTime * moveSpeed;

    if (input.isKeyDown(engine::Key::LeftControl)) {
        speed *= 2.0f;
    }

    if (input.isKeyDown(engine::Key::W)) {
        camera.position += camera.forward() * speed;
    }
    if (input.isKeyDown(engine::Key::S)) {
        camera.position -= camera.forward() * speed;
    }
    if (input.isKeyDown(engine::Key::A)) {
        camera.position -= camera.right() * speed;
    }
    if (input.isKeyDown(engine::Key::D)) {
        camera.position += camera.right() * speed;
    }
    if (input.isKeyDown(engine::Key::Space)) {
        camera.position += glm::vec3(0.0f, 1.0f, 0.0f) * speed; 
    }
    if (input.isKeyDown(engine::Key::LeftShift)) {
        camera.position -= glm::vec3(0.0f, 1.0f, 0.0f) * speed; 
    }
}

const engine::Camera &Player::getCamera() const {
    return camera;
}
engine::Camera &Player::getCamera() {
    return camera;
}

} // namespace game