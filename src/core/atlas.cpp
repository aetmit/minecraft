#include <core/atlas.hpp>

#include <filesystem>
#include <stdexcept>
#include <string>
#include <cstdint>

#include <stbi/stb_image_write.h>
#include <stbi/stb_image.h>

namespace tools {

void Atlas::generateAtlas() {
    constexpr int atlasHeight = 1024;
    constexpr int atlasWidth = 1024;
    constexpr int channels = 4;
    constexpr int tileSize = 16;
    constexpr int tilesPerRow = atlasWidth / tileSize;


    std::uint8_t pixels[atlasHeight * atlasWidth * channels] {};

    int tileIndex = 0;

    for (const auto &entry : std::filesystem::directory_iterator("assets/textures")) {
        if (!entry.is_regular_file() || entry.path().extension() != ".png" || entry.path().filename() == "atlas.png") {
            continue;
        }

        const std::string path = entry.path().string();

        int width;
        int height;
        int sourceChannels;

        std::uint8_t *source = stbi_load(path.c_str(), &width, &height, &sourceChannels, channels);

        if (!source) {
            throw std::runtime_error("Failed to load texture: " + path);
        }

        if (width != tileSize || height != tileSize) {
            stbi_image_free(source);

            throw std::runtime_error("Texture is not 16x16: " + path);
        }

        const int tileX = (tileIndex % tilesPerRow) * tileSize;
        const int tileY = (tileIndex / tilesPerRow) * tileSize;

        for (int y = 0; y < tileSize; ++y) {
            for (int x = 0; x < tileSize; ++x) {
                const int sourceIndex =
                    (y * tileSize + x) * channels;

                const int atlasIndex =
                    ((tileY + y) * atlasWidth + (tileX + x)) * channels;

                for (int c = 0; c < channels; ++c) {
                    pixels[atlasIndex + c] = source[sourceIndex + c];
                }
            }
        }

        stbi_image_free(source);

        tileIndex++;
    }

    stbi_write_png("assets/textures/atlas.png", atlasWidth, atlasHeight, channels, pixels, atlasWidth * channels);
}

engine::UVCoord Atlas::getUV(game::BlockType block) {
    const AtlasTile tile = atlasTiles[static_cast<std::size_t>(block)];

    constexpr float atlasTilesPerAxis = 64.0f;

    return {tile.x / atlasTilesPerAxis, 1.0f - (tile.y + 1) / atlasTilesPerAxis, (tile.x + 1) / atlasTilesPerAxis, 1.0f - tile.y / atlasTilesPerAxis};
}


} // namespace tools