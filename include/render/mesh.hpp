#pragma once

#include <cstdint>
#include <vector>

#include <render/vertex.hpp>

namespace engine {

// a generic mesh interface for game facing code to call
// different rendering apis should extend this class and provide implementations for methods
class Mesh {

public:

    virtual ~Mesh() = default;


protected:

};

struct MeshData {
    std::vector<std::uint32_t> indices;
    std::vector<Vertex> vertices;

    void addIndex(std::uint32_t index);
    void addVertex(Vertex vertex);
};

} // namespace engine