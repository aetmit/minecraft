#include <game/world/chunk_mesher.hpp>

#include <cstdint>

#include <core/atlas.hpp>

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
                    addPositiveXFace(data, x, y, z, block);
                }

                if (x == 0 ||
                    chunk.block(x - 1, y, z) == BlockType::Air) {
                    addNegativeXFace(data, x, y, z, block);
                }

                if (y == Chunk::CHUNK_HEIGHT - 1 ||
                    chunk.block(x, y + 1, z) == BlockType::Air) {
                    addPositiveYFace(data, x, y, z, block);
                }

                if (y == 0 ||
                    chunk.block(x, y - 1, z) == BlockType::Air) {
                    addNegativeYFace(data, x, y, z, block);
                }

                if (z == Chunk::CHUNK_WIDTH - 1 ||
                    chunk.block(x, y, z + 1) == BlockType::Air) {
                    addPositiveZFace(data, x, y, z, block);
                }

                if (z == 0 ||
                    chunk.block(x, y, z - 1) == BlockType::Air) {
                    addNegativeZFace(data, x, y, z, block);
                }
            }
        }
    }

    return data;
}

void ChunkMesher::addPositiveXFace(engine::MeshData &data, int x, int y, int z, BlockType type) {
    engine::UVCoord uv = tools::Atlas::getUV(type);
    data.addQuadIndicies();

    data.addVertex({{x + 1, y, z}, {uv.uMin, uv.vMin}});
    data.addVertex({{x + 1, y, z + 1}, {uv.uMax, uv.vMin}});
    data.addVertex({{x + 1, y + 1, z + 1}, {uv.uMax, uv.vMax}});
    data.addVertex({{x + 1, y + 1, z}, {uv.uMin, uv.vMax}});
}

void ChunkMesher::addNegativeXFace(engine::MeshData &data, int x, int y, int z, BlockType type) {
    engine::UVCoord uv = tools::Atlas::getUV(type);
    data.addQuadIndicies(); 
    
    data.addVertex({{x, y, z + 1}, {uv.uMin, uv.vMin}});
    data.addVertex({{x, y + 1, z + 1}, {uv.uMin, uv.vMax}});
    data.addVertex({{x, y + 1, z}, {uv.uMax, uv.vMax}});
    data.addVertex({{x, y, z}, {uv.uMax, uv.vMin}});
}

void ChunkMesher::addPositiveYFace(engine::MeshData &data, int x, int y, int z, BlockType type) {
    engine::UVCoord uv = tools::Atlas::getUV(type);
    data.addQuadIndicies();

    data.addVertex({{x, y + 1, z}, {uv.uMin, uv.vMin}});
    data.addVertex({{x, y + 1, z + 1}, {uv.uMin, uv.vMax}});
    data.addVertex({{x + 1, y + 1, z + 1}, {uv.uMax, uv.vMax}});
    data.addVertex({{x + 1, y + 1, z}, {uv.uMax, uv.vMin}});
}

void ChunkMesher::addNegativeYFace(engine::MeshData &data, int x, int y, int z, BlockType type) {
    engine::UVCoord uv = tools::Atlas::getUV(type);
    data.addQuadIndicies();

    data.addVertex({{x, y, z + 1}, {uv.uMin, uv.vMin}});
    data.addVertex({{x, y, z}, {uv.uMin, uv.vMax}});
    data.addVertex({{x + 1, y, z}, {uv.uMax, uv.vMax}});
    data.addVertex({{x + 1, y, z + 1}, {uv.uMax, uv.vMin}});
}

void ChunkMesher::addPositiveZFace(engine::MeshData &data, int x, int y, int z, BlockType type) {
    engine::UVCoord uv = tools::Atlas::getUV(type);
    data.addQuadIndicies();
    
    data.addVertex({{x, y, z + 1}, {uv.uMin, uv.vMin}});
    data.addVertex({{x + 1, y, z + 1}, {uv.uMax, uv.vMin}});
    data.addVertex({{x + 1, y + 1, z + 1}, {uv.uMax, uv.vMax}});
    data.addVertex({{x, y + 1, z + 1}, {uv.uMin, uv.vMax}});
}

void ChunkMesher::addNegativeZFace(engine::MeshData &data, int x, int y, int z, BlockType type) {
    engine::UVCoord uv = tools::Atlas::getUV(type);
    data.addQuadIndicies();

    data.addVertex({{x + 1, y, z}, {uv.uMin, uv.vMin}});
    data.addVertex({{x, y, z}, {uv.uMax, uv.vMin}});
    data.addVertex({{x, y + 1, z}, {uv.uMax, uv.vMax}});
    data.addVertex({{x + 1, y + 1, z}, {uv.uMin, uv.vMax}});
}
} // namespace game