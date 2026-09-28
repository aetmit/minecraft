#pragma once

#include <memory>

#include <render/mesh.hpp>
#include <render/opengl/vertex_array.hpp>
#include <render/opengl/vertex_buffer.hpp>
#include <render/opengl/index_buffer.hpp>


namespace engine {

namespace opengl {

class Mesh final : public engine::Mesh {
public:
    Mesh(engine::MeshData data);

    void bind() const;

private:
    engine::MeshData data;

    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<IndexBuffer> ebo; 
};

} // namespace opengl

} // namespace engine