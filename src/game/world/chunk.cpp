#include <game/world/chunk.hpp>

namespace game {

BlockType Chunk::block(unsigned int x, unsigned int y, unsigned int z) const {
    return blocks[x + CHUNK_WIDTH * (z + CHUNK_WIDTH * y)];
}

void Chunk::setBlock(unsigned int x, unsigned int y, unsigned int z, BlockType block) {
    blocks[x + CHUNK_WIDTH * (z + CHUNK_WIDTH * y)] = block;
}

void Chunk::setDummy() {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 256; y++) {
            for (int z = 0; z < 16; z++) {
                if (y == 64) {
                    setBlock(x, y, z, BlockType::Dirt);
                } else {
                    setBlock(x, y, z, BlockType::Air);
                }
            }
        }
    }
}
    
} // namespace game