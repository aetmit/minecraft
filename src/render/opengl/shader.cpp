#include <render/opengl/shader.hpp>

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <memory>
#include <optional>
#include <filesystem>

namespace engine {

OpenGLShaderProgram::OpenGLShaderProgram(Window* window) {
    program = glCreateProgram();
}

OpenGLShaderProgram::~OpenGLShaderProgram() {
    glDeleteProgram(program);
}


OpenGLShaderProgram::operator GLuint() const {
    return program;
}

void OpenGLShaderProgram::compileShader(const std::filesystem::path& file, OpenGLShaderType shaderType) {
    auto shader = loadShader(file);
    if (!shader) {
        throw std::runtime_error("faield to load shader") ;
    }
    shaders.push_back(compileShader(shader->c_str(), static_cast<GLuint>(shaderType)));
}

int OpenGLShaderProgram::link() {
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

GLuint OpenGLShaderProgram::getProgram() const {
    return program;
}

void OpenGLShaderProgram::bind() const {
    glUseProgram(program);
}


std::optional<std::string> OpenGLShaderProgram::loadShader(const std::filesystem::path& file) const {
    std::ifstream shaderFile(file);
    if (!shaderFile.is_open()) {
        return std::nullopt; 
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint OpenGLShaderProgram::compileShader(const char *shaderSource, GLuint type) const {
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

}  // namespace engine
