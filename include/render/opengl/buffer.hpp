#pragma once


#include <cstddef>

#include <glad/glad.h>

namespace engine {

namespace opengl {

class Buffer {

public:
    virtual ~Buffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void setData(const void *data, std::size_t size) const = 0;

protected:

    GLuint buffer;

};

} // namespace opengl

} // namespace engine