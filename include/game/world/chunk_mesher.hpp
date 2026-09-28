#pragma once

#include <render/mesh.hpp>
#include <game/world/chunk.hpp>

namespace game {

class ChunkMesher {
public:
    ChunkMesher() = default;

    engine::MeshData generate(const Chunk &chunk);

private:
    void addPositiveXFace(engine::MeshData &data, int x, int y, int z);
    void addNegativeXFace(engine::MeshData &data, int x, int y, int z);
    void addPositiveYFace(engine::MeshData &data, int x, int y, int z);
    void addNegativeYFace(engine::MeshData &data, int x, int y, int z);
    void addPositiveZFace(engine::MeshData &data, int x, int y, int z);
    void addNegativeZFace(engine::MeshData &data, int x, int y, int z);

};

} // namespace game