#pragma once

#include <filesystem>

#include <glad/glad.h>

namespace engine {

class Texture {

public:
    Texture(const std::filesystem::path &path);
    ~Texture();

    void bind(GLuint slot = 0);
};

} // namespace engine