#include <game/world/chunk.hpp>

namespace game {

BlockType Chunk::block(unsigned int x, unsigned int y, unsigned int z) const {
    return blocks[x + CHUNK_WIDTH * (z + CHUNK_WIDTH * y)];
}

void Chunk::setBlock(unsigned int x, unsigned int y, unsigned int z, BlockType block) {
    blocks[x + CHUNK_WIDTH * (z + CHUNK_WIDTH * y)] = block;
}

void Chunk::setDummy(long long x_, long long z_) {
    chunkX = x_;
    chunkZ = z_;

    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_HEIGHT; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                if (y < 64) {
                    setBlock(x, y, z, BlockType::Stone);
                } else {
                    setBlock(x, y, z, BlockType::Air);
                }
            }
        }
    }
}
    
} // namespace game