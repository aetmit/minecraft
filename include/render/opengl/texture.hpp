#pragma once

#include <filesystem>

#include <glad/glad.h>
#include <stbi/stb_image.h>

namespace engine {

namespace opengl {

class Texture {

public:
    Texture(const std::filesystem::path &path);
    ~Texture();

    void bind(GLuint slot = 0) const;
    void unbind();

private:
    int width{0};
    int height{0};
    // bits per pixel
    int bpp{0};

    stbi_uc *imgBuffer{nullptr}; 

    GLuint textureId{0};

    std::filesystem::path path;
};

} // namespace engine

} // namespace engine