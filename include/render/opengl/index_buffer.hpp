#pragma once

#include <cstddef>

#include <render/opengl/buffer.hpp>

namespace engine {

class IndexBuffer : public Buffer {
public:
    IndexBuffer();
    ~IndexBuffer() override;

    void setData(const void *data, std::size_t size) const override;
    void bind() const override;
    void unbind() const override;
};

} // namespace engine