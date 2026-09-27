#pragma once

#include <cstdint>

namespace engine {

// a generic mesh interface for game facing code to call
// different rendering apis should extend this class and provide implementations for methods
class Mesh {

public:
    virtual void addIndex(std::uint32_t index) = 0;

    virtual ~Mesh() = default;

protected:

};

} // namespace engine