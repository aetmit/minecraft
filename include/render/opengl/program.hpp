#pragma once

#include <window/window.hpp>

#include <glad/glad.h>

#include <filesystem>
#include <vector>

namespace engine {

enum class OpenGLShaderType : GLuint {
    Vertex   = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER  
};

class OpenGLShaderProgram {
public:
    OpenGLShaderProgram(Window* window);

    ~OpenGLShaderProgram();

    operator GLuint() const;

    void loadShader(const std::filesystem::path& file, OpenGLShaderType shaderType);

    int link();

    void use() const;

protected:
    GLuint program;
    std::vector<GLuint> shaders;

    [[nodiscard]] 
    std::optional<std::string> loadShader(const std::filesystem::path& file) const;

    [[nodiscard]] 
    GLuint compileShader(const char *shaderSource, GLuint type) const;
};

} // namespace engine
