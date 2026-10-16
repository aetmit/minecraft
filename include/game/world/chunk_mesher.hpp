#pragma once

#include <core/logger.hpp>
#include <render/mesh.hpp>
#include <game/world/chunk.hpp>

namespace game {

class ChunkMesher {
public:
    ChunkMesher(engine::Logger& logger);

    engine::MeshData generate(
        const Chunk &chunk,
        const Chunk* positiveX = nullptr,
        const Chunk* negativeX = nullptr,
        const Chunk* positiveZ = nullptr,
        const Chunk* negativeZ = nullptr);

private:
    engine::Logger& logger;

    void addPositiveXFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addNegativeXFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addPositiveYFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addNegativeYFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addPositiveZFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addNegativeZFace(engine::MeshData &data, int x, int y, int z, BlockType block);

};

} // namespace game