#include <game/world/chunk_mesher.hpp>

#include <cstdint>

namespace game {

engine::MeshData ChunkMesher::generate(const Chunk &chunk) {

    engine::MeshData data;

    for (int x = 0; x < Chunk::CHUNK_WIDTH; x++) {
        for (int y = 0; y < Chunk::CHUNK_HEIGHT; y++) {
            for (int z = 0; z < Chunk::CHUNK_WIDTH; z++) {
                BlockType block = chunk.block(x, y, z);

                if (block == BlockType::Air) {
                    continue;
                }

                if (x == Chunk::CHUNK_WIDTH - 1 ||
                    chunk.block(x + 1, y, z) == BlockType::Air) {
                    addPositiveXFace(data, x, y, z);
                }

                if (x == 0 ||
                    chunk.block(x - 1, y, z) == BlockType::Air) {
                    addNegativeXFace(data, x, y, z);
                }

                if (y == Chunk::CHUNK_HEIGHT - 1 ||
                    chunk.block(x, y + 1, z) == BlockType::Air) {
                    addPositiveYFace(data, x, y, z);
                }

                if (y == 0 ||
                    chunk.block(x, y - 1, z) == BlockType::Air) {
                    addNegativeYFace(data, x, y, z);
                }

                if (z == Chunk::CHUNK_WIDTH - 1 ||
                    chunk.block(x, y, z + 1) == BlockType::Air) {
                    addPositiveZFace(data, x, y, z);
                }

                if (z == 0 ||
                    chunk.block(x, y, z - 1) == BlockType::Air) {
                    addNegativeZFace(data, x, y, z);
                }
            }
        }
    }

    return data;
}

void ChunkMesher::addPositiveXFace(engine::MeshData &data, int x, int y, int z) {
    data.addQuadIndicies();

    data.addVertex({{x + 1, y, z}, {0.0f, 0.0f}});
    data.addVertex({{x + 1, y + 1, z}, {0.0f, 1.0f}});
    data.addVertex({{x + 1, y + 1, z + 1}, {1.0f, 1.0f}});
    data.addVertex({{x + 1, y, z + 1}, {1.0f, 0.0f}});
}

void ChunkMesher::addNegativeXFace(engine::MeshData &data, int x, int y, int z) {
    data.addQuadIndicies(); 
    
    data.addVertex({{x, y, z + 1}, {0.0f, 0.0f}});
    data.addVertex({{x, y + 1, z + 1}, {0.0f, 1.0f}});
    data.addVertex({{x, y + 1, z}, {1.0f, 1.0f}});
    data.addVertex({{x, y, z}, {1.0f, 0.0f}});
}

void ChunkMesher::addPositiveYFace(engine::MeshData &data, int x, int y, int z) {
    data.addQuadIndicies();

    data.addVertex({{x, y + 1, z}, {0.0f, 0.0f}});
    data.addVertex({{x, y + 1, z + 1}, {0.0f, 1.0f}});
    data.addVertex({{x + 1, y + 1, z + 1}, {1.0f, 1.0f}});
    data.addVertex({{x + 1, y + 1, z}, {1.0f, 0.0f}});
}

void ChunkMesher::addNegativeYFace(engine::MeshData &data, int x, int y, int z) {
    data.addQuadIndicies();

    data.addVertex({{x, y, z + 1}, {0.0f, 0.0f}});
    data.addVertex({{x, y, z}, {0.0f, 1.0f}});
    data.addVertex({{x + 1, y, z}, {1.0f, 1.0f}});
    data.addVertex({{x + 1, y, z + 1}, {1.0f, 0.0f}});
}

void ChunkMesher::addPositiveZFace(engine::MeshData &data, int x, int y, int z) {
    data.addQuadIndicies();
    
    data.addVertex({{x, y, z + 1}, {0.0f, 0.0f}});
    data.addVertex({{x + 1, y, z + 1}, {1.0f, 0.0f}});
    data.addVertex({{x + 1, y + 1, z + 1}, {1.0f, 1.0f}});
    data.addVertex({{x, y + 1, z + 1}, {0.0f, 1.0f}});
}

void ChunkMesher::addNegativeZFace(engine::MeshData &data, int x, int y, int z) {
    data.addQuadIndicies();

    data.addVertex({{x + 1, y, z}, {0.0f, 0.0f}});
    data.addVertex({{x, y, z}, {1.0f, 0.0f}});
    data.addVertex({{x, y + 1, z}, {1.0f, 1.0f}});
    data.addVertex({{x + 1, y + 1, z}, {0.0f, 1.0f}});
}

} // namespace game