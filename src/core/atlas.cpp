#include <core/atlas.hpp>

#include <cstdint>

#include <stbi/stb_image_write.h>

namespace tools {

void AtlasGenerator::generateAtlas() {
    constexpr int height = 1024;
    constexpr int width = 1024;
    constexpr int channels = 4;

    std::uint8_t pixels[height * width * channels] {};

    stbi_write_png("atlas.png", width, height, channels, pixels, width * channels);
}

} // namespace tools