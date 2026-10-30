#include <render/opengl/shader.hpp>

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <memory>
#include <optional>
#include <filesystem>

#include <math/glm.hpp>

namespace engine {

namespace opengl {

Shader::Shader(Window* window, Logger &logger): logger(logger) {
    program = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(program);
}


void Shader::compileShader(const std::filesystem::path& file, ShaderType shaderType) {
    auto shader = loadShader(file);
    if (!shader) {
        throw std::runtime_error("faield to load shader") ;
    }
    shaders.push_back(compileShader(shader->c_str(), static_cast<GLuint>(shaderType)));
}

int Shader::link() {
    for (const auto& shader : shaders) {
        glAttachShader(program, shader);
    }

    glLinkProgram(program);
    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) { 
        return status; 
    }

    for (const auto& shader : shaders) {
        glDeleteShader(shader);
    }
    shaders.clear();
    return status;
}

GLuint Shader::getProgram() const {
    return program;
}

void Shader::bind() const {
    glUseProgram(program);
}

GLint Shader::getUniformLocation(const std::string &name) {
    return glGetUniformLocation(getProgram(), name.c_str());
}

void Shader::setUniform1i(const std::string &name, int i1) {
    int location = getUniformLocation(name);
    if (location == -1) {
        logger.error(("failed to locate uniform with name: " + name).c_str());
        logger.warn("uniform not set");
        return;
    }
    glUniform1i(location, i1);
}

void Shader::setUniform3f(const std::string &name, float f1, float f2, float f3) {
    int location = getUniformLocation(name);
    if (location == -1) {
        logger.error(("failed to locate uniform with name: " + name).c_str());
        logger.warn("uniform not set");
        return;
    }
    glUniform3f(location, f1, f2, f3);
}

void Shader::setUniform4f(const std::string &name, float f1, float f2, float f3, float f4) {
    int location = getUniformLocation(name);
    if (location == -1) {
        logger.error(("failed to locate uniform with name: " + name).c_str());
        logger.warn("uniform not set");
        return;
    }
    glUniform4f(location, f1, f2, f3, f4);
}

void Shader::setUniformMat4(const std::string &name, glm::mat4 &mat4) {
    int location = getUniformLocation(name);
    if (location == -1) {
        logger.error(("failed to locate uniform with name: " + name).c_str());
        logger.warn("uniform not set");
        return;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

std::optional<std::string> Shader::loadShader(const std::filesystem::path& file) const {
    std::ifstream shaderFile(file);
    if (!shaderFile.is_open()) {
        return std::nullopt; 
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint Shader::compileShader(const char *shaderSource, GLuint type) const {
    int status;
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        // use a unique ptr here because we do not know the length of the log message
        // ahead of time so we must allocate on the heap and unique_ptr
        // provides us with automatic cleanup once we throw
        auto infoLog = std::make_unique<char[]>(length);
        glGetShaderInfoLog(shader, 512, nullptr, infoLog.get());
        // prevent resource leak by deleting shader before we throw
        glDeleteShader(shader);
        throw std::runtime_error(std::string("Failed to compile shader: ") + infoLog.get());
    }
    return shader;
}

} // namespace opengl

}  // namespace engine
