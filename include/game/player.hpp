#pragma once

#include <input/input.hpp>
#include <camera/camera.hpp>

namespace game {

class Player {
public:
    Player(float aspectRatio);

    void update(float deltaTime, const engine::Input &input);

    const engine::Camera &getCamera() const;
    engine::Camera &getCamera();

private:
    engine::Camera camera;

    float sensitivity;
    float moveSpeed;
};

} // namespace game