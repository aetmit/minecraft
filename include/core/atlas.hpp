#pragma once

#include <cstdint>
#include <cstddef>

#include <game/world/chunk.hpp>
#include <render/uv.hpp>

namespace tools { 

struct AtlasTile {
    // idk y we efven use uint16 here
    std::uint16_t x;
    std::uint16_t y;
};

class Atlas {
public:
    void generateAtlas();
    static engine::UVCoord getUV(game::BlockType block);

private:
    static constexpr std::size_t blockTypeCount = static_cast<std::size_t>(game::BlockType::Count);

    static constexpr std::array<AtlasTile, blockTypeCount> atlasTiles {{
        {0, 0}, // dirt
        {1, 0}, // stone
    }};
};

} // namespace tools