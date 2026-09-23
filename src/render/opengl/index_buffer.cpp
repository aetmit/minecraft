#include <render/opengl/index_buffer.hpp>

#include <glad/glad.h>

namespace engine {

namespace opengl {

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &buffer);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &buffer);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::setData(const void *data, std::size_t size) const {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

} // namespace opengl

} // namespace engine