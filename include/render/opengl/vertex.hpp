#pragma once

#include <cstddef>
#include <cstdint>

namespace engine {

namespace opengl {

struct Vertex {

public:
    Vertex(float x, float y,  float z, float u, float v);

    std::size_t offsetX() const;
    std::size_t offsetY() const;
    std::size_t offsetZ() const; 
    std::size_t offsetU() const;
    std::size_t offsetV() const;


    float x;
    float y;
    float z;

    float u;
    float v;

private:
    std::uintptr_t getThisOffset() const;
};

} // namespace opengl

} // namespace engine