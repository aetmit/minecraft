#include <render/mesh.hpp>


namespace engine {

void MeshData::addIndex(std::uint32_t index) {
    indices.push_back(index);
}

void MeshData::addVertex(Vertex vertex) {
    vertices.push_back(vertex);
}

void MeshData::addQuadIndicies() {
    const std::uint32_t base = vertices.size();

    addIndex(base + 0);
    addIndex(base + 1);
    addIndex(base + 2);

    addIndex(base + 2);
    addIndex(base + 3);
    addIndex(base + 0);
}

} // namespace engine