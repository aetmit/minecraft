#include <render/opengl/program.hpp>

#include <glad/glad.h>

#include <fstream>

namespace engine {

OpenGLShaderProgram::OpenGLShaderProgram(Window* window) {
    window->makeContextCurrent();
    if (!gladLoadGL()) {
        throw std::runtime_error("Failed to load GLAD");
    }
    program = glCreateProgram();
}

OpenGLShaderProgram::~OpenGLShaderProgram() {
    glDeleteProgram(program);
}


OpenGLShaderProgram::operator GLuint() const {
    return program;
}

void OpenGLShaderProgram::loadShader(const std::filesystem::path& file, OpenGLShaderType shaderType) {
    shaders.push_back(compileShader(loadShader(file).c_str(), static_cast<GLuint>(shaderType)));
}

int OpenGLShaderProgram::link() {
    for (const auto& shader : shaders) {
        glAttachShader(program, shader);
    }

    glLinkProgram(program);
    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) { return status; }

    for (const auto& shader : shaders) {
        glDeleteShader(shader);
    }
    shaders.clear();
    return status;
}

void OpenGLShaderProgram::use() const {
    glUseProgram(program);
}


std::string OpenGLShaderProgram::loadShader(const std::filesystem::path& file) const {
    std::ifstream shaderFile(file);
    if (!shaderFile.is_open()) {
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}

GLuint OpenGLShaderProgram::compileShader(const char * shaderSource, GLuint type) const {
    GLuint shader;
    int status;
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(std::format("Failed to compile shader: {}", infoLog));
    }
    return shader;
}

}  // namespace engine
