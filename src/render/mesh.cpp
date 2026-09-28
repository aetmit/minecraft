#include <render/mesh.hpp>


namespace engine {

void MeshData::addIndex(std::uint32_t index) {
    indices.push_back(index);
}

void MeshData::addVertex(Vertex vertex) {
    vertices.push_back(vertex);
}

} // namespace engine