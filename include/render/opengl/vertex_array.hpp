#pragma once

#include <cstdint>

#include <glad/glad.h>

#include <render/opengl/vertex_buffer.hpp>

namespace engine {

enum class VertexElementType : GLenum {
    Float = GL_FLOAT,
};

struct VertexLayout {
    GLuint index;
    GLuint elementCount;
    VertexElementType type;
    bool normalised;
    std::int32_t stride;
    const void *offset;

    VertexLayout(
        GLuint index,
        GLuint elementCount,
        VertexElementType type,
        bool normalised,
        std::int32_t stride,
        const void *offset
    );
};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();


    void bind() const;
    void unbind() const;

    void setLayout(const VertexLayout &layout);

    void enableSlot(GLuint index);

private:
    GLuint vao;
};

} // namespace engine