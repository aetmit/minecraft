#pragma once

#include <array>

namespace game {

enum class BlockType {
    Dirt,
    Air,
};

class Chunk {
public:
    static constexpr int CHUNK_WIDTH = 16;
    static constexpr int CHUNK_HEIGHT = 256;

    void setDummy();


    BlockType block(unsigned int x, unsigned int y, unsigned int z) const;

private:
    std::array<BlockType, CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT> blocks;

    void setBlock(unsigned int x, unsigned int y, unsigned int z, BlockType block);
};

} // namespace game