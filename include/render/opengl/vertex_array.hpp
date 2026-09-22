#pragma once

#include <glad/glad.h>

#include <render/opengl/vertex_buffer.hpp>

namespace engine {

struct VertexLayout {

};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();


    void bind() const;
    void unbind() const;

    void setLayout(const VertexBuffer &buffer);

    void enableSlot(GLuint slot);

private:
    GLuint vao;
};

} // namespace engine