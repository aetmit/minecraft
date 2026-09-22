#include <render/opengl/vertex_array.hpp>

namespace engine {

VertexArray::VertexArray() {
    glGenVertexArrays(1, &vao);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind() const {
    glBindVertexArray(vao);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::enableSlot(GLuint slot) {
    glEnableVertexAttribArray(slot);
}

} // namespac engine