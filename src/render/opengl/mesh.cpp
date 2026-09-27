#include <render/opengl/mesh.hpp>

namespace engine {

namespace opengl {

void Mesh::bind() const {
    vao->bind();
    vbo->bind();
    ibo->bind();
}

} // namespace opengl

} // namespace engine