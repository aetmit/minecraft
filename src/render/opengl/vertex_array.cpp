#include <render/opengl/vertex_array.hpp>

namespace engine {

VertexLayout::VertexLayout(
    GLuint index,
    GLuint elementCount,
    VertexElementType type,
    bool normalised,
    std::int32_t stride,
    const void *offset
): index(index), elementCount(elementCount), type(type), normalised(normalised), stride(stride), offset(offset) {}

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

void VertexArray::enableSlot(GLuint index) {
    glEnableVertexAttribArray(index);
}

void VertexArray::setLayout(const VertexLayout &layout) {
    GLboolean normalised = layout.normalised ? GL_TRUE : GL_FALSE;
    glVertexAttribPointer(
        layout.index, 
        layout.elementCount, 
        static_cast<GLenum>(layout.type), 
        normalised, 
        static_cast<GLsizei>(layout.stride), 
        layout.offset
    );
}

} // namespac engine