#include <render/text.hpp>
#include <render/opengl/shader.hpp>
#include <render/opengl/texture.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdexcept>

namespace engine {

void Text::engineInit(opengl::Texture& texture) {
    bitmapTexture = &texture;
}

Text::Text(std::string text, float x, float y, float size, Color color) :
    text(text),
    x(x),
    y(y),
    size(size),
    color(color),
    hidden(false)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Text::Text(Text&& other) {
    bitmapTexture = other.bitmapTexture;
    color = other.color;
    text = other.text;
    size = other.size;
    vao = other.vao;
    vbo = other.vbo;
    x = other.x;
    y = other.y;
    hidden = other.hidden;

    // Assign to default
    other.bitmapTexture = nullptr;
    other.text = "";
    other.size = 0;
    other.vao = 0;
    other.vbo = 0;
    other.x = 0;
    other.y = 0;
    other.hidden = false;
}

Text::~Text() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Text::hide() {
    hidden = true;
}

void Text::show() {
    hidden = false;
}

void Text::setText(const std::string& newText) {
    text = newText;
}

void Text::setPos(float newX, float newY) {
    x = newX;
    y = newY;
}

void Text::render(
    opengl::Shader& shaderProgram,
    int windowWidth,
    int windowHeight
) {
    const int atlasColumns = 16;
    const int atlasRows = 16;

    if (hidden) { return; }

    shaderProgram.bind();
    const glm::vec4 normalizedColor = color.normalize();
    shaderProgram.setUniform4f(
        "textColor",
        normalizedColor.r,
        normalizedColor.g,
        normalizedColor.b,
        normalizedColor.a
    );

    bitmapTexture->bind();
    shaderProgram.setUniform1i("textAtlas", 0);

    glm::mat4 projection = glm::ortho(
        0.0f,
        static_cast<float>(windowWidth),
        0.0f,
        static_cast<float>(windowHeight)
    );
    shaderProgram.setUniformMat4("projection", projection);

    const GLboolean depthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);

    glBindVertexArray(vao);

    const float charWidth = 8.0f * size;
    const float charHeight = 8.0f * size;
    float cursorX = x;
    float cursorY = y;

    for (unsigned char character : text) {
        if (character == '\n') {
            cursorX = x;
            cursorY -= charHeight;
            continue;
        }
        if (character == '\r') {
            cursorX = x;
            continue;
        }

        const int glyphIndex = static_cast<int>(character);
        const int col = glyphIndex % atlasColumns;
        const int row = glyphIndex / atlasColumns;

        float uWidth = 1.0f / atlasColumns;
        float vHeight = 1.0f / atlasRows;
        
        float u = col * uWidth;
        float v = row * vHeight;

        float xpos = cursorX;
        float ypos = cursorY;

        float vertices[6][4] = {
            { xpos,             ypos + charHeight, u,          v           },
            { xpos,             ypos,              u,          v + vHeight },
            { xpos + charWidth, ypos,              u + uWidth, v + vHeight },

            { xpos,             ypos + charHeight, u,          v           },
            { xpos + charWidth, ypos,              u + uWidth, v + vHeight },
            { xpos + charWidth, ypos + charHeight, u + uWidth, v           }
        };

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        cursorX += charWidth;
    }

    glBindVertexArray(0);
    if (depthTestEnabled) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

}  // namespace engine
