#include <render/opengl/mesh.hpp>

namespace engine {

namespace opengl {

void Mesh::bind() const {
    vao->bind();
    vbo->bind();
    ebo->bind();
}

} // namespace opengl

} // namespace engine