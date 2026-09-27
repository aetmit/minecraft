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

    void bind() const;

private:
    std::unique_ptr<VertexArray> vao;
    std::unique_ptr<VertexBuffer> vbo;
    std::unique_ptr<IndexBuffer> ibo; 
};

} // namespace opengl

} // namespace engine