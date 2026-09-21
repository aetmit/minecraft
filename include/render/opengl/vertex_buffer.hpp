#pragma once

#include <cstddef>

#include <glad/glad.h>

#include <render/opengl/buffer.hpp>

namespace engine {

class VertexBuffer : public Buffer {
public:
    VertexBuffer(const void *data, std::size_t size);
    ~VertexBuffer() override;

    void bind() const override;
    void unbind() const override;

private:
    GLuint buffer;

    const void *data;
    std::size_t size;
};

} // namespace engine