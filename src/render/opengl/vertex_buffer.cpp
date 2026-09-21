#include <render/opengl/vertex_buffer.hpp>

namespace engine {

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &buffer);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &buffer);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// expected the buffer to be bound
void VertexBuffer::setData(const void *data, std::size_t size) const {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

} // namespace engine