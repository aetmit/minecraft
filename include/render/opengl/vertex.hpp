#pragma once

#include <cstddef>

namespace engine {

namespace opengl {

struct Vertex {

public:
    Vertex(float x, float y,  float z);

    std::size_t offsetX() const;
    std::size_t offsetY() const;
    std::size_t offsetZ() const; 

    float x;
    float y;
    float z;

};

} // namespace opengl

} // namespace engine