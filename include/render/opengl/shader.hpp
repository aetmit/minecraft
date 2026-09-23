#pragma once

#include <window/window.hpp>

#include <glad/glad.h>

#include <filesystem>
#include <string>
#include <vector>

namespace engine {

namespace opengl { 

enum class ShaderType : GLuint {
    Vertex   = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER  
};

class ShaderProgram {
public:
    ShaderProgram(Window* window);

    ~ShaderProgram();

    GLuint getProgram() const;

    void compileShader(const std::filesystem::path& file, ShaderType shaderType);

    GLint getUniformLocation(const std::string &name);

    int link();

    void bind() const;

private:
    GLuint program;
    std::vector<GLuint> shaders;

    [[nodiscard]] 
    std::optional<std::string> loadShader(const std::filesystem::path& file) const;

    [[nodiscard]] 
    GLuint compileShader(const char *shaderSource, GLuint type) const;
};

}

} // namespace engine
