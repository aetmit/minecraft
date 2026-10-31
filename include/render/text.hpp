#pragma once

#include <core/color.hpp>
#include <render/opengl/texture.hpp>
#include <render/opengl/shader.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <string_view>

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
    bool rightAligned;

    std::string text;

    const opengl::Texture* bitmapTexture{nullptr};

    void engineInit(opengl::Texture& texture);

    float spaceCharacter(unsigned char c, float size) const;
    float lineWidth(std::string_view line) const;

    friend class opengl::Renderer;

public:
    Text(std::string text, float x, float y, float size = 2.0f, Color color = Color(255, 255, 255));

    Text(Text&& other);

    Text(const Text&) = delete;

    ~Text();

    void hide();

    void show();

    bool visible() const;

    void setText(const std::string& newText);

    void setPos(float newX, float newY);

    void setRightAligned(float rightX, float y);

    void render(
        opengl::Shader& shaderProgram,
        int windowWidth,
        int windowHeight
    );

    Text& operator=(const Text&) = delete;
};

}  // namespace engine
