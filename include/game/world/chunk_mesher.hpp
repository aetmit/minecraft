#pragma once

#include <render/mesh.hpp>
#include <game/world/chunk.hpp>

namespace game {

class ChunkMesher {
public:
    ChunkMesher() = default;

    engine::MeshData generate(const Chunk &chunk);

private:
    void addPositiveXFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addNegativeXFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addPositiveYFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addNegativeYFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addPositiveZFace(engine::MeshData &data, int x, int y, int z, BlockType block);
    void addNegativeZFace(engine::MeshData &data, int x, int y, int z, BlockType block);

};

} // namespace game