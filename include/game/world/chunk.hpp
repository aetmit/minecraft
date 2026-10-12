#pragma once

#include <array>
#include <cstddef>

namespace game {

enum class BlockType : std::size_t {
    Dirt,
    Air,
    Stone,

    Count, // must be last variant in this enum or else stuff gonna break
};

class Chunk {
public:
    static constexpr int CHUNK_WIDTH = 16;
    static constexpr int CHUNK_HEIGHT = 256;

    long long chunkX = 0;
    long long chunkZ = 0;

    void setDummy(long long x_, long long z_);


    BlockType block(unsigned int x, unsigned int y, unsigned int z) const;

private:
    std::array<BlockType, CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT> blocks;

    void setBlock(unsigned int x, unsigned int y, unsigned int z, BlockType block);
};

} // namespace game