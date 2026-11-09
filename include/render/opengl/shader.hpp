#pragma once


#include <filesystem>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <math/glm.hpp>

#include <window/window.hpp>
#include <core/logger.hpp>
namespace engine {

namespace opengl { 

enum class ShaderType : GLuint {
    Vertex   = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER  
};

class Shader {
public:
    Shader(Window* window, Logger &logger);

    ~Shader();

    GLuint getProgram() const;

    void compileShader(const std::filesystem::path& file, ShaderType shaderType);

    GLint getUniformLocation(const std::string &name);

    void setUniform4f(const std::string &name, float f1, float f2, float f3, float f4);
    void setUniform1i(const std::string &name, int i1);
    void setUniform3f(const std::string &name, float f1, float f2, float f3);
    void setUniformMat4(const std::string &name, glm::mat4 &mat4);

    int link();

    void bind() const;

private:
    GLuint program;
    std::vector<GLuint> shaders;

    Logger &logger;

    [[nodiscard]] 
    std::optional<std::string> loadShader(const std::filesystem::path& file) const;

    [[nodiscard]] 
    GLuint compileShader(const char *shaderSource, GLuint type) const;
};

}

} // namespace engine
