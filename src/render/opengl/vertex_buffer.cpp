#include <render/opengl/vertex_buffer.hpp>

namespace engine {

VertexBuffer::VertexBuffer(const void *data, std::size_t size): data(data), size(size) {
    glGenBuffers(1, &buffer);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &buffer);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

} // namespace engine