#include <render/opengl/texture.hpp>


namespace engine {

namespace opengl {

Texture::Texture(const std::filesystem::path &path): path(path) {

    imgBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgBuffer);

    glBindTexture(GL_TEXTURE_2D, textureId);

    
}

Texture::~Texture() {
    if (imgBuffer) {
        stbi_image_free(imgBuffer);
    }

    glDeleteTextures(1, &textureId);
}

void Texture::bind(GLuint slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace opengl

} // namespace engine