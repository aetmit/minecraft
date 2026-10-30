#pragma once

#include <core/color.hpp>
#include <render/opengl/texture.hpp>
#include <render/opengl/shader.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>

namespace engine {

namespace opengl {
class Renderer;
}

class Text {
private:
    GLuint vao{0};
    GLuint vbo{0};

    Color color;

    float x;
    float y;

    float size;

    bool hidden;

    std::string text;

    const opengl::Texture* bitmapTexture{nullptr};

    void engineInit(opengl::Texture& texture);

    friend class opengl::Renderer;

public:
    Text(std::string text, float x, float y, float size = 2.0f, Color color = Color(255, 255, 255));

    Text(Text&& other);

    Text(const Text&) = delete;

    ~Text();

    void hide();

    void show();

    void render(
        opengl::Shader& shaderProgram,
        int windowWidth,
        int windowHeight
    );

    Text& operator=(const Text&) = delete;
};

}  // namespace engine
