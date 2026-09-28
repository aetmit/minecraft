#include <render/opengl/mesh.hpp>

#include <cstddef>

namespace engine {

namespace opengl {

Mesh::Mesh(engine::MeshData data) {
    this->data = data;

    vao = std::make_unique<VertexArray>();
    vbo = std::make_unique<VertexBuffer>();
    ebo = std::make_unique<IndexBuffer>();

    bind();

    vbo->setData(data.vertices.data(), data.vertices.size() * sizeof(decltype(data.vertices)::value_type));

    ebo->setData(data.indices.data(), data.indices.size() * sizeof(decltype(data.indices)::value_type));

    VertexLayout layout(0, 3, VertexElementType::Float, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, position)));
    vao->setLayout(layout);
    vao->enableSlot(0);
    VertexLayout uvlayout(1, 2, VertexElementType::Float, false, sizeof(Vertex), reinterpret_cast<const void*>(offsetof(Vertex, uv)));
    vao->setLayout(uvlayout);
    vao->enableSlot(1);
}

void Mesh::bind() const {
    vao->bind();
    vbo->bind();
    ebo->bind();
}

std::size_t Mesh::getIndiciesLen() const {
    return data.indices.size();
}


} // namespace opengl

} // namespace engine